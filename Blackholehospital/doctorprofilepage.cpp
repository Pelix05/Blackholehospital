#include "doctorprofilepage.h"
#include "ui_doctorprofilepage.h"
#include "databasemanager.h"
#include <QFileDialog>
#include <QPixmap>
#include <QMessageBox>


doctorprofilepage::doctorprofilepage(const QString &doctorId) :

    ui(new Ui::doctorprofilepage)
{
    ui->setupUi(this);
    this->setWindowTitle("DOCTOR'S PROFILE");

    this->setStyleSheet(R"(
        /* === Root background (gradient) === */
        background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                    stop:0 #e6f7ff, stop:1 #ffffff);
        font-family: "Segoe UI";
        font-size: 14px;
        color: #333;
        }

        QLabel {
            font-weight: bold;
            color: #222;
        }

        /* === Inputs: bikin tinggi fix & nyaman === */
        QLineEdit, QDateTimeEdit, QSpinBox, QDoubleSpinBox {
            border: 1px solid #aaa;
            border-radius: 6px;
            padding: 6px 10px;
            background: #ffffff;
            min-height: 34px;            /* <- ini yang bikin gak gepeng */
        }
        QLineEdit:focus, QDateTimeEdit:focus, QSpinBox:focus, QDoubleSpinBox:focus {
            border: 2px solid #0078d7;
            background: #eef6ff;
        }

        /* tombol umum */
        QPushButton {
            background-color: #0078d7;
            color: #fff;
            border: none;
            border-radius: 8px;
            padding: 8px 14px;
            font-weight: bold;
            min-height: 34px;
        }
        QPushButton:hover   { background-color: #005fa3; }
        QPushButton:pressed { background-color: #004578; }

        /* tombol spesifik */
        QPushButton#btnChangePhoto { background-color: #5cb85c; }
        QPushButton#btnChangePhoto:hover { background-color: #4cae4c; }

        QPushButton#btnExit { background-color: #d9534f; }
        QPushButton#btnExit:hover { background-color: #c9302c; }

        QPushButton#btnSave { background-color: #27ae60; }         /* tombol Save hijau */
        QPushButton#btnSave:hover { background-color: #1e8f4d; }

        /* optional: card/frame pembungkus form */
        QFrame#frame {
            background: #e6f7ff;
            border: 2px solid #0078d7;
            border-radius: 12px;
            padding: 12px;
        }

        /* label judul besar (kalau ada lTitle) */
        QLabel#lTitle {
            font-size: 20px;
            font-weight: 800;
            color: #2C3E50;
            padding: 6px 0;
            border-bottom: 2px solid #0078d7;
        }
    )");
    // Style for radio buttons
    QString radioStyle = R"(
        QRadioButton {
            spacing: 8px;
            font-size: 15px;
            color: #333333;
            font-weight: 500;
            background: transparent;
        }

        QRadioButton::indicator {
            width: 20px;
            height: 20px;
            border-radius: 10px;   /* Make it circular */
            border: 2px solid #cccccc;
            background: #f8f9fa;
        }

        QRadioButton::indicator:hover {
            border: 2px solid #0066cc;
            background: #e6f7ff;
        }

        QRadioButton::indicator:checked {
            border: 2px solid #0066cc;
            background: #0066cc;
        }

        QRadioButton::indicator:checked:hover {
            background: #0052a3;
            border: 2px solid #0052a3;
        }

        QRadioButton:disabled {
            color: #aaaaaa;
        }

        QRadioButton::indicator:disabled {
            border: 2px solid #cccccc;
            background: #e9ecef;
        }
    )";
    ui->rbMale->setStyleSheet(radioStyle);
    ui->rbFemale->setStyleSheet(radioStyle);

    // Connect signals and slots
        connect(ui->btnExit, &QPushButton::clicked, this, &doctorprofilepage::onCloseButtonClicked);
        connect(ui->btnChangePhoto, &QPushButton::clicked, this, &doctorprofilepage::onChangePhotoClicked);
        connect(ui->btnSave, &QPushButton::clicked, this, &doctorprofilepage::onSaveButtonClicked);


        // Set initial values
        ui->dsbFee->setMaximum(9999);
        ui->sbDailyLimit->setMaximum(100);

        // Set initial photo
        ui->lPhoto->setPixmap(QPixmap(":/images/doctor.png").scaled(100, 100,
            Qt::KeepAspectRatio, Qt::SmoothTransformation));

        loadDoctorData(doctorId);
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
        QString file = QFileDialog::getOpenFileName(this, "Select a photo :", "", "Images (*.png *.jpg *.bmp)");
        if (!file.isEmpty()) {
            // Copy ke folder proyek
            QString targetPath = QCoreApplication::applicationDirPath() + "/photos/" + QFileInfo(file).fileName();
            if (!QFile::exists(targetPath)) {
                QFile::copy(file, targetPath);
            }

            ui->lPhoto->setPixmap(QPixmap(targetPath).scaled(100, 100,
                        Qt::KeepAspectRatio, Qt::SmoothTransformation));
            currentPhotoPath = targetPath;
        }
    }


    void doctorprofilepage::loadDoctorData(const QString &doctorId)
    {
        DatabaseManager &db = DatabaseManager::instance();
        QMap<QString, QVariant> info = db.getDoctorInfo(doctorId); // pastikan doctorId int di DB

        if (info.isEmpty()) return; // kalau ga ada data

        // Isi ke field
        ui->leUsername->setText(info.value("name").toString());
        ui->leEmail->setText(info.value("email").toString());
        ui->lePhone->setText(info.value("phone").toString());
        ui->leBirthDate->setText(info.value("birth_date").toString());
        ui->leUserId->setText(info.value("id_card").toString());
        ui->leDepartment->setText(info.value("department").toString());
        ui->leAddress->setText(info.value("address").toString());

        // Jika ada gender
        QString gender = info.value("gender").toString();
        if (gender == "M") ui->rbMale->setChecked(true);
        else if (gender == "F") ui->rbFemale->setChecked(true);

        // Photo
        QString photoPath = info.value("photo").toString();
            if (!photoPath.isEmpty()) {
                ui->lPhoto->setPixmap(QPixmap(photoPath).scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
                currentPhotoPath = photoPath;  // simpan path foto saat load
            }
        if (info.contains("fee"))
                ui->dsbFee->setValue(info.value("fee").toDouble());

            if (info.contains("daily_limit"))
                ui->sbDailyLimit->setValue(info.value("daily_limit").toInt());
    }

    void doctorprofilepage::onSaveButtonClicked()
    {
        QString name       = ui->leUsername->text();
        QString email      = ui->leEmail->text();
        QString phone      = ui->lePhone->text();
        QString birthDate  = ui->leBirthDate->text();
        QString idCard     = ui->leUserId->text();
        QString department = ui->leDepartment->text();
        QString address    = ui->leAddress->text();
        QString gender     = ui->rbMale->isChecked() ? "M" : "F";
        double fee = ui->dsbFee->value();
        int dailyLimit = ui->sbDailyLimit->value();


        QString photoPath = currentPhotoPath;

        DatabaseManager &db = DatabaseManager::instance();
        bool success = db.updateDoctor(idCard, name, email, phone, birthDate, department, address, gender, photoPath, fee, dailyLimit);
        qDebug() << "Binding values:";
        qDebug() << ":name" << name;
        qDebug() << ":email" << email;
        qDebug() << ":phone" << phone;
        qDebug() << ":birthDate" << birthDate;
        qDebug() << ":department" << department;
        qDebug() << ":address" << address;
        qDebug() << ":gender" << gender;
        qDebug() << ":photo" << photoPath;
        qDebug() << ":idCard" << idCard;


        if(success) {
            QMessageBox::information(this, "Success", "Profile updated successfully!");
        } else {
            QMessageBox::critical(this, "Error", "Failed to update profile.");
        }
    }



