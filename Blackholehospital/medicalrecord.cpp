#include "medicalrecord.h"
#include "ui_medicalrecord.h"
#include "casedialog.h"
#include <QStandardItem>
#include <QMessageBox>

medicalrecord::medicalrecord(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::medicalrecord)
{
    ui->setupUi(this);

    model = new QStandardItemModel(this);
    model -> setHorizontalHeaderLabels({"序号", "日期", "科室", "主治医生", "工号"});


    addcase(1, "2023-09-01", "内科", "张三", "1001");
    addcase(2, "2023-09-05", "外科", "李四", "1002");

    ui->tableView->setModel(model);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(ui->tableView,&QTableView::doubleClicked,
            this,&medicalrecord::doubleclicked);

}

medicalrecord::~medicalrecord()
{
    delete ui;
}

void medicalrecord::addcase(int id, QString date, QString dep, QString doctor, QString job)
{
    QList<QStandardItem*> row;
        row << new QStandardItem(QString::number(id))
            << new QStandardItem(date)
            << new QStandardItem(dep)
            << new QStandardItem(doctor)
            << new QStandardItem(job);
        model->appendRow(row); //add role to model
}


void medicalrecord::doubleclicked(const QModelIndex &index){

    int row = index.row();
    QString doctor = model -> item(row,3)-> text();
    QString dep = model -> item(row,2)-> text();
    QString date = model -> item(row,1)-> text();
    // 使用模拟数据代替数据库查询
    QString instructions = generateInstructions(dep);
    QString prescription = generatePrescription(dep);


    casedialog dialog(this);
    dialog.setCaseInfo(doctor, dep, date, "这是病例诊断结果........");
    dialog.exec();
}

// 生成模拟医嘱
QString medicalrecord::generateInstructions(const QString &department)
{
    if (department == "内科") {
        return "1. 注意休息，多饮水\n2. 按时服药，每日3次\n3. 如有高热不退或症状加重，请及时复诊\n4. 饮食清淡，避免辛辣刺激食物";
    } else if (department == "外科") {
        return "1. 患肢制动，抬高患肢\n2. 伤后48小时内冷敷，48小时后热敷\n3. 按时服用消肿止痛药物\n4. 一周后复诊，如有肿胀加重请及时就医";
    } else if (department == "眼科") {
        return "1. 按时滴眼药水，每日4次\n2. 注意手部卫生，避免揉眼\n3. 毛巾、脸盆等用品单独使用，防止交叉感染\n4. 症状消失后继续用药3天以巩固疗效";
    } else {
        return "1. 注意休息，避免劳累\n2. 按时服药\n3. 如有不适，请及时就医\n4. 定期复查";
    }
}

// 生成模拟处方
QString medicalrecord::generatePrescription(const QString &department)
{
    if (department == "内科") {
        return "1. 阿莫西林胶囊 0.5g × 24粒\n   用法：口服，每次2粒，每日3次\n2. 复方甘草片 × 1瓶\n   用法：口服，每次3片，每日3次\n3. 布洛芬缓释胶囊 0.3g × 12粒\n   用法：口服，每次1粒，每日2次（发热时服用）";
    } else if (department == "外科") {
        return "1. 云南白药气雾剂 × 1瓶\n   用法：外用，每日3-4次\n2. 双氯芬酸钠肠溶片 25mg × 24片\n   用法：口服，每次1片，每日3次\n3. 活血止痛胶囊 × 36粒\n   用法：口服，每次2粒，每日3次";
    } else if (department == "眼科") {
        return "1. 左氧氟沙星滴眼液 5ml × 1支\n   用法：滴眼，每次1-2滴，每日4次\n2. 阿昔洛韦滴眼液 8ml × 1支\n   用法：滴眼，每次1-2滴，每日4次\n3. 玻璃酸钠滴眼液 0.1% × 1支\n   用法：滴眼，每次1滴，每日4次";
    } else {
        return "1. 维生素C片 100mg × 30片\n   用法：口服，每次1片，每日3次\n2. 复合维生素B片 × 30片\n   用法：口服，每次1片，每日3次";
    }
}
