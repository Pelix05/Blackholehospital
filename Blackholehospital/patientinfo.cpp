#include "patientinfo.h"
#include "ui_patientinfo.h"
#include "editprofile.h"
#include "databasemanager.h"
#include <QDebug>
#include <QMessageBox>

patientinfo::patientinfo(const QString &idCard) :
    ui(new Ui::patientinfo)
{
    ui->setupUi(this);
    setWindowTitle("PATIENT INFO");
    this->setStyleSheet(R"(
        QWidget {
            background-color: qlineargradient(x1: 0, y1: 0,
                                              x2: 1, y2: 1,
                                              stop: 0 #e6f7ff,
                                              stop: 1 #ffffff);
            font-family: "Segoe UI";
            font-size: 14px;
            color: #333;
        }

        /* Frame besar (utama) */
        QFrame#infoFrame {
            background-color: #ffffff;
            border: 1px solid #ccc;
            border-radius: 10px;
            padding: 10px;
        }

        /* Frame kecil (row value) */
        QFrame.valueFrame {
            background-color: #ffffff;
            border: 1px solid #ccc;
            border-radius: 6px;
            padding: 6px;
        }

        /* Buttons */
        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 10px;
            padding: 8px 16px;
            font-size: 14px;
            font-weight: 500;
        }

        QPushButton:hover {
            background-color: #45a049;
        }

        QPushButton:pressed {
            background-color: #0078d7;
        }
    )");






    qDebug() << "idCard:" << idCard;

    loadFromDatabase(idCard);

    connect(ui->editButton, &QPushButton::clicked, [=](){
        // 创建编辑页面实例
        editprofile *editPage = new editprofile;

        // 设置初始信息
        editPage->setpatientinfo(currentinfo);

        // 连接编辑页面信号
        connect(editPage, &editprofile::confirmupdate, this, [=](const personalinfo &info){
            // 更新查看页面数据
            setpatientinfo(info);

            // 删除编辑页面实例，关闭窗口
            editPage->close();
            editPage->deleteLater();
        });

        connect(editPage, &editprofile::cancel, editPage, [=](){
            // 用户取消修改 → 关闭编辑页面
            editPage->close();
            editPage->deleteLater();
        });

        // 显示编辑页面（可以用 show() 或 exec() 如果改成 QDialog）
        editPage->show();   // 非模态窗口
        // editPage->exec(); // 如果 PersonalInfoEditPage 改成 QDialog 模式
    });


}



patientinfo::~patientinfo()
{
    delete ui;
}

void patientinfo :: setpatientinfo(const personalinfo &info)
{
    currentinfo = info;

    qDebug() << "Name:" << info.name;
    qDebug() << "id:" << info.idNumber;
    qDebug() << "Email:" << info.email;
    qDebug() << "Phone:" << info.phone;
    qDebug() << "bitrhDate:" << info.birthDate;
    qDebug() << "gender:" << info.gender;
    qDebug() << "address:" << info.address;


    ui->labelname->setText(info.name);
    ui->labelgender->setText(info.gender);
    ui->labelidnumber->setText(info.idNumber);
    ui->labelemail->setText(info.email);
    ui->labelphone->setText(info.phone);
    ui->labelbirth->setText(info.birthDate);
    ui->labeladdress->setText(info.address);

}

void patientinfo::loadFromDatabase(const QString &idCard)
{
    qDebug() << "Calling loadFromDatabase with username/idCard:" << idCard;

    DatabaseManager &db = DatabaseManager::instance();
    QMap<QString, QVariant> user = db.getPatientInfo(idCard);

    if(user.isEmpty()) {
        QMessageBox::critical(this,"Database Error", "Wrong user name!!");
        qDebug() << "username is" <<idCard ;
        return;
    }

    personalinfo info;
    info.name = user["name"].toString();
    info.gender = user["gender"].toString();
    info.birthDate = user["birth_date"].toString();
    info.idNumber = user["id_card"].toString();
    info.phone = user["phone"].toString();
    info.address = user["address"].toString();
    info.email = user["email"].toString();

    setpatientinfo(info);
}
