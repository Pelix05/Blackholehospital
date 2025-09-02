#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QStandardItemModel>
#include <QTableView>

namespace Ui {
    class registerpage;
}

class registerpage : public QWidget
{
    Q_OBJECT

public:
    explicit registerpage(const QString &patientIdCard, QWidget *parent = nullptr);
    ~registerpage();

private slots:
    void button_clicked();
    void onDoctorDoubleClicked(const QModelIndex &index);

private:
    Ui::registerpage *ui;
    QStandardItemModel *model;
    QString m_patientIdCard;

    void loadDoctorSchedules();

};

#endif
