#include "hpmsettingwidget.h"
#include "ui_hpmsettingwidget.h"
#include <QDebug>

HPMSettingWidget::HPMSettingWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HPMSettingWidget)
{
    ui->setupUi(this);
}

HPMSettingWidget::~HPMSettingWidget()
{
    delete ui;
}

HPMSettingWidget::HPMSettingWidget(int num, int index):
    currentNum(num),
    currentIndex(index),
    ui(new Ui::HPMSettingWidget)
{
    ui->setupUi(this);
//    if(index>4)
//    {
//        return;
//    }
    ui->stackedWidget->setCurrentIndex(currentIndex);
    int t=ui->stackedWidget->count();
    for(int i=0;i<t;i++)
    {
        if(i!=currentIndex)
        {
            QObjectList objects = ui->stackedWidget->widget(i)->children();
            for(int j=0;j<objects.size();j++)
            {
                QWidget *content_widget = qobject_cast<QWidget *>(objects.at(j));
                if (content_widget)
                {
                    content_widget->setVisible(i == false);
                    break; // 这里只是跳出当前页的for循环
                }
            }
            ui->stackedWidget->widget(i)->setVisible(false);
        }

    }
    QString numText=QString("脉冲%1").arg(num)+"：";

    switch (index) {
    case 0:ui->label->setText(numText+"双指数波形");
        inputLineList<<ui->lineEdit_0_2<<ui->lineEdit_0_3<<ui->lineEdit_0_4;
        break;
    case 1:ui->label->setText(numText+"三指数脉冲");
        inputLineList<<ui->lineEdit_1_2<<ui->lineEdit_1_3<<ui->lineEdit_1_4
                    <<ui->lineEdit_1_5<<ui->lineEdit_1_6<<ui->lineEdit_1_7<<ui->lineEdit_1_8
                   <<ui->lineEdit_1_9<<ui->lineEdit_1_10;
        break;
    case 2:ui->label->setText(numText+"高斯脉冲");
        inputLineList<<ui->lineEdit_2_2<<ui->lineEdit_2_3<<ui->lineEdit_2_4;
        break;
    case 3:ui->label->setText(numText+"方波脉冲");
        inputLineList<<ui->lineEdit_3_2<<ui->lineEdit_3_3<<ui->lineEdit_3_4;
        break;
    case 4:ui->label->setText(numText+"正弦脉冲");
        inputLineList<<ui->lineEdit_5_1<<ui->lineEdit_5_2;
        break;
    case 5:ui->label->setText(numText+"自定义脉冲");
        inputLineList<<ui->lineEdit_4_1<<ui->lineEdit_4_3
                    <<ui->lineEdit_4_5<<ui->lineEdit_4_6;
        break;
    default:
        break;
    }
    ui->toolButton->setCheckable(true);
    connect(ui->toolButton,&QToolButton::clicked,this,[=](){
        ui->stackedWidget->setVisible(!ui->toolButton->isChecked());
    });
}

QVector<QLineEdit *> HPMSettingWidget::getInputLineList()
{
    return inputLineList;
}

