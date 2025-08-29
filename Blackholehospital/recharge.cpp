#include "recharge.h"
#include "ui_recharge.h"
#include <QDoubleValidator>
#include <QMessageBox>
#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>

recharge::recharge(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::recharge)
{
    ui->setupUi(this);

    // 金额输入框只允许输入正数
    QDoubleValidator *validator = new QDoubleValidator(0, 1000000000, 2, this);
    validator->setNotation(QDoubleValidator::StandardNotation);
    ui->editAmount->setValidator(validator);

    // 支付按钮
    connect(ui->btnPay, &QPushButton::clicked,
            this, &recharge::Payclicked);
}

recharge::~recharge()
{
    delete ui;
}

void recharge::Payclicked()
{
    QString amount = ui->editAmount->text();

    if (amount.isEmpty() || amount.toDouble() <= 0) {
        QMessageBox::warning(this, "提示", "请输入正确的充值金额！");
        return;
    }

    // 创建支付弹窗
    QDialog *payDialog = new QDialog(this);
    payDialog->setWindowTitle("支付");

    QVBoxLayout *layout = new QVBoxLayout(payDialog);

    QLabel *infoLabel = new QLabel("充值金额：" + amount + " 元", payDialog);
    layout->addWidget(infoLabel);

    // 付款码占位
    QLabel *qrLabel = new QLabel("[付款码区域 - 预留位置]", payDialog);
    qrLabel->setAlignment(Qt::AlignCenter);
    qrLabel->setStyleSheet("QLabel { border: 1px dashed gray; padding: 20px; }");
    layout->addWidget(qrLabel);

    payDialog->setLayout(layout);
    payDialog->exec();  // 模态对话框
}
