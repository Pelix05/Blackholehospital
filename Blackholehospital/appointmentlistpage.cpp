#include "appointmentlistpage.h"
#include "ui_appointmentlistpage.h"
#include <QTableWidgetItem>

appointmentlistpage::appointmentlistpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appointmentlistpage)
{
    ui->setupUi(this);
    populateAppointmentData();

    connect(ui->btnBack, &QPushButton::clicked, this, &appointmentlistpage::on_btnBack_clicked);

}

appointmentlistpage::~appointmentlistpage()
{
    delete ui;
}

void appointmentlistpage::populateAppointmentData()
{
    // Sample data - in real application, this would come from a database
    QStringList patients = {"张三", "李四", "王五", "赵六"};
    QStringList times = {"2023-10-15 09:00", "2023-10-15 10:30", "2023-10-15 14:00", "2023-10-16 11:00"};
    QStringList statuses = {"待就诊", "已就诊", "已取消", "待就诊"};
    QStringList contacts = {"13800138000", "13900139000", "13700137000", "13600136000"};
    QStringList descriptions = {"感冒发烧", "肠胃不适", "腰背疼痛", "年度体检"};

    ui->tAppointment->setRowCount(patients.size());

    for(int i = 0; i < patients.size(); ++i) {
        ui->tAppointment->setItem(i, 0, new QTableWidgetItem(patients[i]));
        ui->tAppointment->setItem(i, 1, new QTableWidgetItem(times[i]));
        ui->tAppointment->setItem(i, 2, new QTableWidgetItem(statuses[i]));
        ui->tAppointment->setItem(i, 3, new QTableWidgetItem(contacts[i]));
        ui->tAppointment->setItem(i, 4, new QTableWidgetItem(descriptions[i]));
    }
}

void appointmentlistpage::on_btnBack_clicked()
{
    emit backToDoctor();
}
