#include "registerpage.h"
#include "ui_registerpage.h"
#include <QMessageBox>
#include <QStandardItem>
#include <QTableView>

registerpage::registerpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerpage)
{
    ui->setupUi(this);

    connect(ui->pushButton, &QPushButton::clicked,
            this, &registerpage::button_clicked);

    model = new QStandardItemModel(this);
    model->setHorizontalHeaderLabels(
        {"编号", "科室", "工号", "姓名", "上班时间", "费用", "上限", "已预约", "剩余"}
    );

    // 添加测试数据
    addDoctor("D001", "内科", "1001", "张三", "08:00-12:00", 20, 10, 3);
    addDoctor("D002", "外科", "1002", "李四", "14:00-18:00", 25, 8, 8);

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
}

registerpage::~registerpage()
{
    delete ui;
}

void registerpage::button_clicked()
{


    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if (!selection->hasSelection()) {
        QMessageBox::warning(this, "提示", "请先选择一个医生");
        return;
    }

    QModelIndex index = selection->currentIndex();
    int row = index.row();
    int booked = model->item(row, 7)->text().toInt();
    int limit  = model->item(row, 6)->text().toInt();
    int remain = model->item(row, 8)->text().toInt();

    if (remain <= 0) {
        QMessageBox::information(this, "提示", "该医生今日已无余号");
        return;
    }

    booked++;
    remain = limit - booked;
    model->setItem(row, 7, new QStandardItem(QString::number(booked)));
    model->setItem(row, 8, new QStandardItem(QString::number(remain)));

    QMessageBox::information(this, "成功", "挂号成功！");
}

void registerpage::addDoctor(QString id, QString dep, QString job, QString name,
                             QString time, double fee, int limit, int booked)
{
    QList<QStandardItem*> row;
    row << new QStandardItem(id)
        << new QStandardItem(dep)
        << new QStandardItem(job)
        << new QStandardItem(name)
        << new QStandardItem(time)
        << new QStandardItem(QString::number(fee))
        << new QStandardItem(QString::number(limit))
        << new QStandardItem(QString::number(booked))
        << new QStandardItem(QString::number(limit - booked));
    model->appendRow(row);
}
