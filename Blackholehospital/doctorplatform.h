#ifndef DOCTORPLATFORM_H
#define DOCTORPLATFORM_H

#include <QWidget>

namespace Ui {
class doctorplatform;
}

class doctorplatform : public QWidget
{
    Q_OBJECT

public:
    explicit doctorplatform(QWidget *parent = nullptr);
    ~doctorplatform();

signals:
    void backButtonClicked();  // Signal untuk tombol back

private slots:
    void onSendMessageClicked();
    void onDoctorSelected();
    void onBackClicked();

private:
    Ui::doctorplatform *ui;
};

#endif // DOCTORPLATFORM_H
