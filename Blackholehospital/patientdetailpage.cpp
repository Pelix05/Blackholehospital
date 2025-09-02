#include "patientdetailpage.h"
#include "ui_patientdetailpage.h"
#include "prescriptionpage.h"
#include <QMessageBox>

PatientDetailPage::PatientDetailPage(const QString &patientInfo)
    :
     ui(new Ui::PatientDetailPage)
    , patientInfo(patientInfo)
{
    ui->setupUi(this);
    setWindowTitle("PATIENT CASE DETAIL");
    resize(1900, 850);



    // 设置患者信息
    ui->infoLabel->setText(patientInfo);

    // --- THEME STYLE ---
        this->setStyleSheet("background-color: qlineargradient("
                            "x1: 0, y1: 0, x2: 1, y2: 1,"
                            "stop: 0 #e6f7ff, stop: 1 #ffffff);");

        // Title Label (misal infoLabel atau bikin label judul terpisah)
        ui->infoLabel->setStyleSheet("QLabel {"
                                     "color: #0066cc;"
                                     "font-size: 22px;"
                                     "font-weight: bold;"
                                     "background-color: transparent;"
                                     "}");

        // Style tombol
        QString mainButtonStyle =
            "QPushButton {"
            "   background-color: #3498db;"
            "   color: white;"
            "   font-size: 16px;"
            "   padding: 8px 20px;"
            "   border-radius: 10px;"
            "}"
            "QPushButton:hover { background-color: #2980b9; }"
            "QPushButton:pressed { background-color: #1f6391; }";

        QString backButtonStyle =
            "QPushButton {"
            "   background-color: #e74c3c;"
            "   color: white;"
            "   font-size: 16px;"
            "   padding: 8px 20px;"
            "   border-radius: 10px;"
            "}"
            "QPushButton:hover { background-color: #c0392b; }"
            "QPushButton:pressed { background-color: #962d22; }";

        QString textEditStyle =
            "QTextEdit {"
            "   background-color: #ffffff;"
            "   border: 2px solid #3498db;"
            "   border-radius: 8px;"
            "   padding: 6px;"
            "   font-size: 14px;"
            "   color: #333;"
            "}"
            "QTextEdit:focus {"
            "   border: 2px solid #2980b9;"
            "   background-color: #f0f9ff;"
            "}";

        // Apply ke text edit yang ada di UI
        if (ui->caseRecord) {
            ui->caseRecord->setStyleSheet(textEditStyle);
        }
        if (ui->adviceEdit) {
            ui->adviceEdit->setStyleSheet(textEditStyle);
        }

    // 连接信号槽
        if (ui->btnSave && ui->btnPrescription && ui->btnBack) {
                ui->btnSave->setStyleSheet(mainButtonStyle);
                ui->btnPrescription->setStyleSheet(mainButtonStyle);
                ui->btnBack->setStyleSheet(backButtonStyle);

                connect(ui->btnSave, &QPushButton::clicked, this, &PatientDetailPage::onSaveButtonClicked);
                connect(ui->btnPrescription, &QPushButton::clicked, this, &PatientDetailPage::onPrescriptionButtonClicked);
                connect(ui->btnBack, &QPushButton::clicked, this, &PatientDetailPage::onBackButtonClicked);
            }
}

PatientDetailPage::~PatientDetailPage()
{
    delete ui;
}

void PatientDetailPage::onSaveButtonClicked()
{
    QMessageBox::information(this, "SAVE", "Doctor's Advice has been saved！");
}

void PatientDetailPage::onPrescriptionButtonClicked()
{
    PrescriptionPage *presPage = new PrescriptionPage(patientInfo);
    presPage->show();
}

void PatientDetailPage::onBackButtonClicked()
{
    this->close();
}
