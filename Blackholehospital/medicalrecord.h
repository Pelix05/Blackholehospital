#ifndef MEDICALRECORD_H
#define MEDICALRECORD_H

#include <QWidget>
#include <QStandardItemModel> //keep data
#include  <QModelIndex>

namespace Ui {
class medicalrecord;
}

class medicalrecord : public QWidget
{
    Q_OBJECT

public:
    explicit medicalrecord(const QString &patientIdCard, QWidget *parent = nullptr);
    ~medicalrecord();

   void loadMedicalRecords();

private slots:
    void doubleclicked(const QModelIndex &index);

private:
    Ui::medicalrecord *ui;
    QStandardItemModel *model;
    QString m_patientIdCard;
    QString generateInstructions(const QString &department);
    QString generatePrescription(const QString &department);

};

#endif // MEDICALRECORD_H
