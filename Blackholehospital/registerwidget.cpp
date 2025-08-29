#include "registerwidget.h"
#include "ui_registerwidget.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

RegisterWidget::RegisterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("REGISTER");


    // Set window properties
    setWindowTitle("Register - Medical System");
    setFixedSize(1900, 900);

    ui->cbRole->addItem("Patient");
    ui->cbRole->addItem("Doctor");

    QPixmap logo(":/images/medical_logo.png");
        QLabel *logoLabel = new QLabel(this);
        logoLabel->setPixmap(logo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        logoLabel->setAlignment(Qt::AlignLeft);
        logoLabel->setAttribute(Qt::WA_TranslucentBackground);
        logoLabel->setStyleSheet("background: transparent;");
        logoLabel->setGeometry(900, 40, 100, 100); // Posisi dan ukuran



        // ===== TAMBAHAN STYLE SHEET =====
            // Style untuk latar belakang window
            this->setStyleSheet("background-color: qlineargradient(x1: 0, y1: 0, x2: 1, y2: 1, stop: 0 #e6f7ff, stop: 1 #ffffff);");

            // Style untuk judul
            ui->labelTitle->setStyleSheet("QLabel {"
                                         "color: #0066cc;"
                                         "font-size: 30px;"
                                         "font-weight: bold;"
                                         "background-color: transparent;"
                                         "}");

            ui->btnRegister->setStyleSheet("QPushButton {"
                                          "background-color: #4CAF50;"
                                          "color: white;"
                                          "border-radius: 10px;"
                                          "padding: 8px;"
                                          "font-size: 16px;"
                                          "}"
                                          "QPushButton:hover {"
                                          "background-color: #45a049;"
                                          "}");
            ui->btnBack->setStyleSheet("QPushButton {"
                                          "background-color: #FF0000;"
                                          "color: white;"
                                          "border-radius: 10px;"
                                          "padding: 8px;"
                                          "font-size: 16px;"
                                          "}"
                                          "QPushButton:hover {"
                                          "background-color: #8B0000;"
                                          "}");


            // Style untuk line edit
            QString lineEditStyle = "QLineEdit {"
                                   "border: 2px solid #cccccc;"
                                   "border-radius: 8px;"
                                   "padding: 9px;"
                                   "font-size: 16px;"
                                   "background-color: white;"
                                   "}"
                                   "QLineEdit:focus {"
                                   "border: 2px solid #0066cc;"
                                   "}";

            ui->leUsername->setStyleSheet(lineEditStyle);
            ui->leUserId->setStyleSheet(lineEditStyle);
            ui->lePassword->setStyleSheet(lineEditStyle);
            ui->leEmail->setStyleSheet(lineEditStyle);
            ui->lePhone->setStyleSheet(lineEditStyle);
            ui->leConfirmPassword->setStyleSheet(lineEditStyle);

            // Style untuk combo box
            ui->cbRole->setStyleSheet(
                    "QComboBox {"
                    "   background-color: #f8f9fa;"
                    "   border: 3px solid #d0d0d0;"
                    "   border-radius: 8px;"
                    "   padding: 5px;"
                    "   font-size: 14px;"
                    "   color: #333333;"
                    "   margin-bottom: 1px;"
                    "   min-width: 15em;"
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

            ui->cbAgree->setStyleSheet(
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

    // Connect buttons to functions
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterWidget::on_btnRegister_clicked);
    connect(ui->btnBack, &QPushButton::clicked, this, &RegisterWidget::on_btnBack_clicked);
}

void RegisterWidget::on_btnRegister_clicked()
{
    // Ambil data dari form
    QString username = ui->leUsername->text();
    QString userid = ui->leUserId->text();
    QString email = ui->leEmail->text();
    QString phone = ui->lePhone->text();
    QString password = ui->lePassword->text();
    QString confirmPassword = ui->leConfirmPassword->text();
    QString role = ui->cbRole->currentText();
    // Validasi input
    if (username.isEmpty() || email.isEmpty() || phone.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Please fill all the information above!");
        return;
    }

    if (!ui->cbAgree->isChecked()) {
        QMessageBox::warning(this, "Error", "You have to agree the terms and conditions!");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Password dan Confirm Password doesn't match!");
        return;
    }

    // Validasi email format
    QRegularExpression emailRegex(R"(\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}\b)",
                                 QRegularExpression::CaseInsensitiveOption);
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Error", "Wrong email format!");
        return;
    }

    // Validasi phone number (minimal 10 digit)
    if (phone.length() < 10) {
        QMessageBox::warning(this, "Error", "Phone number min 10 digit!");
        return;
    }

    // Jika semua validasi passed
    qDebug() << "Register successful:";
    qDebug() << "Name:" << username;
    qDebug() << "Name:" << userid;
    qDebug() << "Email:" << email;
    qDebug() << "Phone:" << phone;
    qDebug() << "Role:" << role;

    QMessageBox::information(this, "Success", "Registrasi Success!");
    emit backToLogin();  // Kembali ke login
}

void RegisterWidget::on_btnBack_clicked()
{
    emit backToLogin();  // Kirim signal untuk kembali ke login
}

QString RegisterWidget::getSelectedRole() const
{
    return ui->cbRole->currentText();
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}
