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
    setWindowTitle("RECHARGE");


        // Background gradient
        this->setStyleSheet("background-color: qlineargradient("
                            "x1: 0, y1: 0, x2: 1, y2: 1,"
                            "stop: 0 #e6f7ff, stop: 1 #ffffff);");

        // Amount input style
        ui->editAmount->setStyleSheet(
            "QLineEdit {"
            "   background-color: #ffffff;"
            "   border: 2px solid #3498db;"
            "   border-radius: 8px;"
            "   padding: 6px 10px;"
            "   font-size: 16px;"
            "   color: #333;"
            "}"
            "QLineEdit:focus {"
            "   border: 2px solid #2980b9;"
            "   background-color: #f0f9ff;"
            "}"
        );

        // Pay button style
        ui->btnPay->setStyleSheet(
            "QPushButton {"
            "   background-color: #27ae60;"
            "   color: white;"
            "   font-size: 18px;"
            "   padding: 8px 20px;"
            "   border-radius: 10px;"
            "}"
            "QPushButton:hover { background-color: #219150; }"
            "QPushButton:pressed { background-color: #1b7c42; }"
        );

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
    payDialog->resize(400, 300);

    // Dialog style (card look)
    payDialog->setStyleSheet(
        "QDialog {"
        "   background-color: #ffffff;"
        "   border: 2px solid #3498db;"
        "   border-radius: 12px;"
        "}"
        "QLabel {"
        "   font-size: 16px;"
        "   color: #333;"
        "}"
    );

    QVBoxLayout *layout = new QVBoxLayout(payDialog);

    QLabel *infoLabel = new QLabel("充值金额：" + amount + " 元", payDialog);
    infoLabel->setStyleSheet("QLabel { color: #0066cc; font-weight: bold; }");
    layout->addWidget(infoLabel);

    // 付款码占位
    QLabel *qrLabel = new QLabel("[付款码区域 - 预留位置]", payDialog);
    qrLabel->setAlignment(Qt::AlignCenter);
    qrLabel->setStyleSheet("QLabel {"
                           "   border: 2px dashed #7f8c8d;"
                           "   border-radius: 8px;"
                           "   padding: 40px;"
                           "   color: #555;"
                           "   font-size: 14px;"
                           "}");
    layout->addWidget(qrLabel);

    payDialog->setLayout(layout);
    payDialog->exec();  // 模态对话框
}

