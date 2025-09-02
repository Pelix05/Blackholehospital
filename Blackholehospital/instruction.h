#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include <QDialog>
#include <QStandardItemModel>
#include <QStyledItemDelegate>

namespace Ui {
class instruction;
}

class instruction : public QDialog
{
    Q_OBJECT

public:
    explicit instruction(qlonglong patientId, QWidget *parent = nullptr);
    ~instruction();

private:
    Ui::instruction *ui;
    QStandardItemModel *model;
    qlonglong m_patientId;
    void loadOrders(); // 从数据库加载医嘱
    void addOrder(const QString &content);
};

class NoElideDelegate : public QStyledItemDelegate {
public:
    using QStyledItemDelegate::QStyledItemDelegate;

    void initStyleOption(QStyleOptionViewItem *option, const QModelIndex &index) const override {
        QStyledItemDelegate::initStyleOption(option, index);
        option->textElideMode = Qt::ElideNone;  // 禁止省略
        option->displayAlignment = Qt::AlignLeft | Qt::AlignVCenter; // 左对齐
    }
};


#endif // INSTRUCTION_H
