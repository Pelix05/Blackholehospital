#ifndef PATIENTINFO_H
#define PATIENTINFO_H

#include "personalprofile.h"
#include <QWidget>

namespace Ui {
class patientinfo;
}

class patientinfo : public QWidget
{
    Q_OBJECT

public:
    explicit patientinfo(const QString &idCard);
    ~patientinfo();

    void setpatientinfo(const personalinfo &info);

signals:
    void editrequest();

private:
    Ui::patientinfo *ui;
    personalinfo currentinfo;
     QString m_username;

    void loadFromDatabase(const QString &idCard);
};

#endif // PATIENTINFO_H
