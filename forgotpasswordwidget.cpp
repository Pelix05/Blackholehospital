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
    setFixedSize(1600, 1500);

    // Connect buttons to functions
    connect(ui->btnResetPassword, &QPushButton::clicked, this, &ForgotPasswordWidget::on_btnResetPassword_clicked);
    connect(ui->btnBack, &QPushButton::clicked, this, &ForgotPasswordWidget::on_btnBack_clicked);
}

void ForgotPasswordWidget::on_btnResetPassword_clicked()
{
    QString email = ui->leEmail->text();
    QString newPassword = ui->leNewPassword->text();
    QString confirmPassword = ui->leConfirmPassword->text();

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
