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
    explicit registerpage(QWidget *parent = nullptr);
    ~registerpage();

private slots:
    void button_clicked();

private:
    Ui::registerpage *ui;
    QStandardItemModel *model;

    void addDoctor(QString id, QString dep, QString job, QString name,
                   QString time, double fee, int limit, int booked);

};

#endif
