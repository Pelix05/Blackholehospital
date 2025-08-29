#include "patientinfo.h"
#include "ui_patientinfo.h"
#include "editprofile.h"

patientinfo::patientinfo(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::patientinfo)
{
    ui->setupUi(this);

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

}
