#include "SmartMedicalDB.h"


bool SmartMedicalDB::createDatabaseAndTables()
{
    // 连接 SQLite 数据库（文件名为 SmartMedicalDB.db）
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("SmartMedicalDB.db");

    if (!db.open()) {
        qDebug() << "无法打开数据库:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;

    // 1. 用户表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS users (
            user_id INTEGER PRIMARY KEY AUTOINCREMENT,
            username VARCHAR(50) NOT NULL UNIQUE,
            id_card VARCHAR(18) NOT NULL UNIQUE,
            password VARCHAR(255) NOT NULL,
            gender TEXT CHECK(gender IN ('M','F')),
            email VARCHAR(100) NOT NULL,
            phone VARCHAR(11) NOT NULL,
            address VARCHAR(100),
            user_type TEXT CHECK(user_type IN ('Patient','Doctor')) NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP
        );
    )")) return false;

    // 2. 患者信息表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS patients (
            patient_id INTEGER PRIMARY KEY AUTOINCREMENT,
            name VARCHAR(50) NOT NULL,
            gender TEXT CHECK(gender IN ('M','F')),
            birth_date DATE,
            id_card VARCHAR(18) NOT NULL UNIQUE,
            phone VARCHAR(11) NOT NULL,
            email VARCHAR(100) NOT NULL,
            address VARCHAR(100),
            FOREIGN KEY (patient_id) REFERENCES users(user_id) ON DELETE CASCADE
        );
    )")) return false;

    // 3. 医生信息表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS doctors (
            doctor_id INTEGER PRIMARY KEY AUTOINCREMENT,
            name VARCHAR(50) NOT NULL,
            gender TEXT CHECK(gender IN ('M','F')),
            birth_date DATE,
            id_card VARCHAR(18) NOT NULL UNIQUE,
            phone VARCHAR(11) NOT NULL,
            email VARCHAR(100) NOT NULL,
            address VARCHAR(100),
                    department VARCHAR(50),
                   photo TEXT,
                   fee REAL DEFAULT 0,
                   daily_limit INTEGER DEFAULT 0,
            FOREIGN KEY (doctor_id) REFERENCES users(user_id) ON DELETE CASCADE
        );
    )")) return false;


    // 4. 预约表
    if (!execQuery(query, R"(
       CREATE TABLE IF NOT EXISTS appointments (
          appointment_id INTEGER PRIMARY KEY AUTOINCREMENT,
          patient_id INTEGER NOT NULL,
          doctor_id INTEGER NOT NULL,
          appoint_time DATETIME NOT NULL,
          status TEXT DEFAULT 'booked',
          FOREIGN KEY (patient_id) REFERENCES patients(patient_id),
          FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
        );
    )")) return false;

    // 5. 病例表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS medical_records (
            record_id INTEGER PRIMARY KEY AUTOINCREMENT,
            patient_id INTEGER NOT NULL,
            doctor_id INTEGER NOT NULL,
            diagnose TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (patient_id) REFERENCES patients(patient_id),
            FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
        );
    )")) return false;

    // 6. 处方表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS prescriptions (
            prescription_id INTEGER PRIMARY KEY AUTOINCREMENT,
            record_id INTEGER NOT NULL UNIQUE,
            content TEXT NOT NULL,
            FOREIGN KEY (record_id) REFERENCES medical_records(record_id) ON DELETE CASCADE
        );
    )")) return false;

    // 7. 医嘱表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS doctor_orders (
            order_id INTEGER PRIMARY KEY AUTOINCREMENT,
            doctor_id INTEGER NOT NULL,
            patient_id INTEGER NOT NULL,
            order_content TEXT NOT NULL,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id),
            FOREIGN KEY (patient_id) REFERENCES patients(patient_id)
        );
    )")) return false;

    // 8. 住院信息表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS hospitalizations (
            hospitalization_id INTEGER PRIMARY KEY AUTOINCREMENT,
            patient_id INTEGER NOT NULL,
            doctor_id INTEGER NOT NULL,
            ward_number VARCHAR(20) NOT NULL,
            bed_number VARCHAR(20) NOT NULL,
            admit_date DATE NOT NULL,
            discharge_date DATE,
            FOREIGN KEY (patient_id) REFERENCES patients(patient_id),
            FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
        );
    )")) return false;

    // 9. Attendance log table
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS attendance_log (
            log_id INTEGER PRIMARY KEY AUTOINCREMENT,
            doctor_id INTEGER NOT NULL,
            check_in_time DATETIME,
            check_out_time DATETIME,
            reason TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
        );
    )")) return false;

    // 4. 医生排班
    if (!query.exec(R"(
        CREATE TABLE IF NOT EXISTS doctor_schedules (
            schedule_id INTEGER PRIMARY KEY AUTOINCREMENT,
            doctor_id INTEGER NOT NULL,
            hospital TEXT,
            department TEXT,
            clinic TEXT,
            job_number TEXT,
            work_date DATE,
            start_time TIME,
            end_time TIME,
            fee REAL,
            limit_per_day INTEGER,
            supports_appointment BOOLEAN,
            booked_count INTEGER DEFAULT 0,
            FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
        );
    )")) return false;

    // 9. Attendance log table
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS attendance_log (
            log_id INTEGER PRIMARY KEY AUTOINCREMENT,
            doctor_id INTEGER NOT NULL,
            check_in_time DATETIME,
            check_out_time DATETIME,
            reason TEXT,
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
            FOREIGN KEY (doctor_id) REFERENCES doctors(doctor_id)
        );
    )")) return false;

    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS medicines (
            medicine_id INTEGER PRIMARY KEY AUTOINCREMENT,
            name TEXT NOT NULL UNIQUE,
            category TEXT,
            spec TEXT,
            usage TEXT,
            caution TEXT,
            imagePath TEXT
        );
    )")) return false;

    // Insert dummy data if empty
    query.exec("SELECT COUNT(*) FROM medicines;");
    if (query.next() && query.value(0).toInt() == 0) {
        execQuery(query, R"(
            INSERT INTO medicines (name, category, spec, usage, caution, imagePath)
            VALUES ('Amoxicillin Capsule', 'Antibiotic', '500mg*20', 'Oral, 500mg per dose, 3 times daily after meals', 'Contraindicated in patients allergic to penicillin; use as prescribed', ':/images/amoxicillin.png');
        )");
        execQuery(query, R"(
            INSERT INTO medicines (name, category, spec, usage, caution, imagePath)
            VALUES ('Vitamin C Tablet', 'Vitamin', '100mg*100', 'Oral, 100mg per dose, 1-2 times daily', 'Avoid long-term excessive use; caution in patients with kidney stones', ':/images/vitaminC.png');
        )");
        execQuery(query, R"(
            INSERT INTO medicines (name, category, spec, usage, caution, imagePath)
            VALUES ('Ibuprofen Tablet', 'Pain Reliever', '200mg*24', 'Oral, 200-400mg per dose, 3 times daily', 'Avoid in patients with gastric ulcers; contraindicated in pregnancy', ':/images/ibuprofen.png');
        )");

    }


    qDebug() << "✅ 数据库和表已成功创建！";
    return true;
}

bool SmartMedicalDB::execQuery(QSqlQuery &query, const QString &sql)
{
    if (!query.exec(sql)) {
        qDebug() << "执行失败:" << sql;
        qDebug() << "错误信息:" << query.lastError().text();
        return false;
    }
    return true;
}
