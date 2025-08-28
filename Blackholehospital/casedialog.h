#ifndef CASEDIALOG_H
#define CASEDIALOG_H

#include <QDialog>

namespace Ui {
class casedialog;
}

class casedialog : public QDialog
{
    Q_OBJECT

public:
    explicit casedialog(QWidget *parent = nullptr);
    ~casedialog();

    void setCaseInfo(QString doctor, QString dep, QString date, QString result,QString instructions,QString prescription);

public slots:
        void backbuttonclicked();

private:
    Ui::casedialog *ui;
};

#endif // CASEDIALOG_H
