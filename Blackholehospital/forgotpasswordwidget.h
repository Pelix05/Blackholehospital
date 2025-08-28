#ifndef FORGOTPASSWORDWIDGET_H
#define FORGOTPASSWORDWIDGET_H

#include <QWidget>

namespace Ui {
class ForgotPasswordWidget;
}

class ForgotPasswordWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ForgotPasswordWidget(QWidget *parent = nullptr);
    ~ForgotPasswordWidget();
signals:
    void backToLogin();  // back to login

private slots:
    void on_btnResetPassword_clicked();
    void on_btnBack_clicked();

private:
    Ui::ForgotPasswordWidget *ui;
};

#endif // FORGOTPASSWORDWIDGET_H
