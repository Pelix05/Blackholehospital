#include "hospitalization.h"
#include "ui_hospitalization.h"

hospitalization::hospitalization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hospitalization)
{
    ui->setupUi(this);
}

hospitalization::~hospitalization()
{
    delete ui;
}

void hospitalization::setHospitalizationInfo(const HospitalizationInfo &info)
{
    currentInfo = info;

    ui->lblDoctor->setText(info.doctor);
    ui->lblRoom->setText(info.room);
    ui->lblBed->setText(info.bed);
    ui->lblAdmissionDate->setText(info.admissionDate);
}
