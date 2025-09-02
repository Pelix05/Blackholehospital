#include "instruction.h"
#include "ui_instruction.h"
#include "databasemanager.h"


instruction::instruction(qlonglong patientId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::instruction),
    model(new QStandardItemModel(this)),
    m_patientId(patientId)
{
    ui->setupUi(this);
    this->setWindowTitle("DOCTOR'S ADVICE");

    model ->setHorizontalHeaderLabels ({"内容"});
    ui -> tableView ->setModel(model);
    ui->tableView->setWordWrap(true);
    ui->tableView->setColumnWidth(0, 1400);
    ui->tableView->setItemDelegate(new NoElideDelegate(ui->tableView));
    ui->tableView->resizeRowsToContents();  // 自动调整行高


    ui->tableView->horizontalHeader()->setStyleSheet(
                "QTableView {"
                "   background-color: white;"
                "   border: 4px solid #0066cc;"
                "   border-radius: 4px;"
                "   gridline-color: #cce6ff;"
                "   selection-background-color: #cce6ff;"
                "   selection-color: #003366;"
                "}"
                "QHeaderView::section {"
                "   background-color: #0066cc;"
                "   color: white;"
                "   padding: 2px;"
                "   border: none;"
                "   font-weight: bold;"
                "   font-size: 16px;"
                "}"
                "QTableCornerButton::section {"
                "   background-color: #0066cc;"
                "   border: none;"
                "}"
                "QTableView::item {"
                "   padding: 16px;"
                "}"
                "QTableView::item:selected {"
                "   background-color: #99ccff;"
                "   color: black;"
                "}"
    );


    loadOrders();

}

instruction::~instruction()
{
    delete ui;
}

// 从数据库加载医嘱
void instruction::loadOrders()
{
    model->removeRows(0, model->rowCount());
    qDebug() << "[DEBUG] About to call getOrdersByPatient with patientId =" << m_patientId;
    QList<QMap<QString, QVariant>> orders = DatabaseManager::instance().getOrdersByPatient(m_patientId);

    for (auto &order : orders) {
        QString content = order["order_content"].toString();
        addOrder(content);

    }
}

// 添加一行医嘱
void instruction::addOrder(const QString &content)
{
    QList<QStandardItem*> row;
    row << new QStandardItem(content);
    model->appendRow(row);
}
