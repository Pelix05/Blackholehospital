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
    explicit appointmentlistpage(const QString doctorId, QWidget *parent = nullptr);
    ~appointmentlistpage();

signals:
    void backToDoctor();

private:
    Ui::appointmentlistpage *ui;
    void populateAppointmentData();
    void on_btnBack_clicked();
    void onTableCellClicked(int row, int column);
    QString m_doctorId;
};

#endif // APPOINTMENTLISTPAGE_H
