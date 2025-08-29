#include "healthyselfcheck.h"
#include "ui_healthyselfcheck.h"
#include <QMessageBox>

healthyselfcheck::healthyselfcheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::healthyselfcheck)
{
    ui->setupUi(this);

    // 提交按钮
    connect(ui->btnSubmit, &QPushButton::clicked,
            this, &healthyselfcheck::submit);
}

healthyselfcheck::~healthyselfcheck()
{
    delete ui;
}

void healthyselfcheck::submit(){
    QString gender;
        if (ui->rbMale->isChecked())
            gender = "男";
        else if (ui->rbFemale->isChecked())
            gender = "女";
        else
            gender = "未选择";

        QStringList symptoms;
        if (ui->cbFever->isChecked()) symptoms << "发烧";
        if (ui->cbCough->isChecked()) symptoms << "咳嗽";
        if (ui->cbHeadache->isChecked()) symptoms << "头痛";

        QString result;
        if (symptoms.isEmpty()) {
            result = "您的状态良好，请继续保持健康的生活习惯！";
        } else {
            result = "您选择的症状有：" + symptoms.join("、") +
                     "\n建议及时就医，注意休息和饮食。";
        }

        QMessageBox::information(this, "自测结果",
                                 "性别：" + gender + "\n" + result);
}
