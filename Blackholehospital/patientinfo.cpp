#include "patientinfo.h"
#include "ui_patientinfo.h"
#include "editprofile.h"

patientinfo::patientinfo(QWidget *parent) :
    QWidget(parent),
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

        QLabel {
            font-size: 14px;
            color: #222;
            padding: 2px;
        }

        /* Label untuk judul data (Nama:, Gender:, dll.) */
        QLabel[data-label="title"] {
            font-weight: bold;
            color: #555;
        }

        /* Label untuk isi data pasien */
        QLabel[data-label="value"] {
            background-color: #ffffff;
            border: 1px solid #ddd;
            border-radius: 8px;
            padding: 6px 10px;
            min-width: 200px;
        }

        QPushButton {
            background-color: #4CAF50;
            color: white;
            border-radius: 10px;
            padding: 8px 16px;
            font-size: 14px;
        }

        QPushButton:hover {
            background-color: #45a049;
        }

        QPushButton:pressed {
            background-color: #0078d7;
        }

    )");



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

    ui->labelname->setText(info.name);
    ui->labelgender->setText(info.gender);
    ui->labelidnumber->setText(info.idNumber);
    ui->labelemail->setText(info.email);
    ui->labelphone->setText(info.phone);
    ui->labelbirth->setText(info.birthDate);
    ui->labeladdress->setText(info.address);

}
