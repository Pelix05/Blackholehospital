#include "casedialog.h"
#include "ui_casedialog.h"
#include "instruction.h"
#include "prescription.h"


casedialog::casedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::casedialog)
{
    ui->setupUi(this);
    this->setWindowTitle("病例详情");

    connect(ui->pushButton,&QPushButton::clicked,
            this,&casedialog::backbuttonclicked);

    // 点击 → 弹出医嘱对话框
    connect(ui->insturctions, &QPushButton::clicked, this, [=](){
        instruction dlg(this);
        dlg.exec();
    });

    connect(ui->prescription, &QPushButton::clicked, this, [=](){
        Prescription dlg(this);
        dlg.exec();
    });
}

casedialog::~casedialog()
{
    delete ui;
}

void casedialog::setCaseInfo(QString doctor, QString dep, QString date, QString result)
{
    ui->labelDoctor->setText("主治医生: " + doctor);
    ui->labelDep->setText("科室: " + dep);
    ui->labelDate->setText("日期: " + date);
    ui->textEditResult->setText(result);

}

void casedialog::backbuttonclicked()
{
    this->hide();
}
