#ifndef DOCTORDETIAL_H
#define DOCTORDETIAL_H

#include <QDialog>

namespace Ui {
class doctordetial;
}

class doctordetial : public QDialog
{
    Q_OBJECT

public:
    explicit doctordetial(QWidget *parent = nullptr);
    ~doctordetial();

    // 设置医生信息
    void setDoctorInfo(const QString &jobId,
                       const QString &department,
                       const QString &name,
                       const QString &profile,
                       const QString &photoPath,
                       const QString &workTime,
                       double fee,
                       int limit);

private:
    Ui::doctordetial *ui;
};

#endif // DOCTORDETIAL_H
