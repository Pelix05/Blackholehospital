#include "medicinesearch.h"
#include "ui_medicinesearch.h"
#include <QMessageBox>
#include <QPixmap>

medicinesearch::medicinesearch(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medicinesearch)
{
    ui->setupUi(this);

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

    if (!medicineDB.contains(key)) {
        QMessageBox::information(this, "提示", "未找到药品：" + key);
        ui->lblImage->clear();
        ui->txtInfo->clear();
        return;
    }

    medicineinfo drug = medicineDB.value(key);

    // 显示图片
    QPixmap pix(drug.imagePath);
    ui->lblImage->setPixmap(pix.scaled(150, 150, Qt::KeepAspectRatio));

    // 显示信息
    QString text = QString("【药品名称】%1\n【类别】%2\n【规格】%3\n\n"
                           "【使用说明】%4\n\n【注意事项】%5")
                           .arg(drug.name)
                           .arg(drug.category)
                           .arg(drug.spec)
                           .arg(drug.usage)
                           .arg(drug.caution);

    ui->txtInfo->setText(text);
}

