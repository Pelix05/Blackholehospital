#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    registerWidget(nullptr)  // Initialize pointer ke nullptr
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Medical System Login");
    setFixedSize(1600, 1500);

    // Connect buttons
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginWidget::on_btnLogin_clicked);
    connect(ui->btnRegister, &QPushButton::clicked, this, &LoginWidget::on_btnRegister_clicked);
    connect(ui->btnForgot, &QPushButton::clicked, this, &LoginWidget::on_btnForgot_clicked);
}

void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Error", "Username dan password tidak boleh kosong!");
        return;
    }

    qDebug() << "Login attempt - Username:" << username << "Password:" << password;
    QMessageBox::information(this, "Success", "Login berhasil!");
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
    QMessageBox::information(this, "Info", "Fitur lupa password akan datang soon!");
}

LoginWidget::~LoginWidget()
{
    delete ui;
    if (registerWidget) {
        delete registerWidget;  // Hapus register widget jika ada
    }
}
