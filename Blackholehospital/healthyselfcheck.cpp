#include "healthyselfcheck.h"
#include "ui_healthyselfcheck.h"
#include <QMessageBox>

healthyselfcheck::healthyselfcheck(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::healthyselfcheck)
{
    ui->setupUi(this);
    setWindowTitle("Healthy Self Check");
    // Background gradient
        this->setStyleSheet("background-color: qlineargradient("
                            "x1: 0, y1: 0, x2: 1, y2: 1,"
                            "stop: 0 #e6f7ff, stop: 1 #ffffff);");

        // Title style (misal ui->titleLabel)
        if (ui->lTitle) {
            ui->lTitle->setStyleSheet("QLabel {"
                                          "color: #0066cc;"
                                          "font-size: 28px;"
                                          "font-weight: bold;"
                                          "background-color: transparent;"
                                          "}");
        }

        // ScrollArea frame style
        if (ui->scrollArea) {
            ui->scrollArea->setStyleSheet(
                "QScrollArea {"
                "   background-color: #ffffff;"
                "   border: 4px solid #3498db;"
                "   border-radius: 14px;"
                "}"
                "QScrollBar:vertical {"
                "   background: #ecf0f1;"
                "   width: 12px;"
                "   margin: 0px 0px 0px 0px;"
                "   border-radius: 6px;"
                "}"
                "QScrollBar::handle:vertical {"
                "   background: #3498db;"
                "   border-radius: 6px;"
                "   min-height: 20px;"
                "}"
                "QScrollBar::handle:vertical:hover {"
                "   background: #2980b9;"
                "}"
                "QScrollBar::add-line, QScrollBar::sub-line {"
                "   height: 0px;"
                "   width: 0px;"
                "}"
            );
        }
        // RadioButton style
        QString radioButtonStyle =
            "QRadioButton {"
            "   spacing: 8px;"
            "   font-size: 16px;"
            "   color: #333;"
            "}"
            "QRadioButton::indicator {"
            "   width: 18px;"
            "   height: 18px;"
            "   border: 2px solid #3498db;"
            "   border-radius: 10px;"
            "   background: white;"
            "}"
            "QRadioButton::indicator:checked {"
            "   background-color: #3498db;"
            "   border: 2px solid #2980b9;"
            "}";

        // Apply ke semua radiobutton
        for (auto rb : this->findChildren<QRadioButton*>()) {
            rb->setStyleSheet(radioButtonStyle);
        }

        // CheckBox style
        QString checkBoxStyle =
            "QCheckBox {"
            "   spacing: 8px;"
            "   font-size: 16px;"
            "   color: #333;"
            "}"
            "QCheckBox::indicator {"
            "   width: 20px;"
            "   height: 20px;"
            "   border: 2px solid #3498db;"
            "   border-radius: 4px;"
            "   background: white;"
            "}"
            "QCheckBox::indicator:checked {"
            "   background-color: #3498db;"
            "   image: url(:/icons/checkmark.png);" // kalau ada icon centang
            "}";

        // apply ke semua checkbox (kalau auto-generated pakai Qt Designer, harus set di masing-masing checkbox atau looping)
        for (auto cb : this->findChildren<QCheckBox*>()) {
            cb->setStyleSheet(checkBoxStyle);
        }

        // Submit button style
        if (ui->btnSubmit) {
            ui->btnSubmit->setStyleSheet(
                "QPushButton {"
                "   background-color: #27ae60;"
                "   color: white;"
                "   font-size: 18px;"
                "   padding: 10px 20px;"
                "   border-radius: 10px;"
                "}"
                "QPushButton:hover { background-color: #219150; }"
                "QPushButton:pressed { background-color: #1b7c42; }"
            );
            connect(ui->btnSubmit, &QPushButton::clicked, this, &healthyselfcheck::submit);
        }
}

healthyselfcheck::~healthyselfcheck()
{
    delete ui;
}

void healthyselfcheck::submit(){
    QString gender;
        if (ui->rbMale->isChecked())
            gender = "男";
        else if (ui->rbFemale->isChecked())
            gender = "女";
        else
            gender = "未选择";

        QStringList symptoms;
        if (ui->cbFever->isChecked()) symptoms << "发烧";
        if (ui->cbCough->isChecked()) symptoms << "咳嗽";
        if (ui->cbHeadache->isChecked()) symptoms << "头痛";

        QString result;
        if (symptoms.isEmpty()) {
            result = "您的状态良好，请继续保持健康的生活习惯！";
        } else {
            result = "您选择的症状有：" + symptoms.join("、") +
                     "\n建议及时就医，注意休息和饮食。";
        }

        QMessageBox::information(this, "自测结果",
                                 "性别：" + gender + "\n" + result);
}
