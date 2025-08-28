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
};

#endif // ATTENDANCEPAGE_H
