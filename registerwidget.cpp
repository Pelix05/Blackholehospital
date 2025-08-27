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

    // Set window properties
    setWindowTitle("Register - Medical System");
    setFixedSize(1600, 1500);

    // Connect buttons to functions
    connect(ui->btnRegister, &QPushButton::clicked, this, &RegisterWidget::on_btnRegister_clicked);
    connect(ui->btnBack, &QPushButton::clicked, this, &RegisterWidget::on_btnBack_clicked);
}

void RegisterWidget::on_btnRegister_clicked()
{
    // Ambil data dari form
    QString name = ui->leUsername->text();
    QString email = ui->leEmail->text();
    QString phone = ui->lePhone->text();
    QString password = ui->lePassword->text();
    QString confirmPassword = ui->leConfirmPassword->text();

    // Validasi input
    if (name.isEmpty() || email.isEmpty() || phone.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Semua field harus diisi!");
        return;
    }

    if (!ui->cbAgree->isChecked()) {
        QMessageBox::warning(this, "Error", "Anda harus menyetujui terms and conditions!");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Error", "Password dan Confirm Password tidak sama!");
        return;
    }

    // Validasi email format
    QRegularExpression emailRegex(R"(\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,}\b)",
                                 QRegularExpression::CaseInsensitiveOption);
    if (!emailRegex.match(email).hasMatch()) {
        QMessageBox::warning(this, "Error", "Format email tidak valid!");
        return;
    }

    // Validasi phone number (minimal 10 digit)
    if (phone.length() < 10) {
        QMessageBox::warning(this, "Error", "Nomor telepon harus minimal 10 digit!");
        return;
    }

    // Jika semua validasi passed
    qDebug() << "Register successful:";
    qDebug() << "Name:" << name;
    qDebug() << "Email:" << email;
    qDebug() << "Phone:" << phone;

    QMessageBox::information(this, "Success", "Registrasi berhasil!\nSilakan login dengan akun Anda.");
    emit backToLogin();  // Kembali ke login
}

void RegisterWidget::on_btnBack_clicked()
{
    emit backToLogin();  // Kirim signal untuk kembali ke login
}

RegisterWidget::~RegisterWidget()
{
    delete ui;
}
