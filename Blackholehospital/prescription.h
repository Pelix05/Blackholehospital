#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class Prescription;
}

class Prescription : public QDialog
{
    Q_OBJECT

public:
    explicit Prescription(QWidget *parent = nullptr);
    ~Prescription();

    // 添加一条处方记录
    void addOrder(const QString &id, const QString &date,
                  const QString &dept, const QString &doctor,
                  const QString &summary, const QString &detail);

private:
    Ui::Prescription *ui;
    QStandardItemModel *model;
};

#endif // PRESCRIPTION_H
