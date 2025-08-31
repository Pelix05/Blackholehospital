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

struct Doctor {
    QString jobId;
    QString name;
    QString hospital;
    QString department;
    QString clinic;
    QTime   shiftStart;
    QTime   shiftEnd;
    bool    supportsAppointment;
    int     limitPerDay;
    int     booked;
};

class appointment : public QWidget
{
    Q_OBJECT

public:
    explicit appointment(QWidget *parent = nullptr);
    ~appointment();

signals:
    void backRequested();

private slots:
    void searchclicked();
    void bookclicked();

private:
    Ui::appointment *ui;
    QStandardItemModel *resultsModel;
    QVector<Doctor> doctors;

    void loadTestDoctors();
    void populateFilterChoices();
    void refillResults(const QList<int> &indexes);
    bool timeWithinShift(const Doctor &d, const QTime &t) const;
};

#endif // APPOINTMENT_H
