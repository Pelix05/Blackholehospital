#include "appointmentlistpage.h"
#include "patientdetailpage.h"
#include "ui_appointmentlistpage.h"
#include "doctorwindow.h"
#include "databasemanager.h"

#include <QTableWidgetItem>
#include <QDate>


appointmentlistpage::appointmentlistpage(const QString doctorId, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::appointmentlistpage),
  m_doctorId(doctorId)
{
    ui->setupUi(this);
    this->setWindowTitle("APPOINTMENT LIST");
    this->setObjectName("appointmentListPage");

    QSqlQuery q;
       q.exec("INSERT OR IGNORE INTO patients (patient_id, name, id_card, phone, email, address, gender, dob) "
              "VALUES (1, 'Alice', 'P001', '13811110001', 'alice@example.com', 'Address A', 'F', '1990-01-01')");
       q.exec("INSERT OR IGNORE INTO patients (patient_id, name, id_card, phone, email, address, gender, dob) "
              "VALUES (2, 'Bob', 'P002', '13811110002', 'bob@example.com', 'Address B', 'M', '1985-02-02')");

       q.exec("INSERT OR IGNORE INTO doctors (doctor_id, name, id_card, phone, email, address, gender, dob) "
              "VALUES (456, 'Dr. Zhang', 'D001', '13800000001', 'zhang@example.com', 'Address 1', 'M', '1980-01-01')");
       q.exec("INSERT OR IGNORE INTO doctors (doctor_id, name, id_card, phone, email, address, gender, dob) "
              "VALUES (456, 'Dr. Li', 'D002', '13800000002', 'li@example.com', 'Address 2', 'F', '1985-02-02')");

       // Dummy appointments
       q.exec("INSERT OR IGNORE INTO appointments (appointment_id, patient_id, doctor_id, appoint_time, status) "
              "VALUES (1, 1, 456, '2025-09-03 09:00:00', 'booked')");
       q.exec("INSERT OR IGNORE INTO appointments (appointment_id, patient_id, doctor_id, appoint_time, status) "
              "VALUES (2, 2, 456, '2025-09-03 14:00:00', 'booked')");
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
                background-color: #ff0000;
                color: white;
                border: none;
                border-radius: 8px;
                padding: 10px 20px;
                font-weight: bold;
                min-height: 36px;
                font-size: 14px;
            }

            QPushButton#btnBack:hover {
                background-color: #8B0000;
            }

            QPushButton#btnBack:pressed {
                background-color: #8B0000;
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
    ui->tAppointment->clear();
       ui->tAppointment->setColumnCount(6);
       QStringList headers = {"NumberID", "Patient", "Time", "Status", "Contact", "Description"};
       ui->tAppointment->setHorizontalHeaderLabels(headers);

       // ambil dari DB
       QString today = QDate::currentDate().toString("yyyy-MM-dd");
       QList<QMap<QString, QVariant>> appointments = DatabaseManager::instance().getAppointmentsByDoctor();


       ui->tAppointment->setRowCount(appointments.size());

       for (int i = 0; i < appointments.size(); ++i) {
           auto record = appointments[i];

           int patientId = record["patient_id"].toInt();

           // 🔹 ambil info pasien
           QMap<QString, QVariant> patient = DatabaseManager::instance().getPatientInfoById(patientId);

           // 🔹 ambil diagnose terbaru dari medical_records
           QString diagnose = "";
           QList<QMap<QString, QVariant>> records = DatabaseManager::instance().getMedicalRecordsByPatient(patientId);
           if (!records.isEmpty()) {
               diagnose = records.first()["diagnose"].toString();
           }

           ui->tAppointment->setItem(i, 0, new QTableWidgetItem(QString::number(record["appointment_id"].toInt())));
           ui->tAppointment->setItem(i, 1, new QTableWidgetItem(patient["name"].toString()));
           ui->tAppointment->setItem(i, 2, new QTableWidgetItem(record["appoint_time"].toString()));
           ui->tAppointment->setItem(i, 3, new QTableWidgetItem(record["status"].toString()));
           ui->tAppointment->setItem(i, 4, new QTableWidgetItem(patient["phone"].toString()));
           ui->tAppointment->setItem(i, 5, new QTableWidgetItem(diagnose));
       }

       ui->tAppointment->hideColumn(0);
        connect(ui->tAppointment, &QTableWidget::cellClicked, this, &appointmentlistpage::onTableCellClicked);
}

void appointmentlistpage::onTableCellClicked(int row, int column)
{
    if(column == 5) { // description column
        QTableWidgetItem *idItem = ui->tAppointment->item(row, 0); // ambil numberID
        if(idItem) {
            QString numberId = idItem->text();

            // Buka patientinfo page sesuai numberID


            PatientDetailPage *patientdetailPage = new PatientDetailPage(numberId);
            patientdetailPage->show();


        }
    }
}

void appointmentlistpage::on_btnBack_clicked()
{
    this->hide();
}
