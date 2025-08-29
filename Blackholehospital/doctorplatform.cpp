#include "doctorplatform.h"
#include "ui_doctorplatform.h"

doctorplatform::doctorplatform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::doctorplatform)
{
    this->setWindowTitle("DOCTOR'S PLATFORM");

    // Add doctors to the list
        QStringList doctors = {"张医生(内科)", "李医生(外科)", "王医生(儿科)", "赵医生(眼科)"};
        ui->listDoctors->addItems(doctors);

        // Connect signals and slots
        connect(ui->btnSend, &QPushButton::clicked, this, &doctorplatform::onSendMessageClicked);
        connect(ui->listDoctors, &QListWidget::itemClicked, this, &doctorplatform::onDoctorSelected);
        connect(ui->btnBack, &QPushButton::clicked, this, &doctorplatform::onBackClicked);
    }

    doctorplatform::~doctorplatform()
    {
        delete ui;
    }

    void doctorplatform::onSendMessageClicked()
    {
        QString message = ui->leMessegeInput->text();
        if(!message.isEmpty()) {
            ui->chatDisplay->append("我: " + message);
            ui->leMessegeInput->clear();
        }
    }

    void doctorplatform::onDoctorSelected()
    {
        QListWidgetItem *item = ui->listDoctors->currentItem();
        if(item) {
            QString doctorName = item->text();
            ui->chatDisplay->clear();
            ui->chatDisplay->append("开始与 " + doctorName + " 对话");
        }
    }

    void doctorplatform::onBackClicked()
    {
        emit backButtonClicked();  // Emit signal untuk kembali
    }
