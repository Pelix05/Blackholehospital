#include "casedialog.h"
#include "ui_casedialog.h"


casedialog::casedialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::casedialog)
{
    ui->setupUi(this);
    this->setWindowTitle("病例详情");

    connect(ui->pushButton,&QPushButton::clicked,
            this,&casedialog::backbuttonclicked);
}

casedialog::~casedialog()
{
    delete ui;
}

void casedialog::setCaseInfo(QString doctor, QString dep, QString date, QString result,QString instructions,QString prescription)
{
    ui->labelDoctor->setText("主治医生: " + doctor);
    ui->labelDep->setText("科室: " + dep);
    ui->labelDate->setText("日期: " + date);
    ui->textEditResult->setText(result);
    ui->labelinstruction->setText(instructions);
    ui->labelprescription->setText(prescription);

}

void casedialog::backbuttonclicked()
{
    this->hide();
}
