#include "forgotpasswordwidget.h"
#include "ui_forgotpasswordwidget.h"
#include <QMessageBox>
#include <QRegularExpression>
#include <QDebug>

ForgotPasswordWidget::ForgotPasswordWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ForgotPasswordWidget)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Reset Password - Medical System");
    setFixedSize(1900, 900);

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
        QMessageBox::warning(this, "Error", "Semua field harus diisi!");
        return;
    }

    // Validasi email format
    QRegularExpression emailRegex(R"(\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}\b)",
                                 QRegularExpression::CaseInsensitiveOption);
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Error", "Format email tidak valid!");
        return;
    }

    if (newPassword != confirmPassword) {
        QMessageBox::warning(this, "Error", "Password baru dan konfirmasi password tidak sama!");
        return;
    }

    // Validasi kekuatan password (minimal 8 karakter)
    if (newPassword.length() < 8) {
        QMessageBox::warning(this, "Error", "Password harus minimal 8 karakter!");
        return;
    }

    // Simulasi pengiriman email reset password
    qDebug() << "Password reset requested for email:" << email;
    qDebug() << "New password would be set to:" << newPassword;

    // Dalam implementasi nyata, di sini akan ada kode untuk:
    // 1. Memverifikasi email terdaftar di database
    // 2. Mengirim email dengan link reset password
    // 3. atau Langsung mengubah password (tergantung kebijakan keamanan)

    QMessageBox::information(this, "Success", "Instruksi reset password telah dikirim ke email Anda!\nSilakan cek inbox atau folder spam Anda.");
    emit backToLogin();  // Kembali ke login
}

void ForgotPasswordWidget::on_btnBack_clicked()
{
    emit backToLogin();  // Kirim signal untuk kembali ke login
}

ForgotPasswordWidget::~ForgotPasswordWidget()
{
    delete ui;
}
