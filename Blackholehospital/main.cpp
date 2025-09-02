#include "loginwidget.h"
#include "patientmainwindow.h"
#include "SmartMedicalDB.h"
#include "databasemanager.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!SmartMedicalDB::createDatabaseAndTables()) {
        return -1; // 初始化失败，退出
    }

    LoginWidget w;
    w.show();
    return a.exec();
}

