#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>
#include "registerwidget.h"
#include "forgotpasswordwidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class LoginWidget; }
QT_END_NAMESPACE

class LoginWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoginWidget(QWidget *parent = nullptr);
    ~LoginWidget();

    QString getSelectedRole() const;


private slots:
    void on_btnLogin_clicked();
    void on_btnRegister_clicked();
    void on_btnForgot_clicked();

private:
    Ui::LoginWidget *ui;
    RegisterWidget *registerWidget;
    ForgotPasswordWidget *forgotPasswordWidget;

};
#endif // LOGINWIDGET_H
