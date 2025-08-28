#ifndef APPOINTMENTLISTPAGE_H
#define APPOINTMENTLISTPAGE_H

#include <QWidget>

namespace Ui {
class appointmentlistpage;
}

class appointmentlistpage : public QWidget
{
    Q_OBJECT

public:
    explicit appointmentlistpage(QWidget *parent = nullptr);
    ~appointmentlistpage();

signals:
    void backToDoctor();

private:
    Ui::appointmentlistpage *ui;
    void populateAppointmentData();
    void on_btnBack_clicked();
};

#endif // APPOINTMENTLISTPAGE_H
