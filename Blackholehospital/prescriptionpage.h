#ifndef PRESCRIPTIONPAGE_H
#define PRESCRIPTIONPAGE_H

#include <QWidget>
#include <QString>

namespace Ui {
class PrescriptionPage;
}

class PrescriptionPage : public QWidget
{
    Q_OBJECT

public:
    explicit PrescriptionPage(const QString &patientInfo, QWidget *parent = nullptr);
    ~PrescriptionPage();

private slots:
    void onSaveButtonClicked();
    void onBackButtonClicked();

private:
    Ui::PrescriptionPage *ui;
    QString patientInfo;
};

#endif // PRESCRIPTIONPAGE_H
