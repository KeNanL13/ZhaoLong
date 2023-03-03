#ifndef HPMSETTINGWIDGET_H
#define HPMSETTINGWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>

namespace Ui {
class HPMSettingWidget;
}

class HPMSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HPMSettingWidget(QWidget *parent = nullptr);
    ~HPMSettingWidget();
    HPMSettingWidget(int num,int index);
    QVector<QLineEdit*>getInputLineList();


private:
    int currentNum;
    int currentIndex;
    Ui::HPMSettingWidget *ui;
    QVector<QLineEdit*>inputLineList;

};

#endif // HPMSETTINGWIDGET_H
