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

    QSqlQuery checkQuery;
    checkQuery.exec("SELECT COUNT(*) FROM doctors");
    if (checkQuery.next() && checkQuery.value(0).toInt() == 0) {

        // ======== 预存三条医生数据（测试用） ========
        QSqlQuery query;

        query.exec("INSERT OR IGNORE INTO doctors (name, birth_date, id_card, phone, email, address, gender) "
                   "VALUES ('张三','1980-01-01','D001','13800000001','zhangsan@example.com','地址1','M')");
        query.exec("INSERT OR IGNORE INTO doctors (name, birth_date, id_card, phone, email, address, gender) "
                   "VALUES ('李四','1985-02-02','D002','lisi@example.com','地址2','F')");
        query.exec("INSERT OR IGNORE INTO doctors (name, birth_date, id_card, phone, email, address, gender) "
                   "VALUES ('王五','1990-03-03','D003','13800000003','地址3','M')");

        // 查询真实 doctor_id
        QMap<QString,int> doctorIds;
        QSqlQuery q2("SELECT doctor_id, name FROM doctors");
        while(q2.next()) {
            doctorIds[q2.value("name").toString()] = q2.value("doctor_id").toInt();
        }

        // 插入排班数据
        {
            QSqlQuery q;
            q.prepare("INSERT OR IGNORE INTO doctor_schedules "
                      "(doctor_id, hospital, department, clinic, job_number, work_date, start_time, end_time, fee, limit_per_day, supports_appointment, booked_count) "
                      "VALUES (?, '黑洞医院', '内科', '门诊1', 'D001', '2025-09-03', '08:00', '12:00', 20.0, 20, 1, 0)");
            q.addBindValue(doctorIds["张三"]);
            q.exec();
        }
        {
            QSqlQuery q;
            q.prepare("INSERT OR IGNORE INTO doctor_schedules "
                      "(doctor_id, hospital, department, clinic, job_number, work_date, start_time, end_time, fee, limit_per_day, supports_appointment, booked_count) "
                      "VALUES (?, '黑洞医院', '外科', '门诊2', 'D002', '2025-09-03', '14:00', '18:00', 30.0, 15, 1, 0)");
            q.addBindValue(doctorIds["李四"]);
            q.exec();
        }
        {
            QSqlQuery q;
            q.prepare("INSERT OR IGNORE INTO doctor_schedules "
                      "(doctor_id, hospital, department, clinic, job_number, work_date, start_time, end_time, fee, limit_per_day, supports_appointment, booked_count) "
                      "VALUES (?, '黑洞医院', '儿科', '门诊3', 'D003', '2025-09-04', '09:00', '17:00', 25.0, 10, 0, 0)");
            q.addBindValue(doctorIds["王五"]);
            q.exec();
        }

        // 插入医嘱，每条使用独立 QSqlQuery
        {
            QSqlQuery q;
            q.prepare("INSERT INTO doctor_orders (doctor_id, patient_id, order_content) VALUES (?, ?, ?)");
            q.addBindValue(1);
            q.addBindValue(1);
            q.addBindValue(
                "1. 注意休息，多饮水\n"
                "2. 按时服药，每日3次\n"
                "3. 高热不退或症状加重，请及时复诊\n"
                "4. 饮食清淡，避免辛辣刺激食物"
            );
            if (!q.exec()) {
                qDebug() << "Insert doctor_order failed:" << q.lastError().text();
            } else {
                qDebug() << "Insert doctor_order succeeded";
            }
        }
        {
            QSqlQuery q;
            q.prepare("INSERT INTO doctor_orders (doctor_id, patient_id, order_content) VALUES (?, ?, ?)");
            q.addBindValue(2);
            q.addBindValue(1);
            q.addBindValue(
                "1. 患肢制动，抬高患肢\n"
                "2. 伤后48小时内冷敷，之后热敷\n"
                "3. 按时服用止痛药物\n"
                "4. 一周后复诊"
            );
            if (!q.exec()) {
                qDebug() << "Insert doctor_order failed:" << q.lastError().text();
            } else {
                qDebug() << "Insert doctor_order succeeded";
            }
        }
        {
            QSqlQuery q;
            q.prepare("INSERT INTO doctor_orders (doctor_id, patient_id, order_content) VALUES (?, ?, ?)");
            q.addBindValue(3);
            q.addBindValue(2);
            q.addBindValue(
                "1. 按时滴眼药水，每日4次\n"
                "2. 注意手部卫生，避免揉眼\n"
                "3. 毛巾、脸盆单独使用，防止交叉感染\n"
                "4. 症状消失后继续用药3天"
            );
            if (!q.exec()) {
                qDebug() << "Insert doctor_order failed:" << q.lastError().text();
            } else {
                qDebug() << "Insert doctor_order succeeded";
            }
        }

        qDebug() << "✅ 已预存三条测试排班 & doctor 数据及医嘱";
    }

       QSqlQuery q("SELECT doctor_id, name FROM doctors");
       while(q.next()) {
           qDebug() << "Doctor table:" << q.value("doctor_id").toInt()
                    << q.value("name").toString();
       }


       QSqlQuery q3("SELECT doctor_id, department FROM doctor_schedules");
       while(q3.next()) {
           qDebug() << "Schedule table:" << q3.value("doctor_id").toInt() << q3.value("department").toString();
       }



}

// ----------------- 用户 -----------------
bool DatabaseManager::addUser(const QString& username, const QString& password,
                              const QString& email,const QString &phone ,
                              const QString& userType,const QString& gender,
                              const QString &idCard, const QString& address) {
    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password, email, phone, user_type, "
                  "gender, id_card, address) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?,?)");
    query.addBindValue(username);
    query.addBindValue(password);
    query.addBindValue(email);
    query.addBindValue(phone);
    query.addBindValue(userType);
    query.addBindValue(gender);
    query.addBindValue(idCard);
    query.addBindValue(address);

    if (!query.exec()) {
        qDebug() << "Add user failed:" << query.lastError().text();
        return false;
    }
    return true;

}

QMap<QString, QVariant> DatabaseManager::checkUserLogin(const QString& username) {
    QSqlQuery query;
    query.prepare("SELECT user_id, username, password, user_type, id_card FROM users WHERE username=?");
    query.addBindValue(username);
    QMap<QString, QVariant> result;
    if (query.exec() && query.next()) {
        result["user_id"] = query.value("user_id");
        result["username"] = query.value("username");
        result["password"] = query.value("password");
        result["user_type"] = query.value("user_type");
        result["id_card"]   = query.value("id_card");
    }
    return result;


}



// ----------------- 患者 -----------------
bool DatabaseManager::addPatient(const QString& name,
                                 const QString& birthDate, const QString& idCard,
                                 const QString& phone, const QString& email,
                                 const QString& address,const QString& gender ) {
    QSqlQuery query;
    query.prepare("INSERT INTO patients (name, birth_date, id_card, phone, email, address, gender) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(birthDate);
    query.addBindValue(idCard);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(address);
    query.addBindValue(gender);

    if (!query.exec()) {
        qDebug() << "Add patient failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QMap<QString, QVariant> DatabaseManager::getPatientInfo(const QString& idCard) {
    QSqlQuery query;
    query.prepare("SELECT * FROM patients WHERE id_card=?");  // 修正列名
    query.addBindValue(idCard);

    QMap<QString, QVariant> result;

    if (!query.exec()) {
        qDebug() << "SQL execution failed:" << query.lastError().text();
        return result;
    }

    if (!query.next()) {
        qDebug() << "No rows returned for idcard:" << idCard;
        // 打印数据库里所有患者，确认表里是否有数据
        QSqlQuery q("SELECT id_card, name FROM patients");
        while (q.next()) {
            qDebug() << "Patient row:" << q.value("id_card").toString() << q.value("name").toString();
        }
        return result;
    }

    // ✅ 成功获取数据
    result["name"] = query.value("name");
    result["gender"] = query.value("gender");
    result["birth_date"]= query.value("birth_date").toString(); // 保证字符串格式
    result["id_card"] = query.value("id_card");
    result["phone"] = query.value("phone");
    result["email"] = query.value("email");
    result["address"] = query.value("address");
    result["patient_id"] = query.value("patient_id");


    qDebug() << "Loaded patient info:" << result;

    return result;
}

// ----------------- 医生 -----------------
bool DatabaseManager::addDoctor(const QString& name,
                                 const QString& birthDate, const QString& idCard,
                                 const QString& phone, const QString& email,
                                 const QString& address,const QString& gender ) {
    QSqlQuery query;
    query.prepare("INSERT INTO doctors (name, birth_date, id_card, phone, email, address, gender) "
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(name);
    query.addBindValue(birthDate);
    query.addBindValue(idCard);
    query.addBindValue(phone);
    query.addBindValue(email);
    query.addBindValue(address);
    query.addBindValue(gender);


    if (!query.exec()) {
        qDebug() << "Add doctor failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QMap<QString, QVariant> DatabaseManager::getDoctorInfo(const QString& idCard) {
    QSqlQuery query;
    query.prepare("SELECT * FROM doctors WHERE id_card=?");  // 修正列名
    query.addBindValue(idCard);

    QMap<QString, QVariant> result;

    if (!query.exec()) {
        qDebug() << "SQL execution failed:" << query.lastError().text();
        return result;
    }

    if (!query.next()) {
        qDebug() << "No rows returned for idcard:" << idCard;
        // 打印数据库里所有患者，确认表里是否有数据
        QSqlQuery q("SELECT id_card, name FROM doctors");
        while (q.next()) {
            qDebug() << "Doctor row:" << q.value("id_card").toString() << q.value("name").toString();
        }
        return result;
    }

    // ✅ 成功获取数据
    result["name"] = query.value("name");
    result["gender"] = query.value("gender");
    result["birth_date"] = query.value("birth_date");
    result["id_card"] = query.value("id_card");
    result["phone"] = query.value("phone");
    result["email"] = query.value("email");
    result["address"] = query.value("address");
    result["department"] = query.value("department");
    result["fee"] = query.value("fee");
    result["daily_limit"] = query.value("daily_limit");


    qDebug() << "Loaded patient info:" << result;

    return result;
}

bool DatabaseManager::updateDoctor(const QString &idCard,
                                   const QString &name,
                                   const QString &email,
                                   const QString &phone,
                                   const QString &birthDate,
                                   const QString &department,
                                   const QString &address,
                                   const QString &gender,
                                   const QString &photo,
                                   double fee,
                                   int dailyLimit)
{
    QSqlQuery query(db);
    query.prepare(R"(
        UPDATE doctors SET
            name = :name,
            email = :email,
            phone = :phone,
            birth_date = :birthDate,
            department = :department,
            address = :address,
            gender = :gender,
            photo = :photo,
                  fee = :fee,
                  daily_limit = :dailyLimit

        WHERE id_card = :idCard
    )");

    query.bindValue(":name", name);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":birthDate", birthDate);
    query.bindValue(":department", department);
    query.bindValue(":address", address);
    query.bindValue(":gender", gender);
    query.bindValue(":photo", photo);
    query.bindValue(":fee", fee);
    query.bindValue(":dailyLimit", dailyLimit);
    query.bindValue(":idCard", idCard);

    if(!query.exec()) {
        qDebug() << "Failed to update doctor:" << query.lastError().text();
        return false;
    }

    return true;
}

// ===== 医生排班 =====
bool DatabaseManager::addDoctorSchedule(int doctorId, const QString& hospital,
                                        const QString& department, const QString& clinic,
                                        const QString& jobNumber, const QDate& workDate,
                                        const QTime& start, const QTime& end,
                                        double fee, int limitPerDay,
                                        bool supportsAppointment) {
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO doctor_schedules
        (doctor_id, hospital, department, clinic, job_number,
         work_date, start_time, end_time, fee, limit_per_day, supports_appointment)
        VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)
    )");
    query.addBindValue(doctorId);
    query.addBindValue(hospital);
    query.addBindValue(department);
    query.addBindValue(clinic);
    query.addBindValue(jobNumber);
    query.addBindValue(workDate);
    query.addBindValue(start);
    query.addBindValue(end);
    query.addBindValue(fee);
    query.addBindValue(limitPerDay);
    query.addBindValue(supportsAppointment);

    if (!query.exec()) {
        qDebug() << "Add schedule failed:" << query.lastError().text();
        return false;
    }
    return true;
}

QList<QVariantMap> DatabaseManager::queryDoctorSchedules(
    const QString& hospital, const QString& department,
    const QString& clinic, const QDate& onDate,
    const QTime& atTime, bool requireSupportAppointment) {

    QList<QVariantMap> results;
    QString sql = "SELECT s.*, d.name, d.gender, d.phone, d.email "
                  "FROM doctor_schedules s "
                  "JOIN doctors d ON s.doctor_id = d.doctor_id WHERE 1=1 ";

    if (!hospital.isEmpty()) sql += " AND hospital='" + hospital + "'";
    if (!department.isEmpty()) sql += " AND department='" + department + "'";
    if (!clinic.isEmpty()) sql += " AND clinic='" + clinic + "'";
    if (onDate.isValid()) sql += " AND work_date='" + onDate.toString("yyyy-MM-dd") + "'";
    if (atTime.isValid()) sql += " AND start_time<='" + atTime.toString("HH:mm") + "' AND end_time>='" + atTime.toString("HH:mm") + "'";
    if (requireSupportAppointment) sql += " AND supports_appointment=1";

    QSqlQuery query(sql);
    while (query.next()) {
        QVariantMap m;
        m["schedule_id"] = query.value("schedule_id");
        m["doctor_id"] = query.value("doctor_id");
        m["name"] = query.value("name");
        m["hospital"] = query.value("hospital");
        m["department"] = query.value("department");
        m["clinic"] = query.value("clinic");
        m["work_date"] = query.value("work_date");
        m["start_time"] = query.value("start_time");
        m["end_time"] = query.value("end_time");
        m["fee"] = query.value("fee");
        m["limit_per_day"] = query.value("limit_per_day");
        m["booked_count"] = query.value("booked_count");
        results.append(m);
    }
    return results;
}

// ===== 挂号/预约 =====
bool DatabaseManager::bookAppointmentBySchedule(const QString& patientIdCard,
                                                int scheduleId,
                                                const QDateTime& appointTime,
                                                QString* errorOut) {
    // 查找患者
    QSqlQuery q1;
    qDebug() << "Looking for patient id_card:" << patientIdCard;
    q1.prepare("SELECT patient_id FROM patients WHERE id_card=?");
    q1.addBindValue(patientIdCard);
    if (!q1.exec() || !q1.next()) {
        if (errorOut) *errorOut = "未找到患者";
        return false;
    }
    int patientId = q1.value(0).toInt();

    // 查找排班
    QSqlQuery q2;
    q2.prepare("SELECT doctor_id, limit_per_day, booked_count "
               "FROM doctor_schedules WHERE schedule_id=?");
    q2.addBindValue(scheduleId);
    if (!q2.exec() || !q2.next()) {
        if (errorOut) *errorOut = "未找到医生排班";
        return false;
    }
    int doctorId = q2.value(0).toInt();
    int limit = q2.value(1).toInt();
    int booked = q2.value(2).toInt();

    if (booked >= limit) {
        if (errorOut) *errorOut = "预约人数已满";
        return false;
    }

    // 插入预约
    QSqlQuery q3;
    q3.prepare("INSERT INTO appointments (patient_id, doctor_id, appoint_time) "
               "VALUES (?, ?, ?)");
    q3.addBindValue(patientId);
    q3.addBindValue(doctorId);
    q3.addBindValue(appointTime);
    if (!q3.exec()) {
        if (errorOut) *errorOut = q3.lastError().text();
        return false;
    }

    // 更新已约人数
    QSqlQuery q4;
    q4.prepare("UPDATE doctor_schedules SET booked_count=booked_count+1 WHERE schedule_id=?");
    q4.addBindValue(scheduleId);
    q4.exec();

    return true;
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

QList<QMap<QString, QVariant>> DatabaseManager::getAppointmentsByDoctor() {
    QSqlQuery query;
    query.prepare("SELECT appointment_id, patient_id, appoint_time, status "
                  "FROM appointments "
                  );

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

QMap<QString, QVariant> DatabaseManager::getPatientInfoById(int patientId) {
    QSqlQuery query;
    query.prepare("SELECT * FROM patients WHERE patient_id=?");
    query.addBindValue(patientId);

    QMap<QString, QVariant> result;
    if (query.exec() && query.next()) {
        result["name"] = query.value("name");
        result["gender"] = query.value("gender");
        result["birth_date"]= query.value("birth_date").toString();
        result["id_card"] = query.value("id_card");
        result["phone"] = query.value("phone");
        result["email"] = query.value("email");
        result["address"] = query.value("address");
    }
    return result;
}

QList<QMap<QString, QVariant>> DatabaseManager::getOrdersByPatient(qlonglong  patientId) {
    QSqlQuery queryCheck;
    qDebug() << "[getOrdersByPatient] Checking doctor_orders table content:";
    queryCheck.exec("SELECT * FROM doctor_orders");
    while(queryCheck.next()) {
        qDebug() << "[doctor_orders table]"
                 << "order_id:" << queryCheck.value("order_id").toInt()
                 << "patient_id:" << queryCheck.value("patient_id").toInt()
                 << "doctor_id:" << queryCheck.value("doctor_id").toInt()
                 << "order_content:" << queryCheck.value("order_content").toString()
                 << "created_at:" << queryCheck.value("created_at").toString();
    }

    QSqlQuery query;
    query.prepare(R"(
        SELECT o.order_id, o.created_at, o.order_content,
               d.name AS doctor_name, d.department
        FROM doctor_orders o
        JOIN doctors d ON o.doctor_id = d.doctor_id
        WHERE o.patient_id = ?
        ORDER BY o.created_at DESC
    )");
    query.addBindValue(patientId);

    QList<QMap<QString, QVariant>> results;

    qDebug() << "[getOrdersByPatient] Executing query for patient_id =" << patientId;

    if (!query.exec()) {
        qDebug() << "[getOrdersByPatient] SQL execution failed:" << query.lastError().text();
        return results;
    }

    if (!query.next()) {
        qDebug() << "[getOrdersByPatient] No orders found for patient_id =" << patientId;

        // 打印 doctor_orders 表内容用于排查
        QSqlQuery qAll("SELECT * FROM doctor_orders");
        while (qAll.next()) {
            qDebug() << "[doctor_orders]"
                     << "order_id:" << qAll.value("order_id").toInt()
                     << "patient_id:" << qAll.value("patient_id").toInt()
                     << "doctor_id:" << qAll.value("doctor_id").toInt()
                     << "order_content:" << qAll.value("order_content").toString()
                     << "created_at:" << qAll.value("created_at").toString();
        }

        return results;
    }

    // 第一行已被 query.next() 移动，需要先处理这一行
    do {
        QMap<QString, QVariant> order;
        order["order_id"] = query.value("order_id");
        order["created_at"] = query.value("created_at");
        order["doctor_name"] = query.value("doctor_name");
        order["department"] = query.value("department");
        order["order_content"] = query.value("order_content");

        qDebug() << "[getOrdersByPatient] Loaded order:"
                 << order["order_id"].toInt()
                 << order["doctor_name"].toString()
                 << order["department"].toString()
                 << order["order_content"].toString();

        results.append(order);
    } while (query.next());

    qDebug() << "[getOrdersByPatient] Total orders loaded:" << results.size();

    return results;
}

