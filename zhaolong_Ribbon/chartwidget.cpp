#include "chartwidget.h"
#include <QSplitter>


ChartWidget::ChartWidget(QWidget *parent) : QWidget(parent)
{
    QSplitter * splitter=new QSplitter;

    plot=new QCustomPlot(this);
    treeWidget=new QTreeWidget();
    QList<int> size;
    size<<1000<<4000;
    splitter->addWidget(treeWidget);
    splitter->addWidget(plot);

    splitter->setSizes(size);
    treeWidget->setHeaderLabel("数据列表");

    QVBoxLayout * layout=new QVBoxLayout();
    layout->addWidget(splitter);
    layout->setMargin(0);
    this->setLayout(layout);
    plot->setContextMenuPolicy(Qt::CustomContextMenu);
    //test
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setTickLabels(false);
    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),plot->xAxis2,SLOT(setRange(QCPRange)));
    connect(plot->yAxis,SIGNAL(rangeChanged(QCPRange)),plot->yAxis2,SLOT(setRange(QCPRange)));
    //
    plot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    logTicker=QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog);
    plot->xAxis->setTicker(logTicker);
    Ticker=QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
    Ticker->setTickCount(20);
    Ticker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);

    plot->xAxis->setNumberFormat("eb");
    plot->xAxis->setNumberPrecision(0);
    plot->xAxis->setLabel(" 频率f/Hz ");
    plot->yAxis->setLabel("S parameters/dB");
    plot->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectPlottables |QCP::iSelectAxes );
    plot->legend->setVisible(true);
//    this->createMenu();
//    showGraph(0);
    tracer=new QCPItemTracer(plot);
    tracer->setStyle(QCPItemTracer::tsCircle);
    tracer->setPen(QPen(Qt::red));
    tracer->setBrush(Qt::red);
    tracer->setSize(6);
//    connect(plot,&QCustomPlot::customContextMenuRequested,this, &ChartWidget::contextMenu);
    connect(plot,&QCustomPlot::mouseMove,this,&ChartWidget::mouseMoveSlot);

    connect(plot,&QCustomPlot::axisClick,this,&ChartWidget::onAxisCliked);

    plot->xAxis->grid()->setSubGridVisible(true);
    plot->yAxis->grid()->setSubGridVisible(true);
    plot->xAxis->setNumberFormat("gbc");
    plot->xAxis->setNumberPrecision(2);
    plot->xAxis->ticker()->setTickCount(20);
    plot->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
    changeX(true);
    connect(treeWidget,&QTreeWidget::itemChanged,this,&ChartWidget::onItemChanged);
    connect(treeWidget,&QTreeWidget::itemDoubleClicked,this,&ChartWidget::onItemClicked);



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
    //test
    plot->xAxis2->setVisible(true);
    plot->yAxis2->setVisible(true);
    plot->xAxis2->setTickLabels(false);
    plot->yAxis2->setTickLabels(false);
    connect(plot->xAxis,SIGNAL(rangeChanged(QCPRange)),plot->xAxis2,SLOT(setRange(QCPRange)));
    connect(plot->yAxis,SIGNAL(rangeChanged(QCPRange)),plot->yAxis2,SLOT(setRange(QCPRange)));
    //
    plot->xAxis->setScaleType(QCPAxis::stLogarithmic);
    logTicker=QSharedPointer<QCPAxisTickerLog>(new QCPAxisTickerLog);
    plot->xAxis->setTicker(logTicker);
    Ticker=QSharedPointer<QCPAxisTicker>(new QCPAxisTicker);
    Ticker->setTickCount(20);
    Ticker->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);

    plot->xAxis->setNumberFormat("eb");
    plot->xAxis->setNumberPrecision(0);
    plot->xAxis->setLabel(" 频率f/Hz ");
    plot->yAxis->setLabel("S parameters/dB");
    plot->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom | QCP::iSelectPlottables |QCP::iSelectAxes );
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

    connect(plot,&QCustomPlot::axisClick,this,&ChartWidget::onAxisCliked);

    plot->xAxis->grid()->setSubGridVisible(true);
    plot->yAxis->grid()->setSubGridVisible(true);
    plot->xAxis->setNumberFormat("gbc");
    plot->xAxis->setNumberPrecision(2);
    plot->xAxis->ticker()->setTickCount(20);
    plot->xAxis->ticker()->setTickStepStrategy(QCPAxisTicker::TickStepStrategy::tssMeetTickCount);
    changeX(true);

}

void ChartWidget::saveGraph()
{
    QString filename = QFileDialog::getSaveFileName(this,"保存图片位置",".jpg","Images (*.jpg);;Images (*.bmp);;Images (*.png);;Images (*.pdf)");


        if( filename == "" ){
            QMessageBox::information(this,"fail","保存失败");
             return ;
         }
         if( filename.endsWith(".png") ){
             QMessageBox::information(this,"success","成功保存为png文件");
             plot->savePng( filename,plot->width(), plot->height() );
             return ;
         }
         if( filename.endsWith(".jpg")||filename.endsWith(".jpeg") ){
             QMessageBox::information(this,"success","成功保存为jpg文件");
             plot->saveJpg( filename, plot->width(), plot->height() );
             return ;
         }
         if( filename.endsWith(".bmp") ){
             QMessageBox::information(this,"success","成功保存为bmp文件");
             plot->saveBmp( filename,plot->width(),plot->height() );
             return ;
         }
         if( filename.endsWith(".pdf") ){
             QMessageBox::information(this,"success","成功保存为pdf文件");
            plot->savePdf( filename, plot->width(), plot->height() );
            return ;
         }
        else{
         //否则追加后缀名为.png保存文件
             QMessageBox::information(this,"success","保存成功,已默认保存为png文件");
        plot->savePng(filename.append(".png"),plot->width(), plot->height() );

        }

}

void ChartWidget::addItem(QVector<QVector<double> > data, QVector<QString> name, QString title)
{
    if(data.size()!=(name.size()+1))
    {
        qDebug()<<"数据数量不匹配";
        return;
    }
    QTreeWidgetItem * root=new QTreeWidgetItem(treeWidget,QStringList(QStringList(title)));

    MapTitleToX.insert(root,data[0]);
    for(int i=0;i<name.size();i++)
    {
        QTreeWidgetItem*item=new QTreeWidgetItem(root,QStringList(name[i]));
        MapItemToData.insert(item,data[i+1]);
        item->setCheckState(0,Qt::Unchecked);
        if(i==0)
        {
            item->setCheckState(0,Qt::Checked);
        }
    }
    if(currentTopItem!=nullptr)
    {
        currentTopItem->setIcon(0,QIcon(""));
    }
    root->setIcon(0,QIcon(IconPath));
    currentTopItem=root;
}

void ChartWidget::showGraph(QTreeWidgetItem *item)
{
    plot->addGraph();
    if(!MapItemToData.contains(item)||!MapTitleToX.contains(item->parent()))
    {
        qDebug()<<"Map里面没有这个item";
        return;
    }
    if(isGhz)
    {
        QVector<double> dataX=MapTitleToX.value(item->parent());
        for(auto &x : dataX)
        {
            x=x*1e-9;
        }

        plot->graph()->setData(dataX,MapItemToData.value(item));
        plot->xAxis->setLabel("频率f/GHz");
    }
    else
    {
        plot->xAxis->setLabel("频率f/Hz");
        plot->graph()->setData(MapTitleToX.value(item->parent()),MapItemToData.value(item));
    }
//    plot->graph()->setData(data[0],data[i+1]);
    plot->graph()->setName(item->parent()->text(0)+":"+item->text(0));
    int num=item->parent()->indexOfChild(item);

    plot->graph()->setPen(QPen(QColor(qSin(num*1+1.2)*80+80, qSin(num*0.3+0)*80+80, qSin(num*0.3+1.5)*80+80)));

    QPen pen;
    pen.setColor(Qt::red);
    pen.setWidth(1);
    plot->graph()->selectionDecorator()->setPen(pen);
    graphMapItem.insert(item,plot->graph());
    plot->rescaleAxes();
//    plot->xAxis->setRange(0,1e10);
    plot->replot();
}

void ChartWidget::removeGraph(QTreeWidgetItem *item)
{
    if(graphMapItem.isEmpty())return;
    if(!graphMapItem.contains(item))return;
    plot->removeGraph(graphMapItem[item]);
    graphMapItem.remove(item);
    plot->rescaleAxes();
    //    plot->xAxis->setRange(0,1e10);
    plot->replot();
}

void ChartWidget::removeItem()
{
    if(currentTopItem==nullptr)
    {
        return;
    }
    currentGraphItem=nullptr;
    for(int i=0;i<currentTopItem->childCount();i++)
    {
        QTreeWidgetItem* item=currentTopItem->child(i);
        MapItemToData.remove(item);
        if(graphMapItem.contains(item))
        {
            removeGraph(item);
        }
    }
    MapTitleToX.remove(currentTopItem);

    delete  currentTopItem;
    currentTopItem=nullptr;
}

void ChartWidget::readCSVFile(QString path)
{
    QVector<QString> name;
    QVector<QVector<double>>data;
    QDir dir = QDir::current();
    QFile file(dir.filePath(path));
    if(!file.open(QIODevice::ReadOnly))
         qDebug()<<"OPEN FILE FAILED";
    QTextStream * out = new QTextStream(&file);//文本流
    QStringList tempOption = out->readAll().split("\n");//每行以\n区分
    for(int i = 0 ; i < tempOption.count() ; i++)
    {
         QStringList tempbar = tempOption.at(i).split(",");//一行中的单元格以，区分
//         qDebug()<<tempbar[0].split(" ")[0];
         if(tempbar[0]=="END\r")
         {
             csvFileCount=0;
         }
         if(csvFileCount==2)
         {
             QVector<double>rowData;

             for(int i=0;i<tempbar.size();i++)
             {
                 rowData.push_back(tempbar[i].toDouble());
             }
             data.push_back(rowData);
         }
         if(csvFileCount==1)
         {
             for(auto x : tempbar)
             {
                 name.push_back(x.trimmed());
             }
             csvFileCount++;
         }

         if(tempbar[0].split(" ")[0]=="BEGIN")
         {
            csvFileCount++;
         }
    }

    //处理data
    QVector<QVector<double>>finalData=transverseVector(data);
    file.close();//操作完成后记得关闭文件

    //处理名字
    name.pop_front();

    //将数据导入进表格
    QString title=path.split("/").last();
    this->addItem(finalData,name,title);
}

void ChartWidget::setItemName(QString name)
{
    if(currentTopItem==nullptr)
    {
        return;
    }
    currentTopItem->setText(0,name);
    for(int i=0;i<currentTopItem->childCount();i++)
    {
        QTreeWidgetItem* item=currentTopItem->child(i);
        if(graphMapItem.contains(item))
        {
            removeGraph(item);
            showGraph(item);
        }
    }

}

void ChartWidget::setGraphColor(QColor color)
{
    if(currentGraphItem==nullptr)
    {
        return;
    }
    QCPGraph * graph=graphMapItem[currentGraphItem];
    graph->setPen(QPen(color));
    plot->replot();
}

bool ChartWidget::isHasMainProject()
{
 if(currentTopItem==nullptr)
 {
     return false;
 }
 else
 {
     return true;
 }
}

bool ChartWidget::isSelectItem()
{
    if(currentGraphItem==nullptr)
    {
        return false;
    }
    else
    {
        return true;
    }
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
    if(isGhz)
    {
        QVector<double> dataX=data[0];
        for(auto &x : dataX)
        {
            x=x*1e-9;
        }

        plot->graph()->setData(dataX,data[i+1]);
        plot->xAxis->setLabel("频率f/GHz");
    }
    else
    {
        plot->xAxis->setLabel("频率f/Hz");
         plot->graph()->setData(data[0],data[i+1]);
    }
//    plot->graph()->setData(data[0],data[i+1]);
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
    for(auto x:graphMapItem)
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
                currentGraphItem=graphMapItem.key(plot->graph(i));
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
                                                 "</table>").arg(plot->graph(i)->name()).arg( QString::number(xValue)).arg(QString::number(yValue,'f',2)), this, this->rect());
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

void ChartWidget::onAxisCliked(QCPAxis *axis, QCPAxis::SelectablePart part, QMouseEvent *event)
{

    if(event->button()==Qt::LeftButton&&part==QCPAxis::spAxisLabel)
    {
        isGhz=!isGhz;
        int length=0;
        for(auto x: data)
        {
            length++;
        }
        QList<QAction*> list=menu->actions();
        for(int i=0;i<length-1;i++)
        {

            if(list[i]->isChecked())
            {
                qDebug()<<i;
                removeGraph(i);
                showGraph(i);
            }
        }
    }
}

void ChartWidget::saveExcel()
{

    ExcelBase * excel=new ExcelBase();
    QString filename = QFileDialog::getSaveFileName(this,"保存Excel文件",".xls","Excel (*.xls)");
    if(filename.isNull())
    {
        return;
    }
    if(currentTopItem==nullptr)
    {
        QMessageBox::warning(this,"提示","未选择当前数据列表");
        return;
    }
    QMessageBox::warning(this,"提示","准备保存为Excel文件，点击确定继续");
    filename.replace("/","\\");
    excel->create(filename);
    QVector<QVector<double>>data;
    data.push_back(MapTitleToX[currentTopItem]);
     QList< QList<QVariant> > m_datas;
     QList<QVariant> row1;
     row1.append("f/Hz");
     for(int i=0;i<currentTopItem->childCount();i++)
     {
         row1.append(currentTopItem->child(i)->text(0));
         data.push_back(MapItemToData[currentTopItem->child(i)]);
     }
    m_datas.append(row1);
    int numRow=MapTitleToX[currentTopItem].size();
    int numCol=currentTopItem->childCount()+1;
    qDebug()<<numRow;
    qDebug()<<numCol;
    for(int i=0;i<numRow;i++)
    {
        QList<QVariant>row;
        for(int j=0;j<numCol;j++)
        {
            row.append(data[j][i]);
        }
        m_datas.append(row);
    }

    excel->setCurrentSheet(1);
    excel->writeCurrentSheet(m_datas);
    excel->save();
    excel->close();

    QMessageBox::information(this,"提示","已经成功保存为Excel文件");
    delete excel;
}

void ChartWidget::changeX(bool isLinear)
{
    if(isLinear)
    {
        plot->xAxis->setScaleType(QCPAxis::ScaleType::stLinear);
        plot->xAxis->setTicker(Ticker);



    }
    else{
        plot->xAxis->setScaleType(QCPAxis::ScaleType::stLogarithmic);
        plot->xAxis->setTicker(logTicker);

    }
    plot->rescaleAxes();
    plot->replot();
}

void ChartWidget::onItemChanged(QTreeWidgetItem *item, int column)
{
    if(item->checkState(column)==Qt::Checked)
    {
        showGraph(item);
    }
    else{
        removeGraph(item);
    }
}

void ChartWidget::onItemClicked(QTreeWidgetItem *item, int column)
{
    if(item->parent()!=nullptr)
    {

        return;
    }
    if(currentTopItem==nullptr)
    {
        currentTopItem=item;
    }
    currentTopItem->setIcon(column,QIcon(""));
    item->setIcon(column,QIcon(IconPath));
    currentTopItem=item;

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

QVector<QVector<double> > ChartWidget::transverseVector(const QVector<QVector<double> > &data)
{
    QVector<QVector<double>>finalData;
    if(data.size()<=0)
    {
        qDebug()<<"数据的尺寸:"<<data.size();
        return finalData;
    }
    int num=data[0].size();
    for(int i=0;i<num;i++)
    {
        QVector<double>columnData;
        for(int j=0;j<data.size();j++)
        {
//            qDebug()<<"i="<<i<<" "<<"j="<<j<<" "<<data[j][i];

            columnData.push_back(data[j][i]);
        }
        finalData.push_back(columnData);
    }
    return finalData;
}


