#include "prescriptionpage.h"
#include "ui_prescriptionpage.h"
#include <QMessageBox>

PrescriptionPage::PrescriptionPage(const QString &patientInfo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PrescriptionPage)
    , patientInfo(patientInfo)
{
    ui->setupUi(this);
    setWindowTitle("PRESCRIPTION EDIT");


    // 设置患者信息
    ui->infoLabel->setText(patientInfo);

    this->setStyleSheet("background-color: qlineargradient("
                            "x1: 0, y1: 0, x2: 1, y2: 1,"
                            "stop: 0 #f0f9ff, stop: 1 #ffffff);");

        ui->infoLabel->setStyleSheet("QLabel {"
                                     "color: #0066cc;"
                                     "font-size: 20px;"
                                     "font-weight: bold;"
                                     "background-color: transparent;"
                                     "}");

        QString saveButtonStyle =
            "QPushButton {"
            "   background-color: #27ae60;"
            "   color: white;"
            "   font-size: 16px;"
            "   padding: 8px 20px;"
            "   border-radius: 10px;"
            "}"
            "QPushButton:hover { background-color: #219150; }"
            "QPushButton:pressed { background-color: #1b7c42; }";

        QString backButtonStyle =
            "QPushButton {"
            "   background-color: #e74c3c;"
            "   color: white;"
            "   font-size: 16px;"
            "   padding: 8px 20px;"
            "   border-radius: 10px;"
            "}"
            "QPushButton:hover { background-color: #c0392b; }"
            "QPushButton:pressed { background-color: #962d22; }";

        ui->saveBtn->setStyleSheet(saveButtonStyle);
        ui->backBtn->setStyleSheet(backButtonStyle);

        // Style untuk QTextEdit prescription
        QString textEditStyle =
            "QTextEdit {"
            "   background-color: #ffffff;"
            "   border: 2px solid #27ae60;"
            "   border-radius: 8px;"
            "   padding: 6px;"
            "   font-size: 14px;"
            "   color: #333;"
            "}"
            "QTextEdit:focus {"
            "   border: 2px solid #1b7c42;"
            "   background-color: #f0fff5;"
            "}";

        if (ui->prescriptionEdit) {
            ui->prescriptionEdit->setStyleSheet(textEditStyle);
        }


    // 连接信号槽
    connect(ui->saveBtn, &QPushButton::clicked, this, &PrescriptionPage::onSaveButtonClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, &PrescriptionPage::onBackButtonClicked);
}

PrescriptionPage::~PrescriptionPage()
{
    delete ui;
}

void PrescriptionPage::onSaveButtonClicked()
{
    QMessageBox::information(this, "Success", "Prescription has been saved！");
}

void PrescriptionPage::onBackButtonClicked()
{
    this->close();
}
