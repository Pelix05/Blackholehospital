#include "forgotpasswordwidget.h"
#include "ui_forgotpasswordwidget.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlError>


ForgotPasswordWidget::ForgotPasswordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPasswordWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("FORGOT PASSWORD");


    // Set window properties
    setWindowTitle("Reset Password - Medical System");
    setFixedSize(1900, 900);
    QPixmap logo(":/images/medical_logo.png");
        QLabel *logoLabel = new QLabel(this);
        logoLabel->setPixmap(logo.scaled(100, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        logoLabel->setAlignment(Qt::AlignLeft);
        logoLabel->setAttribute(Qt::WA_TranslucentBackground);
        logoLabel->setStyleSheet("background: transparent;");
        logoLabel->setGeometry(900, 30, 100, 100); // Posisi dan ukuran

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


        ui->frame->setStyleSheet(
                "QFrame {"
                "   background-color: #e6f7ff;"
                "   border: 2px solid #d0d0d0;"
                "   border-radius: 15px;"
                "   padding: 25px;"
                "}"
            );

        ui->btnResetPassword->setStyleSheet("QPushButton {"
                                      "background-color: #4CAF50;"
                                      "color: white;"
                                      "border-radius: 10px;"
                                      "padding: 15px;"
                                      "font-size: 16px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #45a049;"
                                      "}");

        ui->btnBack->setStyleSheet("QPushButton {"
                                      "background-color: #FF0000;"
                                      "color: white;"
                                      "border-radius: 10px;"
                                      "padding: 15px;"
                                      "font-size: 16px;"
                                      "}"
                                      "QPushButton:hover {"
                                      "background-color: #8B0000;"
                                      "}");


        // Style untuk line edit
        QString lineEditStyle = "QLineEdit {"
                               "border: 2px solid #cccccc;"
                               "border-radius: 8px;"
                               "padding: 12px;"
                               "font-size: 16px;"
                               "background-color: white;"
                               "}"
                               "QLineEdit:focus {"
                               "border: 2px solid #0066cc;"
                               "}";
        ui->leEmail->setStyleSheet(lineEditStyle);
        ui->leNewPassword->setStyleSheet(lineEditStyle);
        ui->leConfirmNewPassword->setStyleSheet(lineEditStyle);





        // ===== END STYLE SHEET =====

    // Connect buttons to functions
    connect(ui->btnResetPassword, &QPushButton::clicked, this, &ForgotPasswordWidget::on_btnResetPassword_clicked);
    connect(ui->btnBack, &QPushButton::clicked, this, &ForgotPasswordWidget::on_btnBack_clicked);
}

void ForgotPasswordWidget::on_btnResetPassword_clicked()
{
    QString email = ui->leEmail->text();
    QString newPassword = ui->leNewPassword->text();
    QString confirmPassword = ui->leConfirmNewPassword->text();

    // Validasi input
        if (email.isEmpty() || newPassword.isEmpty() || confirmPassword.isEmpty()) {
            QMessageBox::warning(this, "Error", "Please fill the information above!");
            return;
        }

        // Validasi format email
        QRegularExpression emailRegex(R"(\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}\b)",
                                      QRegularExpression::CaseInsensitiveOption);
        if (!emailRegex.match(email).hasMatch()) {
            QMessageBox::warning(this, "Error", "Wrong email format!");
            return;
        }

        if (newPassword != confirmPassword) {
            QMessageBox::warning(this, "Error", "Passwords do not match!");
            return;
        }

        if (newPassword.length() < 8) {
            QMessageBox::warning(this, "Error", "Password must be at least 8 characters!");
            return;
        }

        // ====== Update password di database ======
        QSqlQuery query;
        query.prepare("UPDATE users SET password = :password WHERE email = :email");
        query.bindValue(":password", newPassword);
        query.bindValue(":email", email);

        if (!query.exec()) {
            QMessageBox::critical(this, "Error", "Failed to update password: " + query.lastError().text());
            return;
        }

        if (query.numRowsAffected() == 0) {
            QMessageBox::warning(this, "Error", "Email not registered in system!");
            return;
        }

        QMessageBox::information(this, "Success", "Password updated successfully!");
        emit backToLogin();
    }

void ForgotPasswordWidget::on_btnBack_clicked()
{
    emit backToLogin();  // Kirim signal untuk kembali ke login
}

ForgotPasswordWidget::~ForgotPasswordWidget()
{
    delete ui;
}
