#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include <QWidget>
#include <QString>
#include <QTime>
#include <QStandardItemModel>
#include <QVector>

namespace Ui {
class appointment;
}

class appointment : public QWidget
{
    Q_OBJECT

public:
    explicit appointment(const QString &patientIdCard, QWidget *parent = nullptr);
    ~appointment();

signals:
    void backRequested();

private slots:
    void searchclicked();
    void bookclicked();

private:
    Ui::appointment *ui;
    QStandardItemModel *resultsModel;
    QString m_patientIdCard;

    void populateFilterChoices();
    void refillResults(const QList<QVariantMap> &schedules);
};

#endif // APPOINTMENT_H
