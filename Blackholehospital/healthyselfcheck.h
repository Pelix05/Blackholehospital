#ifndef HEALTHYSELFCHECK_H
#define HEALTHYSELFCHECK_H

#include <QWidget>

namespace Ui {
class healthyselfcheck;
}

class healthyselfcheck : public QWidget
{
    Q_OBJECT

public:
    explicit healthyselfcheck(QWidget *parent = nullptr);
    ~healthyselfcheck();

private slots:
    void submit();

private:
    Ui::healthyselfcheck *ui;
};

#endif // HEALTHYSELFCHECK_H
