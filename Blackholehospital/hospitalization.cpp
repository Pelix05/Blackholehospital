#include "hospitalization.h"
#include "ui_hospitalization.h"

hospitalization::hospitalization(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::hospitalization)
{
    ui->setupUi(this);
    this->setWindowTitle("HOSPITALIZED INFO");

    this->setStyleSheet(R"(

            QDialog {
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

            /* Label judul (Doctor:, Room:, dll.) */
            QLabel[data-label="title"] {
                font-weight: bold;
                color: #555;
            }

            /* Label isi data */
            QLabel[data-label="value"] {
                background-color: #ffffff;
                border: 1px solid #ddd;
                border-radius: 8px;
                padding: 4px 8px;
            }

            QPushButton {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                            stop:0 #4facfe, stop:1 #00f2fe);
                color: white;
                border: none;
                border-radius: 10px;
                padding: 8px 16px;
                font-size: 14px;
            }

            QPushButton:hover {
                background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                                            stop:0 #00f2fe, stop:1 #4facfe);
            }

            QPushButton:pressed {
                background-color: #0078d7;
            }

        )");
    ui->lMainDoctor->setProperty("data-label", "title");
    ui->lRoom->setProperty("data-label", "title");
    ui->lBedNo->setProperty("data-label", "title");
    ui->lbHospitalized->setProperty("data-label", "title");

    ui->lblDoctor->setProperty("data-label", "value");
    ui->lblRoom->setProperty("data-label", "value");
    ui->lblBed->setProperty("data-label", "value");
    ui->lblAdmissionDate->setProperty("data-label", "value");


}

hospitalization::~hospitalization()
{
    delete ui;
}

void hospitalization::setHospitalizationInfo(const HospitalizationInfo &info)
{
    currentInfo = info;

    ui->lblDoctor->setText(info.doctor);
    ui->lblRoom->setText(info.room);
    ui->lblBed->setText(info.bed);
    ui->lblAdmissionDate->setText(info.admissionDate);
}
