#include "editprofile.h"
#include "ui_editprofile.h"

editprofile::editprofile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::editprofile)
{
    ui->setupUi(this);
    this->setWindowTitle("EDIT PROFILE");

    this->setStyleSheet(R"(
        QWidget {
            background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #e6f7ff, stop: 1 #ffffff);
        }

        QLabel {
            font-size: 14px;
            color: #444;
            font-weight: 500;
        }

        QLineEdit {
            border: 1px solid #ccc;
            border-radius: 8px;
            padding: 6px 10px;
            background-color: #fff;
        }
        QLineEdit:focus {
            border: 1px solid #0078d7;
            background-color: #eef6ff;
        }

        QComboBox {
            border: 1px solid #ccc;
            border-radius: 8px;
            padding: 6px 10px;
            background-color: #fff;
        }
        QComboBox:hover {
            border: 1px solid #0078d7;
        }

        QPushButton {
            border: none;
            border-radius: 10px;
            padding: 8px 16px;
            font-size: 14px;
            font-weight: 500;
        }

        QPushButton#btnconfirm {
            background-color: #0078d7;
            color: white;
        }
        QPushButton#btnconfirm:hover {
            background-color: #005fa3;
        }

        QPushButton#btnback {
            background-color: #ff0000;
                        color: white;
            color: #333;
        }
        QPushButton#btnback:hover {
            background-color: #8B0000;
        }
    )");

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
    ui->leDateBirth->setText(info.birthDate);
    ui->leAddress->setText(info.address);
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
