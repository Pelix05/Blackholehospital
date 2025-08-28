#ifndef PATIENTMAINWINDOW_H
#define PATIENTMAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class patientmainwindow; }
QT_END_NAMESPACE

class patientmainwindow : public QMainWindow
{
    Q_OBJECT

public:
    patientmainwindow(QWidget *parent = nullptr);
    ~patientmainwindow();

private slots:
    void register_clicked();
    void medicalrecord_clicked();
    void appointment_clicked();

private:
    Ui::patientmainwindow *ui;
};

#endif // PATIENTMAINWINDOW_H
