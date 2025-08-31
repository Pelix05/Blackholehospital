#ifndef SMARTMEDICALDB_H
#define SMARTMEDICALDB_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QDebug>

class SmartMedicalDB
{
public:
    // 初始化数据库并创建所有表
    static bool createDatabaseAndTables();

private:
    // 辅助函数：执行 SQL 并打印错误
    static bool execQuery(QSqlQuery &query, const QString &sql);
};

#endif // SMARTMEDICALDB_H
