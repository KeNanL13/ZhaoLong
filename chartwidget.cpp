#include "chartwidget.h"

ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent)
{

}

ChartWidget::ChartWidget(QVector<QVector<double> > data, QVector<QString> name, QWidget *parent)
    :data(data),
     name(name)

{
    plot=new QCustomPlot(this);
    QVBoxLayout * layout=new QVBoxLayout();
    layout->addWidget(plot);
    layout->setMargin(0);
    this->setLayout(layout);
    plot->setContextMenuPolicy(Qt::CustomContextMenu);
    plot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    QSharedPointer<QCPAxisTickerLog> logTicker(new QCPAxisTickerLog);
    plot->xAxis->setTicker(logTicker);
    plot->xAxis->setNumberFormat("eb");
    plot->xAxis->setNumberPrecision(0);
    plot->xAxis->setLabel(" 频率f/Hz ");
    plot->yAxis->setLabel("S parameters/dB");
    plot->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectPlottables );
    plot->legend->setVisible(true);
    this->createMenu();
    showGraph(0);
    tracer=new QCPItemTracer(plot);
    tracer->setStyle(QCPItemTracer::tsCircle);
    tracer->setPen(QPen(Qt::red));
    tracer->setBrush(Qt::red);
    tracer->setSize(6);
    connect(plot,&QCustomPlot::customContextMenuRequested,this, &ChartWidget::contextMenu);
    connect(plot,&QCustomPlot::mouseMove,this,&ChartWidget::mouseMoveSlot);
}

void ChartWidget::contextMenu(QPoint pos )
{
    if(menu->isEmpty())
    {
        qDebug()<<"?";
    }
    else{
    menu->popup(plot->mapToGlobal(pos));
    }
}

void ChartWidget::showGraph(int i)
{
    plot->addGraph();
    plot->graph()->setData(data[0],data[i+1]);
    plot->graph()->setName(name[i]);
    plot->graph()->setPen(QPen(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80)));

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    plot->graph()->selectionDecorator()->setPen(pen);
    graphMap.insert(i,plot->graph());
    plot->rescaleAxes();
//    plot->xAxis->setRange(0,1e10);
    plot->replot();
}

void ChartWidget::removeGraph(int i)
{
    if(graphMap.isEmpty())return;
    plot->removeGraph(graphMap[i]);
    graphMap.remove(i);
     plot->rescaleAxes();
//    plot->xAxis->setRange(0,1e10);
     plot->replot();
}

void ChartWidget::mouseMoveSlot(QMouseEvent *event)
{
    int num=0;
    for(auto x:graphMap)
    {
        num++;
    }
    if(num==0)
    {
        return;
    }
    else
    {
        double x=plot->xAxis->pixelToCoord(event->pos().x());
        for(int i=0;i<num;i++)
        {
            if(plot->graph(i)->selected())
            {
                tracer->setVisible(true);
                tracer->setGraph(plot->graph(i));
                tracer->setGraphKey(x);
                tracer->setInterpolating(true);
                tracer->updatePosition();
                double xValue=tracer->position->key();
                double yValue=tracer->position->value();
                QToolTip::showText(event->globalPos(), tr(
                                                 "<h4>%1</h4>"
                                                 "<table>"
                                                 "<tr>"
                                                 "<td><h5>X: %2</h5></td>" "<td>  ,  </td>" "<td><h5>Y: %3</h5></td>"
                                                 "</tr>"
                                                 "</table>").arg(plot->graph(i)->name()).arg( QString::number(xValue)).arg(QString::number(yValue)), this, this->rect());
                 plot->replot();
                break;

            }
            else {
                tracer->setVisible(false);
                 plot->replot();
            }
        }
    }
}


void ChartWidget::createMenu()
{
    menu=new QMenu(this);
    int length=0;
    for(auto x: data)
    {
        length++;
    }

    for(int i=0;i<length-1;i++)
    {
        QAction * action=new QAction(name[i]);
        action->setCheckable(true);
        if(i==0)
        {
            action->setChecked(true);
        }
        connect(action,&QAction::triggered,[=](){
           if(action->isChecked())
           {
               this->showGraph(i);
           }
           else
           {
               this->removeGraph(i);
           }
        });
        menu->addAction(action);
    }
}


