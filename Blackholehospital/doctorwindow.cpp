#include "doctorwindow.h"
#include "ui_doctorwindow.h"
#include "doctorwindow.h"
#include "doctorprofilepage.h"
#include "appointmentlistpage.h"
#include "attendancepage.h"
#include "doctorplatform.h"
#include "patientdetailpage.h"
#include "prescriptionpage.h"
#include "loginwidget.h"

doctorwindow::doctorwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctorwindow)
{
    ui->setupUi(this);
    this->setWindowTitle("DOCTOR");

    this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #e6f7ff, stop: 1 #ffffff);");

    // Style untuk judul
    ui->lTitle->setStyleSheet("QLabel {"
                                 "color: #0066cc;"
                                 "font-size: 28px;"
                                 "font-weight: bold;"
                                 "background-color: transparent;"
                                 "}");


    ui->frame->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #3498db;"
        "   border-radius: 12px;"
        "   background-color: #f8f9fa;"
        "   padding: 12px;"
        "}"
    );

    // Styling semua button di dalam frame
    QString buttonStyle =
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   font-size: 18px;"
        "   padding: 8px 16px;"
        "   border-radius: 10px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1f6391;"
        "}";

    ui->btnInfo->setStyleSheet(buttonStyle);
    ui->btnCase->setStyleSheet(buttonStyle);
    ui->btnPrescription->setStyleSheet(buttonStyle);
    ui->btnProfile->setStyleSheet(buttonStyle);
    ui->btnPlatform->setStyleSheet(buttonStyle);
    ui->btnAttendance->setStyleSheet(buttonStyle);
    ui->btnExit->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   font-size: 14px;"
        "   padding: 8px 16px;"
        "   border-radius: 8px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #c0392b;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #962d22;"
        "}"
    );

    connect(ui->btnInfo, &QPushButton::clicked, this, &doctorwindow::onAppointmentInfoClicked);
    connect(ui->btnCase, &QPushButton::clicked, this, &doctorwindow::onEditCaseClicked);
    connect(ui->btnPrescription, &QPushButton::clicked, this, &doctorwindow::onEditPrescriptionClicked);
    connect(ui->btnProfile, &QPushButton::clicked, this, &doctorwindow::onEditProfileClicked);
    connect(ui->btnPlatform, &QPushButton::clicked, this, &doctorwindow::onPlatformClicked);
    connect(ui->btnAttendance, &QPushButton::clicked, this, &doctorwindow::onAttendanceClicked);
    connect(ui->btnExit, &QPushButton::clicked, this, &doctorwindow::onExitClicked);
}

void doctorwindow::onEditProfileClicked()
{
    doctorprofilepage *profilePage = new doctorprofilepage();
    profilePage->show();
}

void doctorwindow::onExitClicked()
{
    LoginWidget *loginWindow = new LoginWidget();
    loginWindow->show();
    this->close();
}

void doctorwindow::onAppointmentInfoClicked()
{
    appointmentlistpage *appointmentPage = new appointmentlistpage();
    appointmentPage->show();

}

void doctorwindow::onEditCaseClicked()
{

PatientDetailPage *patientdetailPage = new PatientDetailPage("");
patientdetailPage->show();

}

void doctorwindow::onEditPrescriptionClicked()
{
 PrescriptionPage *prescriptionPage = new PrescriptionPage("");
 prescriptionPage->show();

}

void doctorwindow::onAttendanceClicked()
{
    attendancepage *attendancePage = new attendancepage();
    attendancePage->show();

}

void doctorwindow::onPlatformClicked()
{
    doctorplatform *doctorPage = new doctorplatform();
    doctorPage->show();

}

doctorwindow::~doctorwindow()
{
    delete ui;
}


