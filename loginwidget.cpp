#include "loginwidget.h"
#include "ui_loginwidget.h"
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
                                   "padding: 15px;"
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
                                      "padding: 15px;"
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

        ui->leUsername->setStyleSheet(lineEditStyle);
        ui->lePassword->setStyleSheet(lineEditStyle);

        // Style untuk combo box
        ui->cbRole->setStyleSheet("QComboBox {"
                                 "border: 2px solid #cccccc;"
                                 "border-radius: 8px;"
                                 "padding: 12px;"
                                 "font-size: 16px;"
                                 "background-color: white;"
                                 "}"
                                 "QComboBox:focus {"
                                 "border: 2px solid #0066cc;"
                                 "}"
                                 "QComboBox QAbstractItemView {"
                                 "border: 2px solid #cccccc;"
                                 "selection-background-color: #0066cc;"
                                 "}");
        // ===== END STYLE SHEET =====

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
