#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class instruction;
}

class instruction : public QDialog
{
    Q_OBJECT

public:
    explicit instruction(QWidget *parent = nullptr);
    ~instruction();

private:
    Ui::instruction *ui;
    QStandardItemModel *model;
    void addOrder(const QString &id, const QString &date,
                  const QString &dept, const QString &doctor,
                  const QString &summary, const QString &detail);
};

#endif // INSTRUCTION_H
