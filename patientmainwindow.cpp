#include "patientmainwindow.h"
#include "ui_patientmainwindow.h"
#include "registerpage.h"
#include "medicalrecord.h"
#include "appointment.h"
#include <QMessageBox>
#include <QDebug>

patientmainwindow::patientmainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::patientmainwindow)
{
    ui->setupUi(this);
    setWindowTitle("患者界面");

    registerpage *regpage = new registerpage(this);
    medicalrecord *medrc = new medicalrecord(this);
    appointment *apm = new appointment(this);
    ui -> stackedWidget -> addWidget(regpage);
    ui-> stackedWidget ->addWidget(medrc);
    ui-> stackedWidget ->addWidget(apm);

    // 显式连接信号槽
    connect(ui->register_2, &QPushButton::clicked,
            this, &patientmainwindow::register_clicked);

    connect(ui->medicalrecord, &QPushButton::clicked,
            this, &patientmainwindow::medicalrecord_clicked);

    connect(ui->appointment, &QPushButton::clicked,
            this, &patientmainwindow::appointment_clicked);

}

patientmainwindow::~patientmainwindow()
{
    delete ui;
}

void patientmainwindow::register_clicked(){

    //QMessageBox::information(this, "test","clicked");

    ui -> stackedWidget -> setCurrentIndex(2);

    qDebug() << "current index:" << ui->stackedWidget->currentIndex();
}

void patientmainwindow::medicalrecord_clicked(){

    //QMessageBox::information(this, "test","clicked");

    ui -> stackedWidget -> setCurrentIndex(3);

    qDebug() << "current index:" << ui->stackedWidget->currentIndex();
}

void patientmainwindow::appointment_clicked(){

    //QMessageBox::information(this, "test","clicked");

    ui -> stackedWidget -> setCurrentIndex(4);

    qDebug() << "current index:" << ui->stackedWidget->currentIndex();
}
