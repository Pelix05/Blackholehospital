#include "medicalrecord.h"
#include "ui_medicalrecord.h"
#include "casedialog.h"
#include "databasemanager.h"
#include <QStandardItem>
#include <QMessageBox>

medicalrecord::medicalrecord(const QString &patientIdCard,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medicalrecord),
    m_patientIdCard(patientIdCard)
{
    ui->setupUi(this);
    this->setWindowTitle("MEDICAL RECORD");
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({"Record ID", "Date", "Doctor ID", "Doctor Name", "Diagnose"});
    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    ui->tableView->setStyleSheet(
                "QTableView {"
                "   background-color: white;"
                "   border: 4px solid #0066cc;"
                "   border-radius: 8px;"
                "   gridline-color: #cce6ff;"
                "   selection-background-color: #cce6ff;"
                "   padding: 12px;"

                "   selection-color: #003366;"
                "}"
                "QHeaderView::section {"
                "   background-color: #0066cc;"
                "   color: white;"
                "   padding: 2px;"
                "   border: none;"
                "   font-weight: bold;"
                "   font-size: 16px;"
                "}"
                "QTableCornerButton::section {"
                "   background-color: #0066cc;"
                "   border: none;"
                "}"
                "QTableView::item {"
                "   padding: 16px;"
                "}"
                "QTableView::item:selected {"
                "   background-color: #99ccff;"
                "   color: black;"
                "}"
    );

    connect(ui->tableView,&QTableView::doubleClicked,
            this,&medicalrecord::doubleclicked);

    // 初始加载病例
    loadMedicalRecords();

}

medicalrecord::~medicalrecord()
{
    delete ui;
}

void medicalrecord::loadMedicalRecords()
{
    qDebug() << "Loading medical records for patient id card:" << m_patientIdCard;

    model->removeRows(0, model->rowCount());

    DatabaseManager &db = DatabaseManager::instance();

        // ----------------- 获取患者信息 -----------------
        QMap<QString, QVariant> patientInfo = db.getPatientInfo(m_patientIdCard);
        qDebug() << "Patient info:" << patientInfo;
        if (patientInfo.isEmpty()) {
            QMessageBox::warning(this, "错误", "未找到该患者信息，无法加载病例！");
            return;
        }

        int patientId = patientInfo["patient_id"].toInt();
         QString patientName = patientInfo["name"].toString();

        QList<QMap<QString, QVariant>> records = db.getMedicalRecordsByPatient(patientId);
        if (records.isEmpty()) {
               qDebug() << "No medical records found for patient, generating test data.";

               // 获取医生列表
               QMap<QString,int> doctorIds;
               QSqlQuery q2("SELECT doctor_id, name FROM doctors");
               while(q2.next()) {
                   doctorIds[q2.value("name").toString()] = q2.value("doctor_id").toInt();
               }

               if (!doctorIds.isEmpty()) {
                   // 随机选一个医生
                   QString docName = doctorIds.firstKey(); // 这里可以改成随机选择
                   int doctorId = doctorIds[docName];

                   // 插入测试病例
                   QSqlQuery query;
                   query.prepare("INSERT INTO medical_records (patient_id, doctor_id, diagnose, created_at) "
                                 "VALUES (:pid, :did, :diag, datetime('now','localtime'))");
                   query.bindValue(":pid", patientId);
                   query.bindValue(":did", doctorId);
                   query.bindValue(":diag", patientName + " 的测试诊断");
                   if(!query.exec()) {
                       qDebug() << "Failed to insert test medical record:" << query.lastError().text();
                   } else {
                       qDebug() << "✅ 已为患者" << patientName << "生成测试病例";
                   }

                   // 再次获取病例
                   records = db.getMedicalRecordsByPatient(patientId);
               }
           }

        qDebug() << "Records found:" << records.size();
        for (const auto &rec : records) {
            qDebug() << "Record:" << rec;
        }

          for (const auto &rec : records) {
              int doctorId = rec["doctor_id"].toInt();

              // 先通过 doctor_id 查 id_card
              QSqlQuery q;
              q.prepare("SELECT id_card FROM doctors WHERE doctor_id=?");
              q.addBindValue(doctorId);
              QString doctorIdCard;
              if (q.exec() && q.next()) {
                  doctorIdCard = q.value("id_card").toString();
              } else {
                  qDebug() << "Cannot find id_card for doctor_id:" << doctorId;
                  doctorIdCard = ""; // 兜底
              }

              QMap<QString, QVariant> docInfo = db.getDoctorInfo(doctorIdCard);
               // 新增按 doctor_id 查询
              QString doctorName = docInfo.isEmpty() ? QString("医生%1").arg(doctorId) : docInfo["name"].toString();

              QList<QStandardItem*> row;
              row << new QStandardItem(rec["record_id"].toString());
              row << new QStandardItem(rec["created_at"].toDateTime().toString("yyyy-MM-dd HH:mm"));
              row << new QStandardItem(doctorIdCard);
              row << new QStandardItem(doctorName);
              row << new QStandardItem(rec["diagnose"].toString());

              model->appendRow(row);
          }
}

void medicalrecord::doubleclicked(const QModelIndex &index){

    if (!index.isValid()) return;

    int row = index.row();
    QString recordId   = model->item(row, 0)->text();
    QString date       = model->item(row, 1)->text();
    QString doctorId   = model->item(row, 2)->text();
    QString doctorName = model->item(row, 3)->text();
    QString diagnose   = model->item(row, 4)->text();

    QString department = "未知科室"; // 可以拓展从 doctor_id 查询科室

    casedialog dialog(doctorName, department, date, diagnose, this);
    dialog.exec();
}

// 生成模拟处方
QString medicalrecord::generatePrescription(const QString &department)
{
    if (department == "内科") {
        return "1. 阿莫西林胶囊 0.5g × 24粒\n   用法：口服，每次2粒，每日3次\n2. 复方甘草片 × 1瓶\n   用法：口服，每次3片，每日3次\n3. 布洛芬缓释胶囊 0.3g × 12粒\n   用法：口服，每次1粒，每日2次（发热时服用）";
    } else if (department == "外科") {
        return "1. 云南白药气雾剂 × 1瓶\n   用法：外用，每日3-4次\n2. 双氯芬酸钠肠溶片 25mg × 24片\n   用法：口服，每次1片，每日3次\n3. 活血止痛胶囊 × 36粒\n   用法：口服，每次2粒，每日3次";
    } else if (department == "眼科") {
        return "1. 左氧氟沙星滴眼液 5ml × 1支\n   用法：滴眼，每次1-2滴，每日4次\n2. 阿昔洛韦滴眼液 8ml × 1支\n   用法：滴眼，每次1-2滴，每日4次\n3. 玻璃酸钠滴眼液 0.1% × 1支\n   用法：滴眼，每次1滴，每日4次";
    } else {
        return "1. 维生素C片 100mg × 30片\n   用法：口服，每次1片，每日3次\n2. 复合维生素B片 × 30片\n   用法：口服，每次1片，每日3次";
    }
}
