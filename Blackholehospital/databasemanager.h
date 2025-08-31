#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QVariant>
#include <QList>
#include <QMap>

class DatabaseManager {
public:
    static DatabaseManager& instance();

    // 用户
    bool addUser(const QString& username, const QString& password,
                 const QString& email, const QString phone ,const QString& userType);
    QMap<QString, QVariant> checkUserLogin(const QString& username);

    // 患者
    bool addPatient(const QString& name,
                    const QString& birthDate, const QString& idCard,
                    const QString& phone);
    QMap<QString, QVariant> getPatientInfo(int patientId);

    // 医生
    bool addDoctor(QString userId, const QString& department, const QString& title,
                   const QString& intro, const QString& workSchedule);
    QMap<QString, QVariant> getDoctorInfo(int doctorId);

    // 预约
    bool addAppointment(int patientId, int doctorId, const QString& appointTime);
    QList<QMap<QString, QVariant>> getAppointmentsByDoctor(int doctorId, const QString& date);
    bool updateAppointmentStatus(int appointmentId, const QString& status);

    // 病例
    bool addMedicalRecord(int patientId, int doctorId, const QString& diagnose);
    QList<QMap<QString, QVariant>> getMedicalRecordsByPatient(int patientId);

private:
    DatabaseManager(); // 构造函数私有化
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
