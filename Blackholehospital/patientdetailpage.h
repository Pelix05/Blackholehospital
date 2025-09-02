#ifndef PATIENTDETAILPAGE_H
#define PATIENTDETAILPAGE_H

#include <QWidget>
#include <QString>

namespace Ui {
class PatientDetailPage;
}

class PatientDetailPage : public QWidget
{
    Q_OBJECT

public:
    explicit PatientDetailPage(const QString &patientInfo);
    ~PatientDetailPage();

private slots:
    void onSaveButtonClicked();
    void onPrescriptionButtonClicked();
    void onBackButtonClicked();

private:
    Ui::PatientDetailPage *ui;
    QString patientInfo;
};

#endif // PATIENTDETAILPAGE_H
