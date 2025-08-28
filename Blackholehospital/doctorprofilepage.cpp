#include "doctorprofilepage.h"
#include "ui_doctorprofilepage.h"

#include <QFileDialog>
#include <QPixmap>

doctorprofilepage::doctorprofilepage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctorprofilepage)
{
    ui->setupUi(this);
    // Connect signals and slots
        connect(ui->btnExit, &QPushButton::clicked, this, &doctorprofilepage::onCloseButtonClicked);
        connect(ui->btnChangePhoto, &QPushButton::clicked, this, &doctorprofilepage::onChangePhotoClicked);

        // Set initial values
        ui->dteWorkTime->setDateTime(QDateTime::currentDateTime());
        ui->dsbFee->setMaximum(9999);
        ui->sbDailyLimit->setMaximum(100);

        // Set initial photo
        ui->lPhoto->setPixmap(QPixmap(":/images/doctor.png").scaled(100, 100,
            Qt::KeepAspectRatio, Qt::SmoothTransformation));
    }

    doctorprofilepage::~doctorprofilepage()
    {
        delete ui;
    }

    void doctorprofilepage::onCloseButtonClicked()
    {
        this->close();
    }

    void doctorprofilepage::onChangePhotoClicked()
    {
        QString file = QFileDialog::getOpenFileName(this, "选择照片", "", "Images (*.png *.jpg *.bmp)");
        if (!file.isEmpty()) {
            ui->lPhoto->setPixmap(QPixmap(file).scaled(100, 100,
                Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
    }
