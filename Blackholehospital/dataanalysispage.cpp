#include "dataanalysispage.h"
#include "ui_dataanalysispage.h"
#include <QHBoxLayout>
#include <QTableWidget>
#include <QHeaderView>
#include <QVector>
#include <QPointF>
#include <QTime>
#include <QtGlobal>

DataAnalysisPage::DataAnalysisPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DataAnalysisPage)
{
    ui->setupUi(this);
    setWindowTitle("数据分析页面");
    resize(600, 400);

    // 创建表格显示数据
    QTableWidget *table = new QTableWidget(this);
    table->setRowCount(11);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels(QStringList() << "X值" << "Y值");

    // 生成随机数据
    qsrand(static_cast<uint>(QTime::currentTime().msec()));
    QVector<QPointF> dataPoints;
    for(int i = 0; i <= 10; ++i) {
        int yValue = qrand() % 100;
        dataPoints.append(QPointF(i, yValue));

        // 填充表格
        QTableWidgetItem *xItem = new QTableWidgetItem(QString::number(i));
        QTableWidgetItem *yItem = new QTableWidgetItem(QString::number(yValue));
        table->setItem(i, 0, xItem);
        table->setItem(i, 1, yItem);
    }

    // 调整表格列宽
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 将表格添加到布局
    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(table);
    setLayout(layout);
}

DataAnalysisPage::~DataAnalysisPage()
{
    delete ui;
}
