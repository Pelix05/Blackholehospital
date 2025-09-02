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
    explicit casedialog(QWidget *parent = nullptr, qlonglong patientId = 1); // 新增
    explicit casedialog(qlonglong patientId, QString doctor, QString dep, QString date, QString result, QWidget *parent = nullptr);
    explicit casedialog(QString doctor, QString dep, QString date, QString result, QWidget *parent = nullptr);
    ~casedialog();

    void setCaseInfo(QString doctor, QString dep, QString date, QString result);

public slots:
        void backbuttonclicked();

private:
    Ui::casedialog *ui;
    qlonglong m_patientId;
};

#endif // CASEDIALOG_H
