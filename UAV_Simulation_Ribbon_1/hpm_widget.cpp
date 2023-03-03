#include "hpm_widget.h"
#include "ui_hpm_widget.h"
#include <hpmsettingwidget.h>

#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QList>
#include <QLineEdit>

HPM_Widget::HPM_Widget(QLineEdit*time,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HPM_Widget),
    m_TimeLine(time)
{
    ui->setupUi(this);

    QVBoxLayout * layout=new QVBoxLayout();
     splitter=new QSplitter();
    splitter->addWidget(ui->scrollArea);
    splitter->addWidget(ui->widget);
    QList<int>list;
    list<<2000<<4000;
    splitter->setSizes(list);

    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);
    state=splitter->saveState();

    ui->scrollArea->setVisible(false);

    //插入图表
    QChartView * chartView=new QChartView();
    QVBoxLayout * layoutChart=new QVBoxLayout;
    layoutChart->setContentsMargins(4,0,2,0);
    layoutChart->addWidget(chartView);
    ui->widget->setLayout(layoutChart);

    chart=new QChart();
    hpmSource=new HPM_Source(chart);
    chart->setTitle("高功率微波源");


    chartView->setChart(chart);

    QValueAxis * xAxis=new QValueAxis();
    xAxis->setRange(0,10);

    QValueAxis * yAxis=new QValueAxis();
    yAxis->setRange(0,10);
    chart->addAxis(xAxis,Qt::AlignmentFlag::AlignBottom);
    chart->addAxis(yAxis,Qt::AlignmentFlag::AlignLeft);
    chartView->setRenderHint(QPainter::Antialiasing);


//    chart->addSeries(seri);
//    chart->createDefaultAxes();

    connect(ui->stackedWidget,&QStackedWidget::currentChanged,this,&HPM_Widget::setChart);
    ui->stackedWidget->setCurrentIndex(0);
    chart->setAnimationOptions(QChart::AnimationOption::AllAnimations);
    chart->setTheme(QChart::ChartTheme::ChartThemeBlueIcy);
    QVBoxLayout * widgetLayout=new QVBoxLayout();
    ui->widget_combination->setLayout(widgetLayout);
    //组合脉冲内容
    connect(ui->pushButton_newPluse,&QPushButton::clicked,this,[=](){
        HPMSettingWidget * w1=new HPMSettingWidget(combinationNum++,ui->comboBox->currentIndex());
        combinationInputLists<<w1->getInputLineList();
        for(auto x:combinationInputLists)
        {
            for(auto y:x)
            {
                connect(y,&QLineEdit::textChanged,this,&HPM_Widget::CombinationInputEditChange,Qt::UniqueConnection);

            }
        }
        widgetList<<w1;
        types<<ui->comboBox->currentIndex();
        widgetLayout->addWidget(w1);
    });
    connect(ui->pushButton_clearPluse,&QPushButton::clicked,this,[=](){
        for(auto x : widgetList)
        {
            widgetLayout->removeWidget(x);
            delete x;
        }
        combinationInputLists.clear();
        widgetList.clear();
        types.clear();
        chart->removeAllSeries();
        combinationNum=1;
    });

//简单脉冲内容
    connect(m_TimeLine,&QLineEdit::textChanged,this,[=](){
        switch (ui->stackedWidget->currentIndex()) {
        case 0:
            if(this->isFitAll(this->list))
            {
                hpmSource->createBiExponetial(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),
                        this->list[1]->text().toDouble(),this->list[2]->text().toDouble());
            }
            break;
        case 1:
            if(this->isFitAll(this->list))
            {
                QVector<QLineEdit*>list1;
                list1<<m_TimeLine;
                list1.append(this->list);
                hpmSource->createTriExponetial(list1);
            }
            break;
        case 2:
            if(this->isFitAll(this->list))
            {

                hpmSource->createGauss(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                        this->list[2]->text().toDouble());
            }
            break;
        case 3:
            if(this->isFitAll(this->list))
            {

                hpmSource->createRect(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                        this->list[2]->text().toDouble());
            }
            break;
        case 4:
            if(this->isFitAll(this->list))
            {

                hpmSource->createSinWave(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble());
            }
            break;
        case 5:
            if(this->isFitAll(this->list))
            {
                hpmSource->createDefine(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                        this->list[2]->text().toDouble(),this->list[3]->text().toDouble());
            }
            break;
        case 6:
            break;
        default:
            break;
        }
    });
    this->list<<ui->lineEdit_1_1<<ui->lineEdit_1_2<<ui->lineEdit_1_3;
    for(auto x :this->list)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
            if(this->isFitAll(this->list))
            {
                hpmSource->createBiExponetial(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),
                        this->list[1]->text().toDouble(),this->list[2]->text().toDouble());

            }
        });
    }
    this->list.clear();
    this->list<<ui->lineEdit_2_1<<ui->lineEdit_2_2<<ui->lineEdit_2_3<<ui->lineEdit_2_4
       <<ui->lineEdit_2_5<<ui->lineEdit_2_6<<ui->lineEdit_2_7<<ui->lineEdit_2_8
      <<ui->lineEdit_2_9<<ui->lineEdit_2_10<<ui->lineEdit_2_11<<ui->lineEdit_2_12;
    for(auto x :this->list)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
            if(this->isFitAll(this->list))
            {
                QVector<QLineEdit*>list1;
                list1<<m_TimeLine;
                list1.append(this->list);
                hpmSource->createTriExponetial(list1);
            }
        });
    }
    this->list.clear();
    this->list<<ui->lineEdit_3_1<<ui->lineEdit_3_2<<ui->lineEdit_3_3;
    for(auto x :this->list)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
            if(this->isFitAll(this->list))
            {

                hpmSource->createGauss(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                        this->list[2]->text().toDouble());
            }
        });
    }
    this->list.clear();
    this->list<<ui->lineEdit_4_1<<ui->lineEdit_4_2<<ui->lineEdit_4_3;
    for(auto x :this->list)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
            if(this->isFitAll(this->list))
            {

                hpmSource->createRect(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                        this->list[2]->text().toDouble());
            }
        });
    }
    this->list.clear();
    this->list<<ui->lineEdit_7_1<<ui->lineEdit_7_2;
    for(auto x : this->list)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
            if(this->isFitAll(this->list)){
                hpmSource->createSinWave(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble());
            }
        });
    }
    this->list.clear();
    this->list<<ui->lineEdit_5_1<<ui->lineEdit_5_2<<ui->lineEdit_5_3<<ui->lineEdit_5_4;
    for(auto x : this->list)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
            if(this->isFitAll(this->list)){
                hpmSource->createDefine(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                        this->list[2]->text().toDouble(),this->list[3]->text().toDouble());
            }
        });
    }
    this->list.clear();
    this->list<<ui->lineEdit_1_1<<ui->lineEdit_1_2<<ui->lineEdit_1_3;
//    this->list<<ui->lineEdit_5_1<<ui->lineEdit_5_2<<ui->lineEdit_5_3<<ui->lineEdit_5_4
//       <<ui->lineEdit_5_5<<ui->lineEdit_5_6;

//    int t=ui->stackedWidget->count();
//    for(int i=0;i<t;i++)
//    {
//        if(i!=ui->stackedWidget->currentIndex())
//        {
//            QObjectList objects = ui->stackedWidget->widget(i)->children();
//            for(int j=0;j<objects.size();j++)
//            {
//                QWidget *content_widget = qobject_cast<QWidget *>(objects.at(j));
//                if (content_widget)
//                {
//                    content_widget->setVisible(i == false);
//                    break; // 这里只是跳出当前页的for循环
//                }
//            }
//            ui->stackedWidget->widget(i)->setVisible(false);
//        }

//    }
}

HPM_Widget::~HPM_Widget()
{
    delete ui;
}



void HPM_Widget::leftWidgetAnimation(int index,bool isOut)
{
    ui->stackedWidget->setCurrentIndex(index);
    if(isOut)
    {
        ui->scrollArea->setVisible(true);
        splitter->restoreState(state);
    }

    int stacWidth=ui->scrollArea->width();
    int stacHeight=ui->scrollArea->height();
    QLabel *labelLeft=new QLabel(this);

    labelLeft->resize(stacWidth,stacHeight);

    labelLeft->setPixmap(ui->scrollArea->grab());

    labelLeft->setAttribute(Qt::WA_DeleteOnClose);
    labelLeft->show();
    if(isOut)
    {
     ui->scrollArea->setVisible(false);
    }

    QLabel*labelRight=new QLabel(this);
    labelRight->resize(ui->widget->width(),ui->widget->height());
    labelRight->setPixmap(ui->widget->grab());
    labelRight->setAttribute(Qt::WA_DeleteOnClose);
    labelRight->show();

    QRect rectLeft1(-stacWidth,0,stacWidth,stacHeight);
    QRect rectLeft2(0,0,stacWidth,stacHeight);
    QRect rectRight1(0,0,ui->widget->width(),ui->widget->height());
    QRect rectRight2(stacWidth,0,ui->widget->width()-stacWidth,ui->widget->height());

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
        if(isOut){
            ui->scrollArea->setVisible(true);
            splitter->restoreState(state);
        }
        else {
            ui->scrollArea->setVisible(false);
        }
    });
}

void HPM_Widget::setTimeLine(QLineEdit *t)
{
    m_TimeLine=t;


}

void HPM_Widget::exportData()
{
     QVector<double> xseries=hpmSource->getX();
     QVector<double> yseries=hpmSource->getY();
     if(xseries.size()==0|yseries.size()==0)
     {
         return;
     }
     QFile file("hpmData.txt");
     if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
         QMessageBox::critical(NULL,"提示","无法创建文件");
         return;
     }else{
         QTextStream stream(&file);
         stream<<"x"<<"\t"<<"y"<<endl;
         for(int i=0;i<xseries.size();i++)
         {
             stream<<xseries[i]<<"\t"<<yseries[i]<<endl;
         }
         file.flush();
     }
     file.close();

}

QChart *HPM_Widget::getChart()
{
    return this->chart;

}

void HPM_Widget::setChart(int i)
{
    QString title;
    list.clear();
    switch (i) {
    case 0:title="双指数脉冲";
         list<<ui->lineEdit_1_1<<ui->lineEdit_1_2<<ui->lineEdit_1_3;
         if(this->isFitAll(this->list))
         {
             hpmSource->createBiExponetial(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),
                     this->list[1]->text().toDouble(),this->list[2]->text().toDouble());
         }
         else
         {
             chart->removeAllSeries();
         }
        break;
    case 1:title="三指数脉冲";
        list<<ui->lineEdit_2_1<<ui->lineEdit_2_2<<ui->lineEdit_2_3<<ui->lineEdit_2_4
           <<ui->lineEdit_2_5<<ui->lineEdit_2_6<<ui->lineEdit_2_7<<ui->lineEdit_2_8
          <<ui->lineEdit_2_9<<ui->lineEdit_2_10<<ui->lineEdit_2_11<<ui->lineEdit_2_12;
        if(this->isFitAll(this->list))
        {
            QVector<QLineEdit*>list1;
            list1<<m_TimeLine;
            list1.append(this->list);
            hpmSource->createTriExponetial(list1);
        }
        else
        {
            chart->removeAllSeries();
        }
        break;
    case 2:title="高斯脉冲";
        list<<ui->lineEdit_3_1<<ui->lineEdit_3_2<<ui->lineEdit_3_3;
        if(this->isFitAll(this->list))
        {

            hpmSource->createGauss(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                    this->list[2]->text().toDouble());
        }
        else
        {
            chart->removeAllSeries();
        }
        break;
    case 3:title="方波脉冲";
        list<<ui->lineEdit_4_1<<ui->lineEdit_4_2<<ui->lineEdit_4_3;
        if(this->isFitAll(this->list))
        {

            hpmSource->createRect(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                    this->list[2]->text().toDouble());
        }
        else
        {
            chart->removeAllSeries();
        }
        break;
    case 4:title="正弦波";
        list<<ui->lineEdit_7_1<<ui->lineEdit_7_2;
        if(this->isFitAll(this->list))
        {

            hpmSource->createSinWave(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble());
        }
        else
        {
            chart->removeAllSeries();
        }
        break;
    case 5:title="自定义脉冲";
        list<<ui->lineEdit_5_1<<ui->lineEdit_5_2<<ui->lineEdit_5_3<<ui->lineEdit_5_4;
        if(this->isFitAll(this->list))
        {

            hpmSource->createDefine(m_TimeLine->text().toDouble(),this->list[0]->text().toDouble(),this->list[1]->text().toDouble(),
                    this->list[2]->text().toDouble(),this->list[3]->text().toDouble());
        }
        else
        {
            chart->removeAllSeries();
        }
        break;
    case 6:title="组合脉冲";
        if(combinationInputLists.isEmpty())
        {
            chart->removeAllSeries();
            break;
        }
        if(this->isFitAll(combinationInputLists)&&!m_TimeLine->text().isNull()&&!m_TimeLine->text().isEmpty())
        {

           this->CombinationInputEditChange("");
        }
        else
        {
            chart->removeAllSeries();
        }
        break;
    default:
        title="脉冲类型";
        break;
    }
    chart->setTitle(title);

}

bool HPM_Widget::isFitAll(QVector<QVector<QLineEdit *> > list)
{
    if(m_TimeLine==nullptr||m_TimeLine->text().isNull()||m_TimeLine->text().isEmpty())
    {
        return false;
    }
    for(auto x : list)
    {
        for(auto y :x)
        {
            if(y->text().isNull()||y->text().isEmpty())
            {
                return false;
            }
        }
    }
    return true;
}

void HPM_Widget::CombinationInputEditChange(const QString &string)
{
    if(combinationInputLists.isEmpty())
    {
        qDebug()<<"combinationINputLists is empty";
        return;
    }
    if(this->isFitAll(combinationInputLists)&&!m_TimeLine->text().isNull()&&!m_TimeLine->text().isEmpty())
    {
        QVector<QVector<double>> inputVector;
        for(auto x:combinationInputLists)
        {
            QVector<double>input;
            for(auto y:x)
            {
                input.push_back(y->text().toDouble());
            }
            inputVector.push_back(input);
        }
        hpmSource->createCombination(types,inputVector,m_TimeLine->text().toDouble());
    }
}

bool HPM_Widget::isFitAll(QVector<QLineEdit *> inputList)
{
    for(auto x :inputList)
    {
        if(x->text().isNull()||x->text().isEmpty())
        {
            return false;
        }
    }
    return true;
}
