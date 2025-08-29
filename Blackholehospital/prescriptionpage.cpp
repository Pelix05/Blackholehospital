#include "prescriptionpage.h"
#include "ui_prescriptionpage.h"
#include <QMessageBox>

PrescriptionPage::PrescriptionPage(const QString &patientInfo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PrescriptionPage)
    , patientInfo(patientInfo)
{
    ui->setupUi(this);
    setWindowTitle("处方编辑页面");
    resize(400, 400);

    // 设置患者信息
    ui->infoLabel->setText(patientInfo);

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
    QMessageBox::information(this, "提示", "处方已保存！");
}

void PrescriptionPage::onBackButtonClicked()
{
    this->close();
}
