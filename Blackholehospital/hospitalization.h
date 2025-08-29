#ifndef HOSPITALIZATION_H
#define HOSPITALIZATION_H

#include <QDialog>

struct HospitalizationInfo {
    QString doctor;
    QString room;
    QString bed;
    QString admissionDate;
};

namespace Ui {
class hospitalization;
}

class hospitalization : public QDialog
{
    Q_OBJECT

public:
    explicit hospitalization(QWidget *parent = nullptr);
    ~hospitalization();

    void setHospitalizationInfo(const HospitalizationInfo &info); // 设置并显示信息


private:
    Ui::hospitalization *ui;
    HospitalizationInfo currentInfo;
};

#endif // HOSPITALIZATION_H
