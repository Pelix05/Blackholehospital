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
    QString recordId = model->item(row, 0)->text();
    QString diagnose = model->item(row, 4)->text();

    QString department = "未知科室"; // 可以拓展从 doctor_id 查询科室

    QString instructions = generateInstructions(department);
    QString prescription = generatePrescription(department);

    casedialog dialog(recordId, diagnose, instructions, prescription, this);
    dialog.exec();
}

// 生成模拟医嘱
QString medicalrecord::generateInstructions(const QString &department)
{
    if (department == "内科") {
        return "1. 注意休息，多饮水\n2. 按时服药，每日3次\n3. 如有高热不退或症状加重，请及时复诊\n4. 饮食清淡，避免辛辣刺激食物";
    } else if (department == "外科") {
        return "1. 患肢制动，抬高患肢\n2. 伤后48小时内冷敷，48小时后热敷\n3. 按时服用消肿止痛药物\n4. 一周后复诊，如有肿胀加重请及时就医";
    } else if (department == "眼科") {
        return "1. 按时滴眼药水，每日4次\n2. 注意手部卫生，避免揉眼\n3. 毛巾、脸盆等用品单独使用，防止交叉感染\n4. 症状消失后继续用药3天以巩固疗效";
    } else {
        return "1. 注意休息，避免劳累\n2. 按时服药\n3. 如有不适，请及时就医\n4. 定期复查";
    }
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
