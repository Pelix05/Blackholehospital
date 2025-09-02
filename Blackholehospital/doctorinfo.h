// DoctorInfo.h
#ifndef DOCTORINFO_H
#define DOCTORINFO_H

#include <QString>
#include <QDate>
#include <QTime>

struct DoctorInfo {
    int scheduleId;
    int doctorId;
    QString jobNumber;
    QString name;
    QString hospital;
    QString department;
    QString clinic;
    QDate workDate;
    QTime shiftStart;
    QTime shiftEnd;
    double fee;
    int limitPerDay;
    int bookedCount;
    bool supportsAppointment;
};

#endif // DOCTORINFO_H
