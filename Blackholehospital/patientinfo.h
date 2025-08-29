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
    explicit patientinfo(QWidget *parent = nullptr);
    ~patientinfo();

    void setpatientinfo(const personalinfo &info);

signals:
    void editrequest();

private:
    Ui::patientinfo *ui;
    personalinfo currentinfo;
};

#endif // PATIENTINFO_H
