#include "editprofile.h"
#include "ui_editprofile.h"

editprofile::editprofile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editprofile)
{
    ui->setupUi(this);

    // 连接确认按钮
    connect(ui->btnconfirm, &QPushButton::clicked, [=](){
        personalinfo updated = getupdatedinfo();
        emit confirmupdate(updated);
    });

    connect(ui->btnback,&QPushButton::clicked,
            this, &editprofile::cancel);
}

editprofile::~editprofile()
{
    delete ui;
}

void editprofile :: setpatientinfo(const personalinfo &info)
{
    currentinfo = info;

    ui->editname->setText(info.name);
    ui->editemail->setText(info.email);
    ui->editphone->setText(info.phone);
    ui->editidnumber->setText(info.idNumber);
    ui->comboBox->setCurrentText(info.gender);
}

personalinfo editprofile :: getupdatedinfo() const
{
    personalinfo info;

    info.name = ui->editname->text();
    info.gender = ui->comboBox->currentText();
    info.email = ui->editemail->text();
    info.phone = ui->editphone->text();
    info.idNumber = ui->editidnumber->text();

    return info;
}
