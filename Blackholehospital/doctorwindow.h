#ifndef DOCTORWINDOW_H
#define DOCTORWINDOW_H

#include <QWidget>

namespace Ui {
class doctorwindow;
}

class doctorwindow : public QWidget
{
    Q_OBJECT

public:
    explicit doctorwindow(QWidget *parent = nullptr);
    ~doctorwindow();

private slots:
   void onAppointmentInfoClicked();
   void onEditCaseClicked();
   void onEditPrescriptionClicked();
   void onEditProfileClicked();
   void onPlatformClicked();
   void onAttendanceClicked();
   void onExitClicked();


private:
    Ui::doctorwindow *ui;
};

#endif // DOCTORWINDOW_H
