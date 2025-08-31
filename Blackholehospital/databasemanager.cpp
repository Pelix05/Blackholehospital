#include "databasemanager.h"
#include "QMessageBox"

// 单例实现
DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

DatabaseManager::DatabaseManager() {
    db = QSqlDatabase::database(); // 获取默认连接
    if (!db.isOpen()) {
        qDebug() << "Database not open in DatabaseManager!";
    }
}

// ----------------- 用户 -----------------
bool DatabaseManager::addUser(const QString& username, const QString& password,
                              const QString& email,const QString phone ,const QString& userType) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, email, phone, user_type) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(phone);
    query.addBindValue(userType);

    if (!query.exec()) {
        qDebug() << "Add user failed:" << query.lastError().text();
        return false;
    }
    return true;

}

QMap<QString, QVariant> DatabaseManager::checkUserLogin(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT user_id, username, password, user_type FROM users WHERE username=?");
    query.addBindValue(username);
    QMap<QString, QVariant> result;
    if (query.exec() && query.next()) {
        result["user_id"] = query.value("user_id");
        result["username"] = query.value("username");
        result["password"] = query.value("password");
        result["user_type"] = query.value("user_type");
    }
    return result;


}



// ----------------- 患者 -----------------
bool DatabaseManager::addPatient(const QString& name,
                                 const QString& birthDate, const QString& idCard,
                                 const QString& phone ) {
    QSqlQuery query;
    query.prepare("INSERT INTO patients (name, birth_date, id_card, phone) "
                  "VALUES (?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(birthDate);
    query.addBindValue(idCard);
    query.addBindValue(phone);

    if (!query.exec()) {
        qDebug() << "Add patient failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QMap<QString, QVariant> DatabaseManager::getPatientInfo(int patientId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM patients WHERE patient_id=?");
    query.addBindValue(patientId);
    QMap<QString, QVariant> result;
    if (query.exec() && query.next()) {
        result["name"] = query.value("name");
        result["gender"] = query.value("gender");
        result["birth_date"] = query.value("birth_date");
        result["id_card"] = query.value("id_card");
        result["phone"] = query.value("phone");
        result["emergency_contact"] = query.value("emergency_contact");
    }
    return result;
}

// ----------------- 医生 -----------------
bool DatabaseManager::addDoctor(QString userId, const QString& department, const QString& title,
                                const QString& intro, const QString& workSchedule) {
    QSqlQuery query;
    query.prepare("INSERT INTO doctors (doctor_id, department, title, intro, work_schedule) "
                  "VALUES (?, ?, ?, ?, ?)");
    query.addBindValue(userId);
    query.addBindValue(department);
    query.addBindValue(title);
    query.addBindValue(intro);
    query.addBindValue(workSchedule);
    if (!query.exec()) {
        qDebug() << "Add doctor failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QMap<QString, QVariant> DatabaseManager::getDoctorInfo(int doctorId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM doctors WHERE doctor_id=?");
    query.addBindValue(doctorId);
    QMap<QString, QVariant> result;
    if (query.exec() && query.next()) {
        result["department"] = query.value("department");
        result["title"] = query.value("title");
        result["intro"] = query.value("intro");
        result["work_schedule"] = query.value("work_schedule");
    }
    return result;
}

// ----------------- 预约 -----------------
bool DatabaseManager::addAppointment(int patientId, int doctorId, const QString& appointTime) {
    QSqlQuery query;
    query.prepare("INSERT INTO appointments (patient_id, doctor_id, appoint_time) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(appointTime);
    if (!query.exec()) {
        qDebug() << "Add appointment failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<QMap<QString, QVariant>> DatabaseManager::getAppointmentsByDoctor(int doctorId, const QString& date) {
    QSqlQuery query;
    query.prepare("SELECT appointment_id, patient_id, appoint_time, status "
                  "FROM appointments "
                  "WHERE doctor_id=? AND DATE(appoint_time)=?");
    query.addBindValue(doctorId);
    query.addBindValue(date);
    QList<QMap<QString, QVariant>> results;
    if (query.exec()) {
        while (query.next()) {
            QMap<QString, QVariant> record;
            record["appointment_id"] = query.value("appointment_id");
            record["patient_id"] = query.value("patient_id");
            record["appoint_time"] = query.value("appoint_time");
            record["status"] = query.value("status");
            results.append(record);
        }
    }
    return results;
}

bool DatabaseManager::updateAppointmentStatus(int appointmentId, const QString& status) {
    QSqlQuery query;
    query.prepare("UPDATE appointments SET status=? WHERE appointment_id=?");
    query.addBindValue(status);
    query.addBindValue(appointmentId);
    if (!query.exec()) {
        qDebug() << "Update appointment failed:" << query.lastError().text();
        return false;
    }
    return true;
}

// ----------------- 病例 -----------------
bool DatabaseManager::addMedicalRecord(int patientId, int doctorId, const QString& diagnose) {
    QSqlQuery query;
    query.prepare("INSERT INTO medical_records (patient_id, doctor_id, diagnose) "
                  "VALUES (?, ?, ?)");
    query.addBindValue(patientId);
    query.addBindValue(doctorId);
    query.addBindValue(diagnose);
    if (!query.exec()) {
        qDebug() << "Add medical record failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<QMap<QString, QVariant>> DatabaseManager::getMedicalRecordsByPatient(int patientId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM medical_records WHERE patient_id=? ORDER BY created_at DESC");
    query.addBindValue(patientId);
    QList<QMap<QString, QVariant>> results;
    if (query.exec()) {
        while (query.next()) {
            QMap<QString, QVariant> record;
            record["record_id"] = query.value("record_id");
            record["doctor_id"] = query.value("doctor_id");
            record["diagnose"] = query.value("diagnose");
            record["created_at"] = query.value("created_at");
            results.append(record);
        }
    }
    return results;
}
