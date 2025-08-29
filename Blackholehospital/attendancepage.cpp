#include "attendancepage.h"
#include "ui_attendancepage.h"

#include <QDateTime>
#include <QMessageBox>

attendancepage::attendancepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::attendancepage)
{
    ui->setupUi(this);
    this->setWindowTitle("ATTANDANCE");

    this->setObjectName("attendancePage");
       ui->btnCheckIn->setObjectName("btnCheckIn");
       ui->btnCheckOut->setObjectName("btnCheckOut");
       ui->btnPermission->setObjectName("btnPermission");
       ui->btnBack->setObjectName("btnBack");
       ui->lStatusIn->setObjectName("statusLabel");
       ui->lStatusOut->setObjectName("statusLabel");

       // Asumsikan frame untuk attendance dan leave
       ui->frameAttendance->setObjectName("attendanceFrame");
       ui->frameLeave->setObjectName("leaveFrame");

       // Asumsikan ada line edit untuk alasan
       ui->leReason->setObjectName("reasonInput");

       // Apply stylesheet
       this->setStyleSheet(R"(
           /* === Main window background === */
           #attendancePage {
               background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                           stop:0 #e6f7ff, stop:1 #ffffff);
               font-family: "Segoe UI";
               font-size: 14px;
               color: #2c3e50;
           }

           /* === Attendance Frame (Check-in/Check-out) === */
           QFrame#attendanceFrame {
               background: #ffffff;
               border: 2px solid #0078d7;
               border-radius: 12px;
               padding: 20px;
               margin: 10px;
           }

           /* === Leave Frame (Permission) === */
           QFrame#leaveFrame {
               background: #ffffff;
               border: 2px solid #28a745;
               border-radius: 12px;
               padding: 20px;
               margin: 10px;
           }

           /* === Status label === */
           QLabel#statusLabel {
               font-size: 15px;
               font-weight: 600;
               color: #0078d7;
               background-color: #f8f9fa;
               border: 1px solid #dee2e6;
               border-radius: 8px;
               padding: 12px;
               margin: 10px 0;
               min-height: 25px;
           }

           /* === General button style === */
           QPushButton {
               border: none;
               border-radius: 8px;
               padding: 12px 20px;
               font-weight: 600;
               min-height: 40px;
               font-size: 14px;
               margin: 5px;
           }

           /* === Check-in button === */
           QPushButton#btnCheckIn {
               background-color: #0078d7;
               color: white;
           }
           QPushButton#btnCheckIn:hover {
               background-color: #005fa3;
           }
           QPushButton#btnCheckIn:pressed {
               background-color: #004578;
           }

           /* === Check-out button === */
           QPushButton#btnCheckOut {
               background-color: #6c757d;
               color: white;
           }
           QPushButton#btnCheckOut:hover {
               background-color: #5a6268;
           }
           QPushButton#btnCheckOut:pressed {
               background-color: #495057;
           }

           /* === Permission button === */
           QPushButton#btnPermission {
               background-color: #28a745;
               color: white;
           }
           QPushButton#btnPermission:hover {
               background-color: #218838;
           }
           QPushButton#btnPermission:pressed {
               background-color: #1e7e34;
           }

           /* === Back button === */
           QPushButton#btnBack {
               background-color: #6c757d;
               color: white;
               border-radius: 8px;
               padding: 10px 20px;
               min-height: 40px;
               margin-top: 20px;
           }
           QPushButton#btnBack:hover {
               background-color: #5a6268;
           }
           QPushButton#btnBack:pressed {
               background-color: #495057;
           }

           /* === Reason input === */
           QLineEdit#reasonInput {
               border: 1px solid #ced4da;
               border-radius: 6px;
               padding: 10px;
               background: #ffffff;
               min-height: 35px;
               font-size: 14px;
               margin: 10px 0;
           }
           QLineEdit#reasonInput:focus {
               border: 2px solid #28a745;
               background: #f8fff9;
           }

           /* === Frame titles (jika ada label di dalam frame) === */
           QLabel {
               font-weight: 600;
               color: #2c3e50;
               font-size: 14px;
           }

           /* === Section titles (jika ada) === */
           QLabel[title="section"] {
               font-size: 16px;
               font-weight: 700;
               color: #0078d7;
               margin-bottom: 15px;
           }

           /* === Message box styling === */
           QMessageBox {
               background-color: #ffffff;
               font-family: "Segoe UI";
           }

           QMessageBox QLabel {
               font-size: 14px;
               color: #333;
           }

           QMessageBox QPushButton {
               background-color: #0078d7;
               color: white;
               border-radius: 6px;
               padding: 8px 16px;
               min-height: 30px;
           }

           QMessageBox QPushButton:hover {
               background-color: #005fa3;
           }
       )");


    // Connect signals and slots
        connect(ui->btnCheckIn, &QPushButton::clicked, this, &attendancepage::onCheckInClicked);
        connect(ui->btnCheckOut, &QPushButton::clicked, this, &attendancepage::onCheckOutClicked);
        connect(ui->btnPermission, &QPushButton::clicked, this, &attendancepage::onLeaveRequestClicked);
        connect(ui->btnBack, &QPushButton::clicked, this, &attendancepage::onBackClicked);
    }

    attendancepage::~attendancepage()
    {
        delete ui;
    }

    void attendancepage::onCheckInClicked()
    {
        QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->lStatusIn->setText("Get on work: " + currentTime);
        QMessageBox::information(this, "success", "Attendance\nTIME: " + currentTime);
    }

    void attendancepage::onCheckOutClicked()
    {
        QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->lStatusOut->setText("Get off work: " + currentTime);
        QMessageBox::information(this, "success", "Get off work\nTIME: " + currentTime);
    }

    void attendancepage::onLeaveRequestClicked()
    {
        QMessageBox::information(this, "Permission", "请假申请功能开发中");
    }

    void attendancepage::onBackClicked()
    {
        emit backButtonClicked();  // Emit signal untuk kembali
    }
