#ifndef REGISTERWIDGET_H
#define REGISTERWIDGET_H

#include <QWidget>

namespace Ui {
class RegisterWidget;
}

class RegisterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterWidget(QWidget *parent = nullptr);
    ~RegisterWidget();

signals:
    void backToLogin();  // Signal untuk kembali ke login


private slots:
    void on_btnRegister_clicked();
    void on_btnBack_clicked();

private:
    Ui::RegisterWidget *ui;
};

#endif // REGISTERWIDGET_H
