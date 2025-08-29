#ifndef RECHARGE_H
#define RECHARGE_H

#include <QWidget>

namespace Ui {
class recharge;
}

class recharge : public QWidget
{
    Q_OBJECT

public:
    explicit recharge(QWidget *parent = nullptr);
    ~recharge();

private slots:
    void Payclicked();

private:
    Ui::recharge *ui;
};

#endif // RECHARGE_H
