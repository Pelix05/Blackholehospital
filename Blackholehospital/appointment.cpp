#include "appointment.h"
#include "ui_appointment.h"
#include "databasemanager.h"
#include <QMessageBox>
#include<QHeaderView>
#include <QDebug>


appointment::appointment(const QString &patientIdCard, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appointment),
    resultsModel(new QStandardItemModel(this)),
    m_patientIdCard(patientIdCard)
{
    ui->setupUi(this);
    qDebug() << "Appointment page created for patient:" << m_patientIdCard;
    this->setWindowTitle("APPOINTMENT");
    ui->resultsView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);




    resultsModel->setHorizontalHeaderLabels({
        "Schedule ID", "Doctor ID", "Doctor Name", "Hospital", "Department",
        "Clinic", "Work Date", "Time", "Fee", "Limit", "Booked", "Remaining"
    });

    ui->resultsView->setModel(resultsModel);      // link model to QTableView
    ui->resultsView->setSelectionBehavior(QAbstractItemView::SelectRows); // select row
    ui->resultsView->setSelectionMode(QAbstractItemView::SingleSelection);// select single

    populateFilterChoices();                      // 从 doctors 提取医院/科室/门诊，填充下拉

    // ====== STYLE UNTUK APPOINTMENT PAGE ======
    this->setStyleSheet(
        "QWidget {"
        "   background-color: #f9fcff;"   // background lembut
        "   font-family: 'Segoe UI', Arial, sans-serif;"
        "   font-size: 14px;"
        "   color: #333;"
        "}"

        // Tombol utama
        "QPushButton {"
        "   background-color: #0066cc;"
        "   color: white;"
        "   border-radius: 8px;"
        "   padding: 8px 16px;"
        "   font-weight: bold;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #0052a3;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #003d7a;"
        "}"

        // ComboBox (下拉选择医院/科室/门诊)
        "QComboBox {"
        "   border: 1px solid #0066cc;"
        "   border-radius: 6px;"
        "   padding: 4px 8px;"
        "   background: white;"
        "}"
        "QComboBox::drop-down {"
        "   border: none;"
        "   width: 20px;"
        "}"
        "QComboBox QAbstractItemView {"
        "   background: white;"
        "   selection-background-color: #cce6ff;"
        "   selection-color: #003366;"
        "}"

        // DateEdit & TimeEdit
        "QDateEdit, QTimeEdit {"
        "   border: 1px solid #0066cc;"
        "   border-radius: 6px;"
        "   padding: 4px 8px;"
        "   background: white;"
        "}"

        // TableView hasil pencarian
        "QTableView {"
        "   background-color: white;"
        "   border: 4px solid #0066cc;"
        "   border-radius: 4px;"
        "   gridline-color: #cce6ff;"
        "   selection-background-color: #cce6ff;"
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


    // 显式连接信号槽
    connect(ui->searchButton, &QPushButton::clicked,
            this, &appointment::searchclicked);
    connect(ui->bookButton,   &QPushButton::clicked,
            this, &appointment::bookclicked);

    // 设定时间控件
    ui->dateedit->setCalendarPopup(true);
    ui->dateedit->setDate(QDate::currentDate());

    ui->timeEdit->setDisplayFormat("HH:mm");
    ui->timeEdit->setTime(QTime::currentTime());

    //初次进入页面时，展示所有支持预约的医生
    searchclicked();
}

appointment::~appointment()
{
    delete ui;
}

void appointment::populateFilterChoices()     // 根据 doctors 动态填充下拉框
{
    DatabaseManager &db = DatabaseManager::instance();
    QList<QVariantMap> schedules = db.queryDoctorSchedules("", "", "", QDate(), QTime(), false);

    QSet<QString> hospitals, departments, clinics;
    for (auto m : schedules) {
        hospitals.insert(m["hospital"].toString());
        departments.insert(m["department"].toString());
        clinics.insert(m["clinic"].toString());
    }

    ui->hospitalCombo->clear();                   // 先清空，再添加“全部”+选项
    ui->hospitalCombo->addItem("ALL");
    for (auto &h : hospitals) ui->hospitalCombo->addItem(h);

    ui->departmentCombo->clear();
    ui->departmentCombo->addItem("ALL");
    for (auto &d : departments) ui->departmentCombo->addItem(d);

    ui->clinicCombo->clear();
    ui->clinicCombo->addItem("ALL");
    for (auto &c : clinics) ui->clinicCombo->addItem(c);
}


void appointment::searchclicked()           // 点击“搜索”后执行过滤
{
    QString hospital = ui->hospitalCombo->currentText();
    QString department = ui->departmentCombo->currentText();
    QString clinic = ui->clinicCombo->currentText();
    if (hospital == "ALL") hospital.clear();
    if (department == "ALL") department.clear();
    if (clinic == "ALL") clinic.clear();

    QDate date = ui->dateedit->date();
    QTime time = ui->timeEdit->time();

    DatabaseManager &db = DatabaseManager::instance();
    QList<QVariantMap> schedules = db.queryDoctorSchedules(
        hospital, department, clinic, date, time, true
    );

    refillResults(schedules);
}

void appointment::refillResults(const QList<QVariantMap> &schedules)
{
     resultsModel->removeRows(0, resultsModel->rowCount());

    for (const auto &m : schedules) {
            QList<QStandardItem*> row;
            int scheduleId = m["schedule_id"].toInt();
            int limit = m["limit_per_day"].toInt();
            int booked = m["booked_count"].toInt();
            int remain = limit - booked;

            row << new QStandardItem(QString::number(scheduleId));
            row << new QStandardItem(m["doctor_id"].toString());
            row << new QStandardItem(m["name"].toString());
            row << new QStandardItem(m["hospital"].toString());
            row << new QStandardItem(m["department"].toString());
            row << new QStandardItem(m["clinic"].toString());
            row << new QStandardItem(m["work_date"].toDate().toString("yyyy-MM-dd"));
            row << new QStandardItem(m["start_time"].toString() + "-" + m["end_time"].toString());
            row << new QStandardItem(QString::number(m["fee"].toDouble(), 'f', 2));
            row << new QStandardItem(QString::number(limit));
            row << new QStandardItem(QString::number(booked));
            row << new QStandardItem(QString::number(remain));

            resultsModel->appendRow(row);
        }
}

void appointment::bookclicked()
{
    QItemSelectionModel *sel = ui->resultsView->selectionModel();
    if (!sel->hasSelection()) {
        QMessageBox::warning(this, "提示", "请选择一个医生排班！");
        return;
    }

    int row = sel->currentIndex().row();
    int scheduleId = resultsModel->item(row, 0)->text().toInt();

    QString error;
    bool ok = DatabaseManager::instance().bookAppointmentBySchedule(
        m_patientIdCard, scheduleId, QDateTime::currentDateTime(), &error
    );

    if (ok) {
        QMessageBox::information(this, "成功", "预约成功！");
        searchclicked(); // 刷新列表
    } else {
        QMessageBox::critical(this, "失败", "预约失败: " + error);
    }

}


