#include "patientmainwindow.h"
#include "ui_patientmainwindow.h"
#include "registerpage.h"
#include "medicalrecord.h"
#include "appointment.h"
#include "healthyselfcheck.h"
#include "recharge.h"
#include "loginwidget.h"
#include "medicinesearch.h"
#include "patientinfo.h"
#include <QMessageBox>
#include <QDebug>

patientmainwindow::patientmainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::patientmainwindow)
{
    ui->setupUi(this);
    setWindowTitle("PATIENT");
    // ===== STYLE SHEET UNTUK MAIN WINDOW =====
        this->setStyleSheet(
            "QMainWindow {"
            "   background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #e6f7ff, stop: 1 #f0f8ff);"
            "   font-family: 'Segoe UI', Arial, sans-serif;"
            "}"
        );
        // ===== END STYLE MAIN WINDOW =====

        // ===== STYLE SHEET UNTUK TOMBOL SIDEBAR =====
        QString sidebarButtonStyle =
                "QPushButton {"
                                                   "background-color: #0066cc;"
                                                   "color: white;"
                                                   "border-radius: 10px;"
                                                   "padding: 12px;"
                                                   "font-size: 16px;"
                                                   "font-weight: bold;"
                                                   "}"
                                                   "QPushButton:hover {"
                                                   "background-color: #0052a3;"
                                                   "}"
                                                   "QPushButton:pressed {"
                                                   "background-color: #003d7a;"                                   "}";

        ui->register_2->setStyleSheet(sidebarButtonStyle);
        ui->medicalrecord->setStyleSheet(sidebarButtonStyle);
        ui->appointment->setStyleSheet(sidebarButtonStyle);
        // ===== END STYLE TOMBOL SIDEBAR =====

        // ===== STYLE SHEET UNTUK STACKED WIDGET =====
        ui->stackedWidget->setStyleSheet(
            "QStackedWidget {"
            "   background-color: white;"            // isi biar kontras
            "   border: 2px solid #0066cc;"          // warna border
            "   border-radius: 12px;"                // sudut melengkung
            "   padding: 8px;"                       // jarak isi dari border
            "}"
        );
        // ===== END STYLE STACKED WIDGET =====

        // ===== STYLE SHEET UNTUK HEADER/LABEL =====
        ui->labelTitle->setStyleSheet(
            "QLabel {"
            "   color: #0066cc;"
            "   font-size: 24px;"
            "   font-weight: bold;"
            "   background-color: transparent;"
            "   padding: 10px;"
            "   margin-bottom: 20px;"
            "}"
        );
        // ===== END STYLE HEADER =====

        registerpage *regpage = new registerpage(this);
        medicalrecord *medrc = new medicalrecord(this);
        appointment *apm = new appointment(this);
        healthyselfcheck *selfc = new healthyselfcheck(this);
        medicinesearch *mdsrch = new medicinesearch(this);




    ui -> stackedWidget -> addWidget(regpage);
    ui-> stackedWidget ->addWidget(medrc);
    ui-> stackedWidget ->addWidget(apm);
    ui-> stackedWidget ->addWidget(selfc);
    ui-> stackedWidget ->addWidget(mdsrch);

    // 显式连接信号槽
    connect(ui->register_2, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(regpage);
    });

    connect(ui->medicalrecord, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(medrc);
    });

    connect(ui->appointment, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(apm);
    });

    connect(ui->selfcheck, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(selfc);
    });

    connect(ui->medicinesearch, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(mdsrch);
    });

    connect(ui->btnback, &QPushButton::clicked, this, [=]() {
        LoginWidget *loginWindow = new LoginWidget();
        loginWindow->show();
        this->close();
    });

    connect(ui->btnpayment, &QPushButton::clicked, this, [=]() {
        recharge *rech = new recharge();
        rech->show();
    });

    connect(ui->personalprofile, &QPushButton::clicked, this, [=]() {
        patientinfo *pinfo = new patientinfo();
        pinfo->show();
    });

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
