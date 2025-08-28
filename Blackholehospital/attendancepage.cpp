#include "attendancepage.h"
#include "ui_attendancepage.h"

#include <QDateTime>
#include <QMessageBox>

attendancepage::attendancepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::attendancepage)
{
    ui->setupUi(this);
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
        ui->lStatus->setText("上班打卡时间: " + currentTime);
        QMessageBox::information(this, "打卡成功", "上班打卡成功\n时间: " + currentTime);
    }

    void attendancepage::onCheckOutClicked()
    {
        QString currentTime = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
        ui->lStatus->setText("下班打卡时间: " + currentTime);
        QMessageBox::information(this, "打卡成功", "下班打卡成功\n时间: " + currentTime);
    }

    void attendancepage::onLeaveRequestClicked()
    {
        QMessageBox::information(this, "请假申请", "请假申请功能开发中");
    }

    void attendancepage::onBackClicked()
    {
        emit backButtonClicked();  // Emit signal untuk kembali
    }
