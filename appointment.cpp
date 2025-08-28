#include "appointment.h"
#include "ui_appointment.h"
#include <QSet>
#include <QMessageBox>
#include <QStandardItem>


appointment::appointment(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appointment),
    resultsModel(new QStandardItemModel(this))
{
    ui->setupUi(this);

    resultsModel->setHorizontalHeaderLabels({
        "工号", "姓名", "医院", "科室", "门诊", "坐诊时间", "支持预约", "上限", "已预约", "剩余"
       });

    ui->resultsView->setModel(resultsModel);      // link model to QTableView
    ui->resultsView->setSelectionBehavior(QAbstractItemView::SelectRows); // select row
    ui->resultsView->setSelectionMode(QAbstractItemView::SingleSelection);// select single

    loadTestDoctors();
    populateFilterChoices();                      // 从 doctors 提取医院/科室/门诊，填充下拉

    // 显式连接信号槽
    connect(ui->searchButton, &QPushButton::clicked,
            this, &appointment::searchclicked);
    connect(ui->bookButton,   &QPushButton::clicked,
            this, &appointment::bookclicked);
    connect(ui->backButton,   &QPushButton::clicked,
            this, &appointment::backclicked);

    // 设定时间控件
    ui->dateedit->setCalendarPopup(true);
    ui->dateedit->setDate(QDate::currentDate());

    ui->timeEdit->setDisplayFormat("HH:mm");
    ui->timeEdit->setTime(QTime::currentTime());

    //初次进入页面时，展示所有支持预约的医生
    searchclicked();
}

appointment::~appointment()
{
    delete ui;
}

void appointment::loadTestDoctors()
{

    doctors.append(Doctor{
        "1001", "张三", "第一人民医院", "内科", "消化内科",
        QTime(8, 0), QTime(12, 0), true, 10, 3
    });
    doctors.append(Doctor{
        "1002", "李四", "第一人民医院", "外科", "普外门诊",
        QTime(14, 0), QTime(18, 0), true, 8,  2
    });
    doctors.append(Doctor{
        "1003", "王五", "第二附属医院", "内科", "呼吸内科",
        QTime(9, 30), QTime(11, 30), false, 12, 0
    });
    doctors.append(Doctor{
        "1004", "赵六", "第二附属医院", "骨科", "关节门诊",
        QTime(9, 0), QTime(12, 0), true, 6, 6
    });
}

void appointment::populateFilterChoices()     // 根据 doctors 动态填充下拉框
{
    QSet<QString> hospitals;                      // 使用 QSet 去重
    QSet<QString> departments;
    QSet<QString> clinics;

    for (const Doctor &d : doctors) {             // 基于范围 for 遍历 QVector
        hospitals.insert(d.hospital);
        departments.insert(d.department);
        clinics.insert(d.clinic);
    }

    ui->hospitalCombo->clear();                   // 先清空，再添加“全部”+选项
    ui->hospitalCombo->addItem("全部");
    for (const QString &h : hospitals) ui->hospitalCombo->addItem(h);

    ui->departmentCombo->clear();
    ui->departmentCombo->addItem("全部");
    for (const QString &d : departments) ui->departmentCombo->addItem(d);

    ui->clinicCombo->clear();
    ui->clinicCombo->addItem("全部");
    for (const QString &c : clinics) ui->clinicCombo->addItem(c);
}

bool appointment::timeWithinShift(const Doctor &d, const QTime &t) const
{
    // 判定 t 是否在 [shiftStart, shiftEnd] 区间（含端点）
    return (t >= d.shiftStart && t <= d.shiftEnd);
}

void appointment::searchclicked()           // 点击“搜索”后执行过滤
{
    //读取筛选条件
    const QString hSel = ui->hospitalCombo->currentText();
    const QString dSel = ui->departmentCombo->currentText();
    const QString cSel = ui->clinicCombo->currentText();
    const QDate date = ui->dateedit->date();
    const QTime time = ui->timeEdit->time();
    // 拼成完整时间点
    QDateTime dt(date, time);
    const QTime     t  = dt.time();

    QList<int> hitIndexes;                                     // 保存命中的 doctors 下标

    // 遍历 doctors 做多条件匹配
    for (int i = 0; i < doctors.size(); ++i) {
        const Doctor &d = doctors[i];
        //医院/科室/门诊三项：为“全部”时不限制，否则必须全等
        const bool hospitalOK   = (hSel == "全部" || d.hospital   == hSel);
        const bool departmentOK = (dSel == "全部" || d.department == dSel);
        const bool clinicOK     = (cSel == "全部" || d.clinic     == cSel);
        //是否支持预约 + 时间是否匹配（注意只比对时分）
        const bool supportOK    = d.supportsAppointment;
        const bool timeOK       = timeWithinShift(d, t);

        if (hospitalOK && departmentOK && clinicOK && supportOK && timeOK) {
            hitIndexes.append(i);
        }
    }

    //用命中的索引重建表格
    refillResults(hitIndexes);
}

void appointment::refillResults(const QList<int> &indexes)
{
    resultsModel->removeRows(0, resultsModel->rowCount());      //清空旧数据

    for (int idx : indexes) {
        const Doctor &d = doctors[idx];
        const int row = resultsModel->rowCount();
        resultsModel->insertRow(row);

        const int remain = std::max(0, d.limitPerDay - d.booked);

        //逐列设置单元格（new QStandardItem(text)）
        resultsModel->setItem(row, 0, new QStandardItem(d.jobId));
        resultsModel->setItem(row, 1, new QStandardItem(d.name));
        resultsModel->setItem(row, 2, new QStandardItem(d.hospital));
        resultsModel->setItem(row, 3, new QStandardItem(d.department));
        resultsModel->setItem(row, 4, new QStandardItem(d.clinic));
        //坐诊时间段组合
        resultsModel->setItem(row, 5, new QStandardItem(
            d.shiftStart.toString("HH:mm") + "-" + d.shiftEnd.toString("HH:mm")
        ));
        resultsModel->setItem(row, 6, new QStandardItem(d.supportsAppointment ? "是" : "否"));
        resultsModel->setItem(row, 7, new QStandardItem(QString::number(d.limitPerDay)));
        resultsModel->setItem(row, 8, new QStandardItem(QString::number(d.booked)));
        resultsModel->setItem(row, 9, new QStandardItem(QString::number(remain)));

        // 在某列埋入源索引，方便“预约”时反查 doctors
        resultsModel->item(row, 0)->setData(idx, Qt::UserRole); // UserRole 保存原索引
    }

    ui->resultsView->resizeColumnsToContents();                 // 列宽自适应（可选）
}

void appointment::bookclicked()
{
    //获取当前选中行
    auto sel = ui->resultsView->selectionModel();
    if (!sel || !sel->hasSelection()) {
        QMessageBox::warning(this, "提示", "请先在结果中选择一位医生");
        return;
    }
    const QModelIndex cur = sel->currentIndex();
    const int row = cur.row();

    //从第 0 列取回我们埋的源索引
    const int srcIdx = resultsModel->item(row, 0)->data(Qt::UserRole).toInt();

    //检查剩余号源
    Doctor &d = doctors[srcIdx];
    const int remain = d.limitPerDay - d.booked;
    if (remain <= 0) {
        QMessageBox::information(this, "提示", "该医生今日已无可预约号");
        return;
    }

    // 扣减号源并更新 UI
    d.booked += 1;
    resultsModel->setItem(row, 8, new QStandardItem(QString::number(d.booked)));
    resultsModel->setItem(row, 9, new QStandardItem(QString::number(d.limitPerDay - d.booked)));


    const QDateTime dt(ui->dateedit->date(), ui->timeEdit->time());
    const QString when = dt.toString("yyyy-MM-dd HH:mm");
    QMessageBox::information(this, "预约成功",
        QString("已为您预约 %1（工号%2）\n就诊时间：%3")
            .arg(d.name).arg(d.jobId).arg(when));

}

void appointment::backclicked()
{
    emit backRequested();
}
