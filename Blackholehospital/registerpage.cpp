#include "registerpage.h"
#include "ui_registerpage.h"
#include "databasemanager.h"
#include <QDialog>
#include <QMessageBox>
#include <QStandardItem>
#include <QTableView>
#include <QDate>
#include <QTime>

registerpage::registerpage(const QString &patientIdCard, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerpage)
  , m_patientIdCard(patientIdCard)
{
    qDebug() << "registerpage created for patientIdCard:" << m_patientIdCard;
    ui->setupUi(this);
    this->setWindowTitle("REGISTER");
    // 设置表格模型
    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels({
        "排班ID", "医生姓名", "科室", "门诊", "工号",
        "上班时间", "下班时间", "挂号费用", "限额", "已预约人数"
    });

    ui->tableView->setModel(model);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);



    // ====== STYLE UNTUK REGISTER PAGE ======
    this->setStyleSheet(
        "QWidget {"
        "   background-color: #f9fcff;"   // warna background lembut
        "   font-family: 'Segoe UI', Arial, sans-serif;"
        "   font-size: 15px;"
        "   color: #333;"
        "}"

        // Tombol (misalnya ui->pushButton)
        "QPushButton {"
        "   background-color: #0066cc;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 12px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0052a3;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #003d7a;"
        "}"

        // TableView (tabel dokter)
                "QTableView {"
                    "   background-color: white;"
                "   border: 4px solid #0066cc;"
                    "   border-radius: 5px;"
                    "   gridline-color: #cce6ff;"
                    "   selection-background-color: #cce6ff;"
                    "   selection-color: #003366;"
                    "}"
                    "QHeaderView::section {"
                    "   background-color: #0066cc;"
                    "   color: white;"
                    "   padding: 6px;"
                    "   border: none;"
                    "   font-weight: bold;"
                    "   font-size: 14px;"
                    "}"
                "QTableView::item {"
                "   padding: 16px;"
                "}"
                    "QTableCornerButton::section {"
                    "   background-color: #0066cc;"  // samain dengan header
                    "   border: none;"
                    "}"

        // Baris tabel
        "QTableView::item {"
        "   padding: 4px;"
        "}"
        "QTableView::item:selected {"
        "   background-color: #99ccff;"
        "   color: black;"
        "}"
    );

    loadDoctorSchedules();

    connect(ui->pushButton, &QPushButton::clicked,
            this, &registerpage::button_clicked);

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &registerpage::onDoctorDoubleClicked);
}

registerpage::~registerpage()
{
    delete ui;
}

void registerpage::loadDoctorSchedules()
{
    model->removeRows(0, model->rowCount());

    // 调用数据库查询接口（这里传空参数表示查询全部）
    auto schedules = DatabaseManager::instance().queryDoctorSchedules(
        "", "", "", QDate(), QTime(), false);
    qDebug() << "Schedules size:" << schedules.size();

    QString sql = "SELECT s.*, d.name, d.gender, d.phone, d.email "
                  "FROM doctor_schedules s "
                  "JOIN doctors d ON s.doctor_id = d.doctor_id WHERE 1=1 ";
    qDebug() << sql;


    for (int i = 0; i < schedules.size(); ++i) {
        QList<QStandardItem*> row;
        row << new QStandardItem(schedules[i]["schedule_id"].toString())
            << new QStandardItem(schedules[i]["name"].toString())
            << new QStandardItem(schedules[i]["department"].toString())
            << new QStandardItem(schedules[i]["clinic"].toString())
            << new QStandardItem(schedules[i]["job_number"].toString())
            << new QStandardItem(schedules[i]["start_time"].toString())
            << new QStandardItem(schedules[i]["end_time"].toString())
            << new QStandardItem(schedules[i]["fee"].toString())
            << new QStandardItem(schedules[i]["limit_per_day"].toString())
            << new QStandardItem(schedules[i]["booked_count"].toString());
        model->appendRow(row);
    }
}

void registerpage::button_clicked()
{


    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if (!selection->hasSelection()) {
        QMessageBox::warning(this, "Attention", "Please select a Doctor");
        return;
    }

    int row = selection->currentIndex().row();
    int scheduleId = model->item(row, 0)->text().toInt();

    QString error;
       bool ok = DatabaseManager::instance().bookAppointmentBySchedule(
           m_patientIdCard, scheduleId, QDateTime::currentDateTime(), &error);

       if (ok) {
           QMessageBox::information(this, "成功", "挂号成功！");
           loadDoctorSchedules();  // 刷新
       } else {
           QMessageBox::critical(this, "失败", "挂号失败: " + error);
       }
}

// 双击医生姓名时弹出详情
void registerpage::onDoctorDoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    QString name = model->item(row, 1)->text();
    QString dept = model->item(row, 2)->text();
    QString clinic = model->item(row, 3)->text();
    QString profile = name + " 医生（科室：" + dept + "，门诊：" + clinic + "），经验丰富。";

    QMessageBox::information(this, "医生详情", profile);
}


