#include "instruction.h"
#include "ui_instruction.h"

instruction::instruction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instruction),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    model ->setHorizontalHeaderLabels ({"序号", "日期", "科室", "主治医生", "内容"});
    ui -> tableView ->setModel(model);

    // 添加测试数据
    addOrder("1", "2025-08-01", "内科", "张三", "感冒药处方", "阿莫西林胶囊 2 次/天");
    addOrder("2", "2025-08-10", "外科", "李四", "术后医嘱", "保持伤口清洁，复查日期 8月15日");

}

instruction::~instruction()
{
    delete ui;
}

void instruction::addOrder(const QString &id, const QString &date, const QString &dept, const QString &doctor, const QString &summary, const QString &detail){
    QList<QStandardItem*> row;
    row << new QStandardItem(id)
        << new QStandardItem(date)
        << new QStandardItem(dept)
        << new QStandardItem(doctor)
        << new QStandardItem(summary + " - " + detail);
    model->appendRow(row);
}
