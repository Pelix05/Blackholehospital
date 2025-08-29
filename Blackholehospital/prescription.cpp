#include "prescription.h"
#include "ui_prescription.h"

Prescription::Prescription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Prescription),
    model(new QStandardItemModel(this))
{
    ui->setupUi(this);
    model->setHorizontalHeaderLabels({"序号", "日期", "科室", "主治医生", "处方内容"});
    ui->tableView->setModel(model);

    // 测试数据
    addOrder("1", "2025-08-02", "内科", "王五", "消炎药处方", "头孢克肟片 1 次/天，连用 7 天");
    addOrder("2", "2025-08-12", "外科", "赵六", "止痛药处方", "布洛芬片 2 次/天，连用 3 天");

}

Prescription::~Prescription()
{
    delete ui;
}

void Prescription::addOrder(const QString &id, const QString &date,
                                  const QString &dept, const QString &doctor,
                                  const QString &summary, const QString &detail)
{
    QList<QStandardItem*> row;
    row << new QStandardItem(id)
        << new QStandardItem(date)
        << new QStandardItem(dept)
        << new QStandardItem(doctor)
        << new QStandardItem(summary + " - " + detail);
    model->appendRow(row);
}
