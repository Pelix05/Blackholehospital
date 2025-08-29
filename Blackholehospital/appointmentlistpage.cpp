#include "appointmentlistpage.h"
#include "ui_appointmentlistpage.h"
#include <QTableWidgetItem>

appointmentlistpage::appointmentlistpage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appointmentlistpage)
{
    ui->setupUi(this);
    this->setWindowTitle("APPOINTMENT LIST");
    this->setObjectName("appointmentListPage");
        ui->tAppointment->setObjectName("appointmentTable");
        ui->btnBack->setObjectName("btnBack");

        // Apply stylesheet
        this->setStyleSheet(R"(
            /* === Main window background === */
            #appointmentListPage {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                            stop:0 #e6f7ff, stop:1 #ffffff);
                font-family: "Segoe UI";
                font-size: 14px;
                color: #333;
            }

            /* === Title label === */
            QLabel {
                font-weight: bold;
                color: #222;
                font-size: 16px;
            }

            /* === Table styling === */
            QTableWidget#appointmentTable {
                background-color: white;
                border: 4px solid #0078d7;
                border-radius: 12px;
                gridline-color: #ddd;
                alternate-background-color: #f8f9fa;
            }

            QTableWidget#appointmentTable::item {
                padding: 8px;
                border-bottom: 2px solid #eee;
            }

            QTableWidget#appointmentTable::item:selected {
                background-color: #0078d7;
                color: white;
            }
                            QTableWidget#appointmentTable::item:selected {
                                background-color: #0078d7;
                                color: white;
                            }

            QTableWidget#appointmentTable QHeaderView::section {
                background-color: #0078d7;
                color: white;
                font-weight: bold;
                padding: 10px;
                border: none;
            }
                            QTableWidget#appointmentTable QTableCornerButton::section {
                                background-color: #0066cc;
                                color: white;
                                font-weight: bold;
                                padding: 10px;
                                border: none;

                            }

            /* === Back button === */
            QPushButton#btnBack {
                background-color: #0078d7;
                color: white;
                border: none;
                border-radius: 8px;
                padding: 10px 20px;
                font-weight: bold;
                min-height: 36px;
                font-size: 14px;
            }

            QPushButton#btnBack:hover {
                background-color: #005fa3;
            }

            QPushButton#btnBack:pressed {
                background-color: #004578;
            }
        )");

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
