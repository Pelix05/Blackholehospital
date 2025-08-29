#include "doctorwindow.h"
#include "ui_doctorwindow.h"
#include "doctorwindow.h"
#include "doctorprofilepage.h"
#include "appointmentlistpage.h"
#include "attendancepage.h"
#include "doctorplatform.h"

doctorwindow::doctorwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctorwindow)
{
    ui->setupUi(this);
    connect(ui->btnInfo, &QPushButton::clicked, this, &doctorwindow::onAppointmentInfoClicked);
     //   connect(ui->btnCase, &QPushButton::clicked, this, &doctorwindow::onEditCaseClicked);
     //   connect(ui->btnPrescription, &QPushButton::clicked, this, &doctorwindow::onEditPrescriptionClicked);
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
    close();
}

void doctorwindow::onAppointmentInfoClicked()
{
    appointmentlistpage *appointmentPage = new appointmentlistpage();
    appointmentPage->show();

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


