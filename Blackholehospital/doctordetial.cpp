#include "doctordetial.h"
#include "ui_doctordetial.h"
#include <QPixmap>

doctordetial::doctordetial(QWidget *parent)  :

    QDialog(parent),
    ui(new Ui::doctordetial)
{
    ui->setupUi(this);
    this->setWindowTitle("DOCTOR'S DETAIL");
    this->setModal(true);
}

doctordetial::~doctordetial()
{
    delete ui;
}

void doctordetial::setDoctorInfo(const QString &jobId,
                                       const QString &department,
                                       const QString &name,
                                       const QString &profile,
                                       const QString &photoPath,
                                       const QString &workTime,
                                       double fee,
                                       int limit)
{
    ui->labelName->setText("姓名: " + name);
    ui->labelJobId->setText("工号: " + jobId);
    ui->labelDep->setText("科室: " + department);
    ui->labelProfile->setText("个人资料: " + profile);
    ui->labelWorkTime->setText("上班时间: " + workTime);
    ui->labelFee->setText("挂号费用: " + QString::number(fee));
    ui->labelLimit->setText("单日上限: " + QString::number(limit));

    QPixmap pix(photoPath);
    if (!pix.isNull()) {
        ui->labelPhoto->setPixmap(
            pix.scaled(120, 160, Qt::KeepAspectRatio, Qt::SmoothTransformation)
        );
    }
}


