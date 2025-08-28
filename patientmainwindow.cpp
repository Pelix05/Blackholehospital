#include "patientmainwindow.h"
#include "ui_patientmainwindow.h"
#include "registerpage.h"
#include <QMessageBox>
#include <QDebug>

patientmainwindow::patientmainwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::patientmainwindow)
{
    ui->setupUi(this);
    setWindowTitle("患者界面");

    registerpage *regpage = new registerpage(this);
    ui -> stackedWidget -> addWidget(regpage);

    // 显式连接信号槽
    connect(ui->pushButton, &QPushButton::clicked,
            this, &patientmainwindow::register_clicked);

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

