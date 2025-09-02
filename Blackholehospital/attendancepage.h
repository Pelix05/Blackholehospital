#ifndef ATTENDANCEPAGE_H
#define ATTENDANCEPAGE_H

#include <QWidget>

namespace Ui {
class attendancepage;
}

class attendancepage : public QWidget
{
    Q_OBJECT

public:
    explicit attendancepage(QWidget *parent = nullptr);
    ~attendancepage();

signals:
    void backButtonClicked();  // Signal untuk tombol back

private slots:
    void onCheckInClicked();
    void onCheckOutClicked();
    void onLeaveRequestClicked();
    void onBackClicked();

private:
    Ui::attendancepage *ui;
    int currentDoctorId = 0; // pastikan ini di-set dari login

        // Tambahkan deklarasi fungsi private ini
        void saveAttendanceToDB(const QString &reason, const QString &checkIn = "", const QString &checkOut = "");
        void loadLastAttendance();
};

#endif // ATTENDANCEPAGE_H
