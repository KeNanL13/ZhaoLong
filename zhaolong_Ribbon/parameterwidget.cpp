#include "parameterwidget.h"
#include "ui_parameterwidget.h"
#include <QDebug>

ParameterWidget::ParameterWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
}

ParameterWidget::ParameterWidget(int type, QStringList parameters,QWidget *parent ):
    QWidget(parent),
    ui(new Ui::ParameterWidget)
{
    ui->setupUi(this);
    QStringList parameterNames;
    parameterNames.clear();
    switch (type) {
    case 0:parameterNames<<"线缆间距"<<"距地高度"<<"半径1"<<"半径2"<<"线缆长度"<<"入射场强"<<"极化方向"
                        <<"入射方向thetaE"<<"入射方向phiP";
        break;
    case 1:parameterNames<<"线缆长度"<<"缠绕系数"<<"间距"<<"离地高度"<<"半径1"<<"半径2"<<"入射场强"
                        <<"极化方向"<<"入射方向thetaE"<<"入射方向phiP";
        break;
    case 2:parameterNames<<"线缆半径"<<"信号线距离"<<"屏蔽层半径"<<"PE相对介电常数"<<"损耗正切"<<"屏蔽层厚度"
                        <<"线缆总长"<<"屏蔽层电导率"<<"线缆电导率"<<"沟槽宽度"<<"最小频率"<<"最大频率"<<"夹具";
        break;
    default:
        break;
    }
    ui->tableWidget->setColumnCount(parameterNames.size());
    ui->tableWidget->setHorizontalHeaderLabels(parameterNames);
    ui->tableWidget->insertRow(0);
//    ui->tableWidget->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    for(int i=0;i<parameters.size();i++)
    {
        qDebug()<<parameters[i];
        ui->tableWidget->setItem(0,i,new QTableWidgetItem(parameters[i]));
        ui->tableWidget->item(0,i)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }
}

ParameterWidget::~ParameterWidget()
{
    delete ui;
}
