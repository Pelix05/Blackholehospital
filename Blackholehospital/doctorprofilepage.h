#ifndef DOCTORPROFILEPAGE_H
#define DOCTORPROFILEPAGE_H

#include <QWidget>

namespace Ui {
class doctorprofilepage;
}

class doctorprofilepage : public QWidget
{
    Q_OBJECT

public:
    explicit doctorprofilepage(QWidget *parent = nullptr);
    ~doctorprofilepage();

private slots:
    void onCloseButtonClicked();
    void onChangePhotoClicked();

private:
    Ui::doctorprofilepage *ui;
};

#endif // DOCTORPROFILEPAGE_H
