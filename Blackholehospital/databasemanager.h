#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>
#include <QVariant>
#include <QList>
#include <QMap>
#include <QDate>
#include <QTime>

struct PrescriptionRecord {
    int prescriptionId;
    int recordId;
    QString content;
};

class DatabaseManager {
public:
    static DatabaseManager& instance();

    // 用户
    bool addUser(const QString& username, const QString& password,
                 const QString& email, const QString &phone ,
                 const QString& userType,const QString& gender
                 ,const QString &idCard, const QString &address);
    QMap<QString, QVariant> checkUserLogin(const QString& username);

    // 患者
    bool addPatient(const QString& name,
                    const QString& birthDate, const QString& idCard,
                    const QString& phone, const QString& email,
                    const QString& address,const QString& gender);
    QMap<QString, QVariant> getPatientInfo(const QString& idCard);

    // 医生
    bool addDoctor(const QString& name,
                    const QString& birthDate, const QString& idCard,
                    const QString& phone, const QString& email,
                    const QString& address,const QString& gender);
    QMap<QString, QVariant> getDoctorInfo(const QString& idCard);

    // 预约
    bool addAppointment(int patientId, int doctorId, const QString& appointTime);
    QList<QMap<QString, QVariant>> getAppointmentsByDoctor();
    bool updateAppointmentStatus(int appointmentId, const QString& status);

    // 病例
    bool addMedicalRecord(int patientId, int doctorId, const QString& diagnose);
    QList<QMap<QString, QVariant>> getMedicalRecordsByPatient(int patientId);


    bool updateDoctor(const QString &idCard,
                      const QString &name,
                      const QString &email,
                      const QString &phone,
                      const QString &birthDate,
                      const QString &department,
                      const QString &address,
                      const QString &gender,
                      const QString &photo,
                      double fee,
                      int dailyLimit);

    QMap<QString, QVariant> getPatientInfoById(int patientId);


    // ===== 医生排班 =====
       bool addDoctorSchedule(int doctorId, const QString& hospital,
                              const QString& department, const QString& clinic,
                              const QString& jobNumber, const QDate& workDate,
                              const QTime& start, const QTime& end,
                              double fee, int limitPerDay,
                              bool supportsAppointment);
       QList<QVariantMap> queryDoctorSchedules(
           const QString& hospital, const QString& department,
           const QString& clinic, const QDate& onDate,
           const QTime& atTime, bool requireSupportAppointment);


       // ====== 预约 / 挂号 ======
       // 根据 schedule_id + 患者 id_card 建立预约，并更新已约人数。返回是否成功。
       bool bookAppointmentBySchedule(const QString& patientIdCard,
                                      int scheduleId,
                                      const QDateTime& appointTime,
                                      QString* errorOut = nullptr);

    bool insertPerscription(int recordId, const QString &content);
    QVector<PrescriptionRecord> getPrescriptions();

    // 获取患者医嘱
    QList<QMap<QString, QVariant>> getOrdersByPatient(qlonglong  patientId);


private:
    DatabaseManager(); // 构造函数私有化
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H
