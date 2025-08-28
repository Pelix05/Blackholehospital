#include "loginwidget.h"
#include "ui_loginwidget.h"
#include "patientmainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QPixmap>
#include <QLabel>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    registerWidget(nullptr),  // Initialize pointer ke nullptr
    forgotPasswordWidget(nullptr)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Medical System Login");
    setFixedSize(1900, 850);

    QPixmap logo(":/images/medical_logo.png");
        QLabel *logoLabel = new QLabel(this);
        logoLabel->setPixmap(logo.scaled(300, 300, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        logoLabel->setAlignment(Qt::AlignLeft);
        logoLabel->setAttribute(Qt::WA_TranslucentBackground);
        logoLabel->setStyleSheet("background: transparent;");
        logoLabel->setGeometry(250, 300, 300, 300); // Posisi dan ukuran

    ui->cbRole->addItem("Patient");
    ui->cbRole->addItem("Doctor");

    // ===== TAMBAHAN STYLE SHEET =====
        // Style untuk latar belakang window
        this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #e6f7ff, stop: 1 #ffffff);");

        // Style untuk judul
        ui->labelTitle->setStyleSheet("QLabel {"
                                     "color: #0066cc;"
                                     "font-size: 28px;"
                                     "font-weight: bold;"
                                     "background-color: transparent;"
                                     "}");

        // Style untuk tombol login
        ui->btnLogin->setStyleSheet("QPushButton {"
                                   "background-color: #0066cc;"
                                   "color: white;"
                                   "border-radius: 10px;"
                                   "padding: 12px;"
                                   "font-size: 16px;"
                                   "font-weight: bold;"
                                   "}"
                                   "QPushButton:hover {"
                                   "background-color: #0052a3;"
                                   "}"
                                   "QPushButton:pressed {"
                                   "background-color: #003d7a;"
                                   "}");

        // Style untuk tombol register
        ui->btnRegister->setStyleSheet("QPushButton {"
                                      "background-color: #4CAF50;"
                                      "color: white;"
                                      "border-radius: 10px;"
                                      "padding: 12px;"
                                      "font-size: 16px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #45a049;"
                                      "}");

        // Style untuk tombol lupa password
        ui->btnForgot->setStyleSheet("QPushButton {"
                                    "background-color: transparent;"
                                    "color: #0066cc;"
                                    "text-decoration: underline;"
                                    "border: none;"
                                    "}"
                                    "QPushButton:hover {"
                                    "color: #004080;"
                                    "}");
        ui->cbRole->setStyleSheet(
                "QComboBox {"
                "   background-color: #f8f9fa;"
                "   border: 2px solid #d0d0d0;"
                "   border-radius: 8px;"
                "   padding: 12px;"
                "   font-size: 14px;"
                "   color: #333333;"
                "   margin-bottom: 10px;"
                "   min-width: 10em;"
                "}"
                "QComboBox:focus {"
                "   border: 2px solid #0066cc;"
                "   background-color: #ffffff;"
                "}"
                "QComboBox:hover {"
                "   border: 2px solid #a0a0a0;"
                "}"
                "QComboBox QAbstractItemView {"
                "   border: 2px solid #d0d0d0;"
                "   border-radius: 8px;"
                "   background-color: white;"
                "   selection-background-color: #0066cc;"
                "   selection-color: white;"
                "}"
            );


        // Style untuk line edit
        QString lineEditStyle = "QLineEdit {"
                               "border: 2px solid #cccccc;"
                               "border-radius: 8px;"
                               "padding: 8px;"
                               "font-size: 16px;"
                               "background-color: white;"
                               "}"
                               "QLineEdit:focus {"
                               "border: 2px solid #0066cc;"
                               "}";

        ui->leUserId->setStyleSheet(lineEditStyle);
        ui->lePassword->setStyleSheet(lineEditStyle);

        // Style untuk combo box
        ui->cbRole->setStyleSheet(
                "QComboBox {"
                "   background-color: #f8f9fa;"
                "   border: 3px solid #d0d0d0;"
                "   border-radius: 8px;"
                "   padding: 9px;"
                "   font-size: 14px;"
                "   color: #333333;"
                "   margin-bottom: 8px;"
                "   min-width: 10em;"
                "}"
                "QComboBox:focus {"
                "   border: 2px solid #0066cc;"
                "   background-color: #ffffff;"
                "}"
                "QComboBox:hover {"
                "   border: 2px solid #a0a0a0;"
                "}"
                "QComboBox QAbstractItemView {"
                "   border: 2px solid #d0d0d0;"
                "   border-radius: 8px;"
                "   background-color: white;"
                "   selection-background-color: #0066cc;"
                "   selection-color: white;"
                "}"
            );

        ui->cbRememberMe->setStyleSheet(
                "QCheckBox {"
                "   spacing: 8px;"
                "   font-size: 13px;"
                "   color: #555555;"
                "   margin: 10px 0px;"
                "}"
                "QCheckBox::indicator {"
                "   width: 18px;"
                "   height: 18px;"
                "   border: 2px solid #d0d0d0;"
                "   border-radius: 4px;"
                "   background-color: #f8f9fa;"
                "}"
                "QCheckBox::indicator:hover {"
                "   border: 2px solid #a0a0a0;"
                "}"
                "QCheckBox::indicator:checked {"
                "   background-color: #0066cc;"
                "   border: 2px solid #0066cc;"
                "   image: url(:/images/checkmark.png);"
                "}"
                "QCheckBox::indicator:checked:hover {"
                "   background-color: #0052a3;"
                "   border: 2px solid #0052a3;"
                "}"
                "QCheckBox::indicator:disabled {"
                "   background-color: #e9ecef;"
                "   border: 2px solid #cccccc;"
                "}"
            );

        // ===== END STYLE SHEET =====

    // Connect buttons
    connect(ui->btnRegister, &QPushButton::clicked, this, &LoginWidget::on_btnRegister_clicked);
    connect(ui->btnForgot, &QPushButton::clicked, this, &LoginWidget::on_btnForgot_clicked);
}

void LoginWidget::on_btnLogin_clicked()
{
    QString userid = ui->leUserId->text();
    QString password = ui->lePassword->text();
    QString role = ui->cbRole->currentText();
    if (userid.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "UserID dan password cannot be empty!");
        return;
    }

    qDebug() << "Login attempt - UserID:" << userid << "Password:" << password;
    if (role == "Patient") {
            patientmainwindow *pmw = new patientmainwindow();
            pmw->show();
            this->close();   // Tutup login window
        }
        else {
            QMessageBox::warning(this, "Error", "Invalid role selected!");
        }
}

void LoginWidget::on_btnRegister_clicked()
{
    // Buat register window jika belum ada
    if (!registerWidget) {
        registerWidget = new RegisterWidget();

        // Connect signal dari register window
        connect(registerWidget, &RegisterWidget::backToLogin, this, [this]() {
            this->show();                   // Tampilkan login window
            registerWidget->hide();         // Sembunyikan register window
        });
    }

    this->hide();           // Sembunyikan login window
    registerWidget->show(); // Tampilkan register window
    registerWidget->raise();
    registerWidget->activateWindow();
}

void LoginWidget::on_btnForgot_clicked()
{
    // Buat forgot password window jika belum ada
    if (!forgotPasswordWidget) {
        forgotPasswordWidget = new ForgotPasswordWidget();

        // Connect signal dari forgot password window
        connect(forgotPasswordWidget, &ForgotPasswordWidget::backToLogin, this, [this]() {
            this->show();                           // Tampilkan login window
            forgotPasswordWidget->hide();           // Sembunyikan forgot password window
        });
    }

    this->hide();                   // Sembunyikan login window
    forgotPasswordWidget->show();   // Tampilkan forgot password window
    forgotPasswordWidget->raise();
    forgotPasswordWidget->activateWindow();
}

QString LoginWidget::getSelectedRole() const
{
    return ui->cbRole->currentText();
}

LoginWidget::~LoginWidget()
{
    delete ui;
    if (registerWidget) {
        delete registerWidget;  // Hapus register widget jika ada
    }
    if (forgotPasswordWidget) {
        delete forgotPasswordWidget;  // Hapus forgot password widget jika ada
    }
}
