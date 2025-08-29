#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <QWidget>
#include <QStandardItemModel> //keep data

namespace Ui {
class medicalrecord;
}

class medicalrecord : public QWidget
{
    Q_OBJECT

public:
    explicit medicalrecord(QWidget *parent = nullptr);
    ~medicalrecord();

    void addcase(int id, QString date, QString dep, QString doctor, QString job);

private slots:
    void doubleclicked(const QModelIndex &index);

private:
    Ui::medicalrecord *ui;
    QStandardItemModel *model;
    QString generateInstructions(const QString &department);
    QString generatePrescription(const QString &department);

};

#endif // MEDICALRECORD_H
