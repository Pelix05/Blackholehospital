#include "patientdetailpage.h"
#include "ui_patientdetailpage.h"
#include "prescriptionpage.h"
#include <QMessageBox>

PatientDetailPage::PatientDetailPage(const QString &patientInfo, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::PatientDetailPage)
    , patientInfo(patientInfo)
{
    ui->setupUi(this);
    setWindowTitle("患者病例详情");
    resize(400, 450);

    // 设置患者信息
    ui->infoLabel->setText(patientInfo);

    // 连接信号槽
    connect(ui->saveBtn, &QPushButton::clicked, this, &PatientDetailPage::onSaveButtonClicked);
    connect(ui->prescriptionBtn, &QPushButton::clicked, this, &PatientDetailPage::onPrescriptionButtonClicked);
    connect(ui->backBtn, &QPushButton::clicked, this, &PatientDetailPage::onBackButtonClicked);
}

PatientDetailPage::~PatientDetailPage()
{
    delete ui;
}

void PatientDetailPage::onSaveButtonClicked()
{
    QMessageBox::information(this, "保存", "医嘱已保存！");
}

void PatientDetailPage::onPrescriptionButtonClicked()
{
    PrescriptionPage *presPage = new PrescriptionPage(patientInfo);
    presPage->show();
}

void PatientDetailPage::onBackButtonClicked()
{
    this->close();
}
