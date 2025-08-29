#ifndef EDITPROFILE_H
#define EDITPROFILE_H

#include <QWidget>
#include "personalprofile.h"

namespace Ui {
class editprofile;
}

class editprofile : public QWidget
{
    Q_OBJECT

public:
    explicit editprofile(QWidget *parent = nullptr);
    ~editprofile();

    void setpatientinfo(const personalinfo &info);
    personalinfo getupdatedinfo()const;   //get updated indo

signals:
    void confirmupdate(const personalinfo &info);
    void cancel();

private:
    Ui::editprofile *ui;
    personalinfo currentinfo;
};

#endif // EDITPROFILE_H
