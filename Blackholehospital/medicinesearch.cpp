#include "medicinesearch.h"
#include "ui_medicinesearch.h"
#include <QMessageBox>
#include <QPixmap>
#include <QSqlQuery>
#include <QSqlError>


medicinesearch::medicinesearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medicinesearch)
{
    ui->setupUi(this);

    // ====== Stylesheet utama ======
    this->setStyleSheet(R"(
        QWidget {
            background-color: #f8f9fa;
            font-family: "Segoe UI";
            font-size: 14px;
            color: #333;
        }

        QLabel {
            font-size: 14px;
            color: #444;
            font-weight: 500;
        }

        QLineEdit {
            border: 1px solid #ccc;
            border-radius: 8px;
            padding: 6px 10px;
            background-color: #fff;
        }
        QLineEdit:focus {
            border: 1px solid #0078d7;
            background-color: #eef6ff;
        }

        QPushButton {
            border: none;
            border-radius: 10px;
            padding: 8px 16px;
            font-size: 14px;
            font-weight: 500;
            background-color: #0078d7;
            color: white;
        }
        QPushButton:hover {
            background-color: #005fa3;
        }

        QTextEdit {
            border: 1px solid #ccc;
            border-radius: 8px;
            padding: 8px;
            background-color: #fff;
        }

        QScrollArea {
            border: 1px solid #bbb;
            border-radius: 10px;
            background: #ffffff;
        }
    )");


     initmedicineDB();

     connect(ui->btnSearch, &QPushButton::clicked,
                 this, &medicinesearch::onSearch);

     // 默认信息清空
     ui->lblImage->clear();
     ui->txtInfo->clear();
}

medicinesearch::~medicinesearch()
{
    delete ui;
}

void medicinesearch::initmedicineDB()
{
    // 假数据
    medicineinfo amoxicillin = {
        "阿莫西林胶囊",
        "抗生素",
        "0.5g*20粒",
        "口服，每次 0.5g，每日 3 次，饭后服用",
        "对青霉素过敏者禁用；请遵医嘱服用",
        ":/images/amoxicillin.png"   // 资源文件里的图片
    };
    medicineDB.insert("阿莫西林", amoxicillin);
    medicineDB.insert("阿莫西林胶囊", amoxicillin);

    medicineinfo vitaminC = {
        "维生素C片",
        "维生素",
        "100mg*100片",
        "口服，每次 100mg，每日 1-2 次",
        "避免长期大剂量使用；肾结石患者慎用",
        ":/images/vitaminC.png"
    };
    medicineDB.insert("维生素C", vitaminC);
    medicineDB.insert("维生素C片", vitaminC);
}

void medicinesearch::onSearch()
{
    QString key = ui->editName->text().trimmed();
    if (key.isEmpty()) {
        QMessageBox::warning(this, "提示", "请输入药品名称！");
        return;
    }

    QSqlQuery query;
    query.prepare("SELECT name, category, spec, usage, caution, imagePath FROM medicines WHERE name LIKE :name");
    query.bindValue(":name", "%" + key + "%");

    if (!query.exec()) {
        QMessageBox::critical(this, "错误", "数据库查询失败: " + query.lastError().text());
        return;
    }

    if (!query.next()) {
        QMessageBox::information(this, "提示", "未找到药品：" + key);
        ui->lblImage->clear();
        ui->txtInfo->clear();
        return;
    }

    QString name = query.value(0).toString();
    QString category = query.value(1).toString();
    QString spec = query.value(2).toString();
    QString usage = query.value(3).toString();
    QString caution = query.value(4).toString();
    QString imagePath = query.value(5).toString();

    // 显示图片
    QPixmap pix(imagePath);
    ui->lblImage->setPixmap(pix.scaled(300, 300, Qt::KeepAspectRatio));

    // 显示信息
    QString text = QString("【药品名称】%1\n【类别】%2\n【规格】%3\n\n"
                           "【使用说明】%4\n\n【注意事项】%5")
                           .arg(name)
                           .arg(category)
                           .arg(spec)
                           .arg(usage)
                           .arg(caution);

    ui->txtInfo->setText(text);
}


