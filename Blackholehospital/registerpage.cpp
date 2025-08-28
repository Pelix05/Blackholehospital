#include "registerpage.h"
#include "ui_registerpage.h"
#include "doctordetial.h"
#include <QDialog>
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

    connect(ui->tableView, &QTableView::doubleClicked,
            this, &registerpage::onDoctorDoubleClicked);


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

// 双击医生姓名时弹出详情
void registerpage::onDoctorDoubleClicked(const QModelIndex &index)
{
    int row = index.row();
    int col = index.column();

    // 只处理“姓名”列（第 3 列，索引为 3）
    if (col == 3) {
        QString jobId   = model->item(row, 2)->text();
        QString dep     = model->item(row, 1)->text();
        QString name    = model->item(row, 3)->text();
        QString workTime= model->item(row, 4)->text();
        double fee      = model->item(row, 5)->text().toDouble();
        int limit       = model->item(row, 6)->text().toInt();

        // 可以改成数据库取真实资料和头像路径
        QString profile = name + " 医生，经验丰富，擅长临床诊断与治疗。";
        QString photoPath = ":/images/default_doctor.png";

        doctordetial dialog(this);
        dialog.setDoctorInfo(jobId, dep, name, profile, photoPath, workTime, fee, limit);
        dialog.exec();
    }
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
