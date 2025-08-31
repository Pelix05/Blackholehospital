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
            password VARCHAR(255) NOT NULL,
            email VARCHAR(100) NOT NULL,
            phone VARCHAR(11) NOT NULL,
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
            emergency_contact VARCHAR(50),
            FOREIGN KEY (patient_id) REFERENCES users(user_id) ON DELETE CASCADE
        );
    )")) return false;

    // 3. 医生信息表
    if (!execQuery(query, R"(
        CREATE TABLE IF NOT EXISTS doctors (
            doctor_id INTEGER PRIMARY KEY AUTOINCREMENT,
            department VARCHAR(50) NOT NULL,
            title VARCHAR(50),
            intro TEXT,
            work_schedule VARCHAR(100),
            max_patients INTEGER DEFAULT 30,
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
            status TEXT CHECK(status IN ('pending','confirmed','canceled')) DEFAULT 'pending',
            created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
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
