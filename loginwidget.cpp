#include "loginwidget.h"
#include "ui_loginwidget.h"
#include <QMessageBox>
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoginWidget),
    registerWidget(nullptr),  // Initialize pointer ke nullptr
    forgotPasswordWidget(nullptr)
{
    ui->setupUi(this);

    // Set window properties
    setWindowTitle("Medical System Login");
    setFixedSize(1600, 1500);

    ui->cbRole->addItem("Patient");
    ui->cbRole->addItem("Doctor");

    // Connect buttons
    connect(ui->btnLogin, &QPushButton::clicked, this, &LoginWidget::on_btnLogin_clicked);
    connect(ui->btnRegister, &QPushButton::clicked, this, &LoginWidget::on_btnRegister_clicked);
    connect(ui->btnForgot, &QPushButton::clicked, this, &LoginWidget::on_btnForgot_clicked);
}

void LoginWidget::on_btnLogin_clicked()
{
    QString username = ui->leUsername->text();
    QString password = ui->lePassword->text();
    QString role = ui->cbRole->currentText();
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
