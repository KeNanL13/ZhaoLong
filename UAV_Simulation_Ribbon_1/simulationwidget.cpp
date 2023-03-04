#include "simulationwidget.h"
#include "ui_simulationwidget.h"
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QDebug>
#include <QParallelAnimationGroup>

SimulationWidget::SimulationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationWidget)
{
    ui->setupUi(this);
    QVBoxLayout * layout=new QVBoxLayout;
    splitter=new QSplitter;
    splitterRight=new QSplitter;
    splitterRight->addWidget(ui->widget_Hpm);
    splitterRight->addWidget(ui->widget_Environment);
    splitterRight->addWidget(ui->widget_Model);
    splitter->addWidget(ui->scrollArea);
    splitter->addWidget(splitterRight);
    QList<int>list;
    list<<1000<<1000<<1000;
    splitterRight->setSizes(list);
    list.clear();
    list<<1000<<3000;
    splitter->setSizes(list);

    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);
    state=splitter->saveState();
    ui->scrollArea->setVisible(false);

}

SimulationWidget::~SimulationWidget()
{
    delete ui;
}

void SimulationWidget::leftWidgetAnimation(int index, bool isOut)
{
    Q_UNUSED(index);
    qDebug()<<"主窗口的宽度是："<<this->width();
    qDebug()<<"右边窗口的宽度是："<<splitterRight->width();
    qDebug()<<"左边窗口的宽度是"<<ui->scrollArea->width();
    int rightWidth=splitterRight->width();
    QPixmap rightPixamap=splitterRight->grab();

    if(isOut)
    {
        ui->scrollArea->setVisible(true);
        splitter->restoreState(state);
    }

    int stacWidth=ui->scrollArea->width();
    int stacHeight=ui->scrollArea->height();
    qDebug()<<stacWidth<<"  "<<splitterRight->width();
    QLabel *labelLeft=new QLabel(this);
//    labelLeft->show();

    labelLeft->resize(stacWidth,stacHeight);

    labelLeft->setPixmap(ui->scrollArea->grab());

    labelLeft->setAttribute(Qt::WA_DeleteOnClose);
    labelLeft->show();
    if(isOut)
    {
     ui->scrollArea->setVisible(false);
    }

    QLabel*labelRight=new QLabel(this);
    labelRight->resize(rightWidth,splitterRight->height());
    labelRight->setPixmap(rightPixamap);
    labelRight->setScaledContents(true);
    labelRight->setAttribute(Qt::WA_DeleteOnClose);
    labelRight->show();
    QRect rectLeft1(-stacWidth,0,stacWidth,stacHeight);
    QRect rectLeft2(0,0,stacWidth,stacHeight);
    QRect rectRight1(0,0,isOut?rightWidth:splitterRight->width()+stacWidth,splitterRight->height());
    QRect rectRight2(stacWidth,0,isOut?rightWidth-stacWidth:splitterRight->width(),splitterRight->height());


    QPropertyAnimation * aniLeft=new QPropertyAnimation(labelLeft,"geometry");
    aniLeft->setDuration(1000);
    aniLeft->setStartValue(isOut?rectLeft1:rectLeft2);
    aniLeft->setEndValue(isOut?rectLeft2:rectLeft1);
    aniLeft->setEasingCurve(QEasingCurve::Linear);

    QPropertyAnimation * aniRight=new QPropertyAnimation(labelRight,"geometry");
    aniRight->setDuration(1000);
    aniRight->setStartValue(isOut?rectRight1:rectRight2);
    aniRight->setEndValue(isOut?rectRight2:rectRight1);
    aniRight->setEasingCurve(QEasingCurve::Linear);



    QParallelAnimationGroup * group=new QParallelAnimationGroup();
    group->addAnimation(aniLeft);
    group->addAnimation(aniRight);

    group->start(QAbstractAnimation::DeleteWhenStopped);
      labelLeft->raise();
      labelRight->raise();

    connect(group,&QParallelAnimationGroup::finished,[=](){
        labelLeft->close();
        labelRight->close();
        state=splitter->saveState();
        if(isOut){
            ui->scrollArea->setVisible(true);
        }
        else {
            ui->scrollArea->setVisible(false);
        }
        splitter->restoreState(state);
    });
}
