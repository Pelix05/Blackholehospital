#ifndef DATAANALYSISPAGE_H
#define DATAANALYSISPAGE_H

#include <QWidget>

namespace Ui {
class DataAnalysisPage;
}

class DataAnalysisPage : public QWidget
{
    Q_OBJECT

public:
    explicit DataAnalysisPage(QWidget *parent = nullptr);
    ~DataAnalysisPage();

private:
    Ui::DataAnalysisPage *ui;
};

#endif // DATAANALYSISPAGE_H
