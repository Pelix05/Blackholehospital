#include "casedialog.h"
#include "ui_casedialog.h"
#include "instruction.h"
#include "prescription.h"
#include "hospitalization.h"
#include <QDebug>


casedialog::casedialog(QWidget *parent, qlonglong patientId) :
    QDialog(parent),
    ui(new Ui::casedialog)
{
    ui->setupUi(this);
    this->setWindowTitle("CASE DETAIL");

    this->setStyleSheet(
        "QDialog {"
        "   background-color: #fdfdfd;"
        "   border-radius: 12px;"
        "}"
        "QLabel {"
        "   font-size: 14px;"
        "   font-weight: bold;"
        "   color: #333;"
        "}"
        "QTextEdit {"
        "   border: 1px solid #cccccc;"
        "   border-radius: 6px;"
        "   padding: 6px;"
        "   background: #ffffff;"
        "}"
        "QPushButton {"
        "   background-color: #0078D7;"
        "   color: white;"
        "   border-radius: 8px;"
        "   padding: 6px 14px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "   background-color: #005a9e;"
        "}"
    );


    connect(ui->pushButton,&QPushButton::clicked,
            this,&casedialog::backbuttonclicked);

    // 点击 → 弹出医嘱对话框
    connect(ui->insturctions, &QPushButton::clicked, this, [=](){
        instruction dlg(patientId, this);
        dlg.exec();
    });

    connect(ui->prescription, &QPushButton::clicked, this, [=](){
        Prescription dlg(this);
        dlg.exec();
    });

    connect(ui->hospitalization, &QPushButton::clicked, this, [=](){
        hospitalization dlg(this);
        dlg.exec();
    });

    qDebug() << "[casedialog] m_patientId initial:" << m_patientId;

}

// 带参数构造函数，委托给默认构造函数
casedialog::casedialog(QString doctor, QString dep, QString date, QString result, QWidget *parent)
    : casedialog(parent)   // 调用默认构造函数
{
    setCaseInfo(doctor, dep, date, result);
}

casedialog::~casedialog()
{
    delete ui;
}

void casedialog::setCaseInfo(QString doctor, QString dep, QString date, QString result)
{
    ui->labelDoctor->setText("主治医生: " + doctor);
    ui->labelDep->setText("科室: " + dep);
    ui->labelDate->setText("日期: " + date);
    ui->textEditResult->setText(result);

}

void casedialog::backbuttonclicked()
{
    this->hide();
}
