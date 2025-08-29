#ifndef MEDICINESEARCH_H
#define MEDICINESEARCH_H

#include <QWidget>
#include <QMap>

namespace Ui {
class medicinesearch;
}

struct medicineinfo {
    QString name;
    QString category;
    QString spec;
    QString usage;
    QString caution;
    QString imagePath;  // 本地图片路径
};

class medicinesearch : public QWidget
{
    Q_OBJECT

public:
    explicit medicinesearch(QWidget *parent = nullptr);
    ~medicinesearch();


private slots:
    void onSearch();


private:
    Ui::medicinesearch *ui;
    QMap<QString, medicineinfo> medicineDB;   // 模拟药品数据库
    void initmedicineDB();                // 初始化测试数据
};

#endif // MEDICINESEARCH_H
