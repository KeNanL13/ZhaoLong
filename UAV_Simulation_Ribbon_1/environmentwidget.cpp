#include "environmentwidget.h"
#include "ui_environmentwidget.h"
#include <QVBoxLayout>
#include <QPropertyAnimation>
#include <QLabel>
#include <QParallelAnimationGroup>
#include <QDebug>
#include <QList>
#include <TDF_LabelSequence.hxx>
#include <STEPCAFControl_Reader.hxx>
#include <XCAFApp_Application.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_DocumentTool.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <complex.h>




EnvironmentWidget::EnvironmentWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EnvironmentWidget),
    angle(0,0,0),position(0,0,0),angleLinear(0,0,0),positionInter(100,0,0),
    angleIncident(0),anglePolariziton(0),
    velocity(0),UAVGain(0),InterFrequency(0),interPower(0),
    interWidth(0)
{
    ui->setupUi(this);
    QVBoxLayout * layout=new QVBoxLayout();
     splitter=new QSplitter();
    splitter->addWidget(ui->scrollArea);
    splitter->addWidget(ui->widget);
    QList<int>list;
    list<<1500<<4000;
    splitter->setSizes(list);

//    splitter->setStretchFactor(0,1);
//    splitter->setStretchFactor(1,4);
    layout->addWidget(splitter);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    this->setLayout(layout);
    state=splitter->saveState();

    occWidget=new OccView();
    QVBoxLayout* layoutWidget=new QVBoxLayout();
    layoutWidget->addWidget(occWidget);
    layoutWidget->setContentsMargins(0,0,0,0);
    ui->widget->setLayout(layoutWidget);



//    ui->stackedWidget->setVisible(false);
    ui->scrollArea->setVisible(false);

    occWidget->getView()->SetBgGradientColors(Quantity_NOC_LIGHTSKYBLUE, Quantity_NOC_LIGHTSKYBLUE4, Aspect_GFM_VER);
    occWidget->getView()->FitAll();
    occWidget->getViewer()->ActivateGrid(Aspect_GridType::Aspect_GT_Rectangular,Aspect_GridDrawMode::Aspect_GDM_Lines);
    occWidget->getViewer()->SetRectangularGridGraphicValues(2000,2000,1);
//    occWidget->getView()->Camera()->SetProjectionType(Graphic3d_Camera::Projection::Projection_Perspective);
    //设置模型加载
    this->loadModel(QDir::currentPath()+QDir::separator()+"Models/Boeing F A-18 E F Super Hornet.step");
    qDebug()<<QDir::currentPath()+QDir::separator()+"Models/Boeing F A-18 E F Super Hornet.step";
    TopoDS_Shape box1=BRepPrimAPI_MakeBox(gp_Pnt(-1,-1,-1),gp_Pnt(1,1,1));
    inter=new AIS_Shape(box1);
    vecIncident=new AdaptorVec_AIS(gp_Pnt(0,0,0),gp_Vec(10,0,0));
    vecIncident->SetText("入射方向");
    vecPori=new AdaptorVec_AIS(gp_Pnt(0,0,0),gp_Vec(0,0,10));
    vecPori->SetText("极化方向");
    this->interTranslate(positionInter,0,0);
    occWidget->getContext()->Display(model,false);
    occWidget->getContext()->Display(inter,true);
//    occWidget->getContext()->Display(vecIncident,false);
//    occWidget->getContext()->Display(vecPori,true);
    this->ModelTranslate(angle,position);

    timer=new QTimer;
    connect(timer,&QTimer::timeout,this,[=](){
        float k1=angleLinear.x(),k2=angleLinear.y(),k3=angleLinear.z();
        double velocity=this->velocity;
//        qDebug()<<"pitch="<<k2*0.005f*time<<"yaw="<<k3*0.005f*time;
        QVector3D angleNow=(angle+QVector3D(k1*0.005f*time,k2*0.005f*time,k3*0.005f*time))*static_cast<float>(M_PI)/180.0;
        QVector3D vel=QVector3D(velocity*cosf(angleNow[1])*cosf(angleNow[2]),velocity*cosf(angleNow[1])*sinf(angleNow[2]),velocity*sinf(angleNow[1]));
//        qDebug()<<"速度="<<vel;
        position=position+vel*0.005f*(time>0?1:0);
//        qDebug()<<position;
        gp_Pnt point(static_cast<double>(position.x()),static_cast<double>(position.y()),static_cast<double>(position.z()));
//        points.push_back(point);
qDebug()<<"这轮开始";
qDebug()<<"time="<<time;
qDebug()<<"x="<<point.X()<<"y="<<point.Y()<<"z="<<point.Z();
        if(time>0)
        {
            if(time>1)
            {
                occWidget->getContext()->Remove(moveWire,true);
            }
            if(!points.last().IsEqual(point,1e-5))
            {
                TopoDS_Edge edge=BRepBuilderAPI_MakeEdge(points.last(),point);
                wireMaker->Add(edge);

            }
            else{
                qDebug()<<"点不相同";
                goto DOWN;
            }
            moveWire=new AIS_Shape(wireMaker->Wire());
            moveWire->SetWidth(3);
            occWidget->getContext()->Display(moveWire,false);

        }
        DOWN:
        qDebug()<<"test1";
        points.push_back(point);
        this->ModelTranslate(angleNow,position);
        this->getData(time,angleNow);
        qDebug()<<"test2";


        time++;
        if(time>deadTime/0.005 )
        {
            timer->stop();
            for(int i=0;i<6;i++)
            {
                plotWidget[i]->rescaleAxes();
                plotWidget[i]->replot();
            }

        }
        qDebug()<<"这轮结束";
    });
    //设置模型实时变化
    QVector<QLineEdit*> modelParameters;
    modelParameters<<ui->lineEdit_Roll<<ui->lineEdit_Roll_k
                  <<ui->lineEdit_Yaw<<ui->lineEdit_Yaw_k
                 <<ui->lineEdit_Pitch<<ui->lineEdit_Pitch_k
                <<ui->lineEdit_UAVPosition;
    for(auto x : modelParameters)
    {
        connect(x,&QLineEdit::textChanged,[=](){
            QVector<double>parameterList;
            for(int i=0;i<6;i++)
            {
                if(!modelParameters[i]->text().isNull()&&!modelParameters[i]->text().isEmpty())
                {
                    parameterList.push_back(modelParameters[i]->text().toDouble());
                }
                else{
                    parameterList.push_back(0);
                }
            }
            angle=QVector3D(parameterList[0],parameterList[4],parameterList[2]);
            angleLinear=QVector3D(parameterList[1],parameterList[5],parameterList[3]);
            if(!ui->lineEdit_UAVPosition->text().isNull()&&!ui->lineEdit_UAVPosition->text().isEmpty())
            {
                QString position=ui->lineEdit_UAVPosition->text();
                QStringList pos=position.split(",");
                if(pos.size()==3)
                {
                    this->position=QVector3D(pos[0].toFloat(),pos[1].toFloat(),pos[2].toFloat());
                    qDebug()<<pos[0];
                    qDebug()<<pos[1];
                    qDebug()<<pos[2];
                }
            }

            this->ModelTranslate(angle*static_cast<float>(M_PI)/180.0,position);

        });
    }
    //设置干扰源实时变化
    QVector<QLineEdit*>interParameters;
    interParameters<<ui->lineEdit_InterPosition<<ui->lineEdit_InterDirection<<ui->lineEdit_InterPolarization;
    for(auto x : interParameters)
    {
        connect(x,&QLineEdit::textChanged,this,[=](){
            if(!ui->lineEdit_InterPosition->text().isNull()&&!ui->lineEdit_InterPosition->text().isEmpty())
            {
                QString position=ui->lineEdit_InterPosition->text();
                QStringList pos=position.split(",");
                if(pos.size()==3)
                {
                    this->positionInter=QVector3D(pos[0].toFloat(),pos[1].toFloat(),pos[2].toFloat());
                    qDebug()<<pos[0];
                    qDebug()<<pos[1];
                    qDebug()<<pos[2];
                }
            }
            if(!ui->lineEdit_InterDirection->text().isNull()&&!ui->lineEdit_InterDirection->text().isEmpty())
            {
                angleIncident=ui->lineEdit_InterDirection->text().toDouble();
            }
            if(!ui->lineEdit_InterPolarization->text().isNull()&&!ui->lineEdit_InterPolarization->text().isEmpty())
            {
                anglePolariziton=ui->lineEdit_InterPolarization->text().toDouble();
            }
            this->interTranslate(positionInter,angleIncident,anglePolariziton);
        });
    }
    ui->label_18->setVisible(false);
    ui->label_35->setVisible(false);
    ui->label_19->setVisible(false);
    ui->label_36->setVisible(false);
    ui->lineEdit_InterDirection->setVisible(false);
    ui->lineEdit_InterPolarization->setVisible(false);







}
void EnvironmentWidget::leftWidgetAnimation(int index,bool isOut)
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

//    QLabel*labelRight=new QLabel(this);
//    labelRight->resize(ui->widget->width(),ui->widget->height());
//    labelRight->setPixmap(ui->widget->grab());
//    labelRight->setAttribute(Qt::WA_DeleteOnClose);
//    labelRight->show();

    QRect rectLeft1(-stacWidth,0,stacWidth,stacHeight);
    QRect rectLeft2(0,0,stacWidth,stacHeight);
    QRect rectRight1(0,0,ui->widget->width(),ui->widget->height());
    QRect rectRight2(stacWidth,0,ui->widget->width()-stacWidth,ui->widget->height());

    QPropertyAnimation * aniLeft=new QPropertyAnimation(labelLeft,"geometry");
    aniLeft->setDuration(1000);
    aniLeft->setStartValue(isOut?rectLeft1:rectLeft2);
    aniLeft->setEndValue(isOut?rectLeft2:rectLeft1);
    aniLeft->setEasingCurve(QEasingCurve::Linear);

//    QPropertyAnimation * aniRight=new QPropertyAnimation(labelRight,"geometry");
//    aniRight->setDuration(1000);
//    aniRight->setStartValue(isOut?rectRight1:rectRight2);
//    aniRight->setEndValue(isOut?rectRight2:rectRight1);
//    aniRight->setEasingCurve(QEasingCurve::Linear);



    QParallelAnimationGroup * group=new QParallelAnimationGroup();
    group->addAnimation(aniLeft);
//    group->addAnimation(aniRight);

    group->start(QAbstractAnimation::DeleteWhenStopped);
      labelLeft->raise();
//      labelRight->raise();

    connect(group,&QParallelAnimationGroup::finished,[=](){
        labelLeft->close();
//        labelRight->close();
        if(isOut){
            ui->scrollArea->setVisible(true);
            splitter->restoreState(state);
        }
        else {
            ui->scrollArea->setVisible(false);
        }
    });


}

void EnvironmentWidget::selectUAV()
{
    occWidget->getContext()->SetSelected(model,true);
}

void EnvironmentWidget::selectHPM()
{
    occWidget->getContext()->SetSelected(inter,true);
}

void EnvironmentWidget::startTimer(int interval)
{
    QWidget *widget=new QWidget();
    QGridLayout *layout=new QGridLayout;
    if(wireMaker==nullptr)
    {
        wireMaker=new BRepLib_MakeWire();
    }


//    QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
//    timeTicker->setTimeFormat("%m:%s");
    for(int i=0;i<6;i++)
    {
        plotWidget[i]=new QCustomPlot();
        plotWidget[i]->addGraph();
        plotWidget[i]->graph(0)->setPen(QPen(QColor(40,110,255)));

//        plotWidget[i]->xAxis->setTicker(timeTicker);
        plotWidget[i]->xAxis->setLabel("时间/h");
        plotWidget[i]->axisRect()->setupFullAxesBox();

        connect(plotWidget[i]->xAxis,SIGNAL(rangeChanged(QCPRange)),plotWidget[i]->xAxis2,SLOT(setRange(QCPRange)));
        connect(plotWidget[i]->yAxis,SIGNAL(rangeChanged(QCPRange)),plotWidget[i]->yAxis2,SLOT(setRange(QCPRange)));
        switch (i) {
        case 0:plotWidget[i]->yAxis->setLabel("飞行半径（km）");
            plotWidget[i]->xAxis2->setLabel("飞行半径随时间变化图像");
            layout->addWidget(plotWidget[i],1,1);
            break;
        case 1:plotWidget[i]->yAxis->setLabel("GCS操作信号功率（dBm）");
            plotWidget[i]->xAxis2->setLabel("操纵信号功率随时间变化图像");
            layout->addWidget(plotWidget[i],1,2);
            break;
        case 2:plotWidget[i]->yAxis->setLabel("干扰源信号功率（dBm）");
            plotWidget[i]->xAxis2->setLabel("干扰源信号功率随时间变化图像");
            layout->addWidget(plotWidget[i],2,1);
            break;
        case 3:plotWidget[i]->yAxis->setLabel("ISR（dB）");
            plotWidget[i]->xAxis2->setLabel("操作信号与干扰信号功率差值随时间变化");
            layout->addWidget(plotWidget[i],2,2);
            break;
        case 4:plotWidget[i]->yAxis->setLabel("距离（km）");
            plotWidget[i]->xAxis2->setLabel("无人机与HPM源之间的距离随飞行时间变化");
            layout->addWidget(plotWidget[i],3,1);
            break;
        case 5:plotWidget[i]->yAxis->setLabel("链路整体降雨衰减（dB）");
            plotWidget[i]->xAxis2->setLabel("链路整体降雨衰减");
            layout->addWidget(plotWidget[i],3,2);
            break;
        default:
            break;
        }


    }
    layout->setContentsMargins(0,0,0,0);
    widget->setLayout(layout);


    widget->setAttribute(Qt::WA_DeleteOnClose);
    connect(widget,&QWidget::destroyed,this,[=](){
        if(timer!=nullptr)
        {
            timer->stop();
            qDebug()<<"timer is stop";
        }
    });

    widget->resize(600,600);

    //设置参数接收
    QVector<QLineEdit*> parameterList;
    parameterList<<ui->lineEdit_Velocity<<ui->lineEdit_UAVGain<<ui->lineEdit_InterFrequency<<ui->lineEdit_InterPower
                <<ui->lineEdit_InterGain;
    for(auto x: parameterList)
    {
        if(x->text().isNull()||x->text().isEmpty())
        {
            QMessageBox::warning(this,"提示","参数列表不完整，请检查是否输入所有参数");
            delete widget;
            return;
        }
    }
    velocity=parameterList[0]->text().toDouble();
    UAVGain=parameterList[1]->text().toDouble();
    InterFrequency=parameterList[2]->text().toDouble();
    interPower=parameterList[3]->text().toDouble()*1e-6;
    interWidth=parameterList[4]->text().toDouble();

    //雨衰参数
    switch (ui->comboBox->currentIndex()) {
    case 0:rain=0;
        break;
    case 1:rain=100;
        break;
    case 2:rain=300;
        break;
    case 3:rain=500;
        break;
    default:rain=0;
        break;
    }

    widget->show();
    if(timer!=nullptr)
    {
      timer->start(interval);
    }
}

OccView *EnvironmentWidget::getOccWidget()
{
    if(occWidget==nullptr)
    {
        return occWidget=new OccView;
    }
    return occWidget;
}
EnvironmentWidget::~EnvironmentWidget()
{

    delete ui;
    delete timer;
}

void EnvironmentWidget::loadModel(QString path)
{
    TDF_LabelSequence roots;
    STEPCAFControl_Reader reader1;
    IFSelect_ReturnStatus status= reader1.ReadFile(path.toStdString().c_str());
    if(status==false)
    {
        return ;
    }
    Handle(XCAFApp_Application) anApp=XCAFApp_Application::GetApplication();
    Handle(TDocStd_Document)doc;
    anApp->NewDocument("MDTV-XCAF",doc);
    bool yes=reader1.Transfer(doc);
    qDebug()<<yes;

    TDF_Label mainLabel=doc->Main();
    Handle(XCAFDoc_ShapeTool)ShapeTool = XCAFDoc_DocumentTool::ShapeTool(mainLabel);
    // Get root shapes to visualize.
    ShapeTool->GetFreeShapes(roots);


    model=new XCAFPrs_AISObject(roots.First());//读第一个标签
}

void EnvironmentWidget::ModelTranslate(QVector3D angle,QVector3D position)
{
    gp_Trsf transRoll,transPitch,transYaw,transUAV;
    gp_Trsf fixTrans1,fixTrans2,fixTrans3;
    fixTrans1.SetTranslation(gp_Vec(0,5,0));
    fixTrans2.SetRotation(gp_Ax1(gp_Pnt(0,0,0),gp_Dir(1,0,0)),M_PI_2);
    fixTrans3.SetRotation(gp_Ax1(gp_Pnt(0,0,0),gp_Dir(0,0,1)),M_PI);

    transRoll.SetRotation(gp_Ax1(gp_Pnt(0,0,0),gp_Dir(1,0,0)),static_cast<double>(angle[0]));
    transPitch.SetRotation(gp_Ax1(gp_Pnt(0,0,0),gp_Dir(0,1,0)),-static_cast<double>(angle[1]));
    transYaw.SetRotation(gp_Ax1(gp_Pnt(0,0,0),gp_Dir(0,0,1)),static_cast<double>(angle[2]));

    transUAV.SetTranslation(gp_Vec(static_cast<double>(position.x()),static_cast<double>(position.y()),static_cast<double>(position.z())));
//    qDebug()<<positionUAV.x() << " " <<positionUAV.y() <<" "<<positionUAV.z();
//    transInter.SetTranslation(gp_Vec(positionInter.x(),positionInter.y(),positionInter.z()));
    model->SetLocalTransformation(transUAV*transYaw*transPitch*transRoll*fixTrans3*fixTrans2*fixTrans1);

//    inter->SetLocalTransformation(transInter);
    occWidget->getViewer()->Redraw();

}

void EnvironmentWidget::interTranslate(QVector3D position, double angleInci, double anglePolarization)
{
    gp_Trsf transInci,transPolarization,transPosition;
    transPosition.SetTranslation(gp_Vec(position.x(),position.y(),position.z()));
    transInci.SetRotation(gp_Ax1(gp_Pnt(position.x(),position.y(),position.z()),gp_Dir(0,1,0)),angleInci*M_PI/180.0);
    transPolarization.SetRotation(gp_Ax1(gp_Pnt(position.x(),position.y(),position.z()),gp_Dir(1,0,0)),anglePolarization*M_PI/180.0);
    inter->SetLocalTransformation(transPosition);
    vecIncident->SetLocalTransformation(transInci*transPosition);
    vecPori->SetLocalTransformation(transPolarization*transPosition);
    occWidget->getViewer()->Redraw();
}

void EnvironmentWidget::resetALL()
{
    if(moveWire.IsNull())
    {
        return;
    }

    occWidget->getContext()->Remove(moveWire,true);
    points.clear();
    QString pos=ui->lineEdit_UAVPosition->text();
    QStringList pos1=pos.split(",");
    if(pos1.size()==3)
    {
        this->position=QVector3D(pos1[0].toFloat(),pos1[1].toFloat(),pos1[2].toFloat());
    }
    ModelTranslate(angle,position);
    delete wireMaker;
    wireMaker=nullptr;
    time=0;
}

void EnvironmentWidget::stopSimulation(bool isStop)
{
    if(timer!=nullptr)
    {
        if(isStop)
        {
              timer->stop();
        }
        else{
            timer->start();
        }
    }



}

void EnvironmentWidget::createNewPlot()
{
    double interPower=10;
    QCustomPlot * plot[2];
    for(int i=0;i<2;i++)
    {
        plot[i]=new QCustomPlot();
        plot[i]->setAttribute(Qt::WA_DeleteOnClose);

        plot[i]->addGraph();
        plot[i]->graph(0)->setPen(QPen(QColor(40,110,255)));

//        plotWidget[i]->xAxis->setTicker(timeTicker);
        plot[i]->xAxis->setLabel("距离/km");
        plot[i]->axisRect()->setupFullAxesBox();
        plot[i]->setInteractions(QCP::iRangeDrag| QCP::iRangeZoom);

        connect(plot[i]->xAxis,SIGNAL(rangeChanged(QCPRange)),plot[i]->xAxis2,SLOT(setRange(QCPRange)));
        connect(plot[i]->yAxis,SIGNAL(rangeChanged(QCPRange)),plot[i]->yAxis2,SLOT(setRange(QCPRange)));
        switch (i) {
        case 0:
            plot[i]->yAxis->setLabel("功率密度(W/cm2)");
            break;
        case 1:plot[i]->yAxis->setLabel("电场强度(V/m)");

            break;
        default:
            break;
        }
    }
    QVector<double>distance;
    QVector<double>p;
    QVector<double>e;

    for(int i=100;i<=2000;i++)
    {
        double x =0.5*i;
        double power=interPower*1e9*100/(4*M_PI*pow(x,2));
        double electrical=pow(power*377*2,0.5);
        distance.push_back(x);
        p.push_back(power);
        e.push_back(electrical);
        qDebug()<<electrical;
    }
    plot[0]->graph()->addData(distance,p);

    plot[1]->graph()->addData(distance,e);
    plot[0]->rescaleAxes();
    plot[1]->rescaleAxes();
    plot[0]->replot();
    plot[1]->replot();
    plot[0]->resize(400,400);
    plot[0]->show();
    plot[1]->resize(400,400);
    plot[1]->show();


}

void EnvironmentWidget::evaluationPlot()
{
    QList<QLineEdit*>list;list<<ui->lineEdit_InterPower<<ui->lineEdit_UAVGain<<ui->lineEdit_InterFrequency<<ui->lineEdit_InterGain;
    for(auto x : list)
    {
        if(x->text().isNull()||x->text().isEmpty())
        {
            QMessageBox::warning(this,"提示","未输入完整数据");
            return ;
        }
    }
    double pulseWidth=ui->lineEdit_InterGain->text().toDouble()/1e3;
    double threshold=caculateThreshold(pulseWidth)*0.5+92;
    double ratio=pulseWidth*1e3>=500?pulseWidth*1e3/500:1;
    double power=cacalatePower();
    QString result;
    if(power<threshold/(10*ratio))
    {
        result="无损伤";
    }
    else if(threshold/(10*ratio)<power&&power<threshold/(7*ratio)){
        result="干扰";
    }
    else if(threshold/(7*ratio)<power&&power<threshold/(6*ratio))
    {
        result="性能降级";
    }
    else if(threshold/(6*ratio)<power&&power<threshold)
    {
        result="软损伤";
    }
    else if(power>threshold)
    {
        result="硬损伤";
    }
    evaluationWidget=new QCustomPlot;
    QCPAxis *xAxis = evaluationWidget->xAxis;//x轴
    QCPAxis *yAxis = evaluationWidget->yAxis;//y轴
    QCPBars *bars = new QCPBars(xAxis, yAxis);  // 使用xAxis作为柱状图的x轴，yAxis作为y轴

    bars->setAntialiased(false); // 为了更好的边框效果，关闭抗齿锯
    bars->setName(QString("毁伤评估结果:%1").arg(result)); // 设置图例
    bars->setPen(QPen(QColor(0, 160, 140).lighter(130))); // 设置柱状图的边框颜色
    bars->setBrush(QColor(20,68,106));  // 设置柱状图的画刷颜色


    QVector<double> ticks;
    QVector<QString> labels;
    ticks << 1 << 2 << 3 << 4 << 5<<6;//轴的范围
    labels << "干扰" << "性能降级" << "软损伤" << "硬损伤" << "仿真结果"<<"";//轴的刻度文字显示
    QSharedPointer<QCPAxisTickerText> textTicker(new QCPAxisTickerText);
    textTicker->addTicks(ticks, labels);
    xAxis->setTicker(textTicker);        // 设置为文字轴
//    xAxis->setTickLabelRotation(60);     // 轴刻度文字旋转60度
    xAxis->setSubTicks(false);           // 不显示子刻度
    xAxis->setTickLength(0, 4);          // 轴内外刻度的长度分别是0,4,也就是轴内的刻度线不显示
    xAxis->setRange(0, 9);               // 设置x轴范围
    xAxis->setLabel(QString("毁伤评估结果:%1").arg(result));
    xAxis->setLabelColor(QColor(255,0,100));
    xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);

//    yAxis->setRange(0, 12.1);          //设置y轴范围
    yAxis->setPadding(35);             // 轴的内边距
    yAxis->setLabel("干扰信号功率(W)");
    yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    QVector<double> fossilData;
    fossilData  << threshold/(10*ratio) <<threshold/(7*ratio) << threshold/(6*ratio)<< threshold << power<<0;//y轴坐标值
    qDebug()<<"threshold="<<threshold;
    qDebug()<<"power="<<power;
    bars->setData(ticks, fossilData);

    evaluationWidget->rescaleAxes();
    evaluationWidget->replot();
    evaluationWidget->resize(500,500);

    evaluationWidget->show();
    evaluationWidget->setAttribute(Qt::WA_DeleteOnClose);



}

double EnvironmentWidget::caculateThreshold(double pluseWidth)
{
    int n = 100;                                    // 高功率微波数量
    double W = 0.507, L = 2.34, Z = 24.99;          //沟槽结构尺寸 um
    double copper_sigma = 401, silicon_sigma = 168; //材料的热导率 W / ( m * K )
    double copper_hc = 0.385, silicon_hc = 0.71;    //材料的比热容    J / ( g * K )
    double copper_rho = 8.9, silicon_rho = 2.3290;  //材料的密度    g / cm ^ 3
    double angle = tan(M_PI / 4.0);                   //沟槽的倾斜角取 PI / 4
    double silicon_D = silicon_sigma / (silicon_hc * silicon_rho);      //硅的热扩散系数
    double copper_H = 3.26, copper_L1 = 2.4, copper_L2 = 3, copper_Z = 24.99;   //铜结构尺寸    um
    double silicon_v = W * L * Z, copper_v = 6 * copper_H * (copper_L1 + copper_L2) / 2 * copper_Z;     //结构的体积
    double copper_HC = copper_hc * copper_rho * copper_v * 6; //六个金属结构热容之和
    double T0 = 300, Ta = 300, Tth = 600;
    float D1 = 0.08;     //高功率微波占空比\

    double A = 1.2;         // 散热区域系数
    double H = A * sqrt(silicon_D * pluseWidth);     // 计算结果单位是 um,
    double R_0 = 1.0 / 2 / silicon_sigma / Z * log(1 + 2 * H / L) * 1e6;  //单个沟槽的热阻, 单位是 K / W
    //printf("the resistor is %f \n", R_0);
    double R = R_0 / 6;                                             // 6个沟槽的热阻并联数值
    double silicon_HC = silicon_hc * silicon_rho * silicon_v * 6;   // 六个硅结构热容之和
    double HeatCap = (copper_HC + silicon_HC) * 1e-6;     // 热容之和，单位为 [ 1e-6 * J / K]
    //printf("Heat Capacity is  %f\n", HeatCap);
    //printf("silicon_D == %f\n", silicon_D);
    double K = R * HeatCap;
    double P = ((Tth - Ta) - (T0 - Ta) * exp((n - 1 + D1) * pluseWidth / K)) / (R * (1 - exp(-D1 / K * pluseWidth)) * (1 - pow(exp(-pluseWidth / K), n)) / (1 - exp(-pluseWidth / K)));
    return P;
}

double EnvironmentWidget::cacalatePower()
{

    double powerInter=ui->lineEdit_InterPower->text().toDouble();
    double gainUAV=pow(10,ui->lineEdit_UAVGain->text().toDouble()/10);
    double gainInter=1;
    QVector3D positionUAV=this->position;
    QVector3D positionInter=this->positionInter;
    double lamda=3e8/(ui->lineEdit_InterFrequency->text().toDouble());
    double length=lamda/2;
    double roll=angle[0]*static_cast<float>(M_PI)/180.0;
    double pitch=angle[1]*static_cast<float>(M_PI)/180.0;
    double yaw=angle[2]*static_cast<float>(M_PI)/180.0;

//    double vel=0;

//    QVector3D velocity(vel*cos(pitch)*cos(yaw),vel*cos(pitch)*sin(yaw),vel*sin(pitch));
    QVector3D antannaUAV(-cos(roll)*sin(pitch)*cos(yaw)-sin(roll)*sin(yaw),
           -cos(roll)*sin(pitch)*sin(yaw)+sin(roll)*cos(yaw),
            cos(roll)*cos(pitch));

    double miu=antannaUAV.z();
//    QVector3D currentPostionUAV=positionUAV+velocity*0.005*t;
    QVector3D vectorItoU=positionInter-positionUAV;
//    double R=positionUAV.length();
    double Rj=vectorItoU.length();

    QVector3D aj=vectorItoU;
//    aj.setZ(aj.z()/Rj);
    aj.normalize();
    QVector3D vector=QVector3D::crossProduct(aj,QVector3D(0,0,1));
    QVector3D ae=QVector3D::crossProduct(vector,aj);
    ae.normalize();
    double miuj=QVector3D::dotProduct(ae,antannaUAV);
    double temp=QVector3D::dotProduct(aj,antannaUAV);
    double thetaj=M_PI-acos(temp);
//    double theta=acos(positionUAV.z()/positionUAV.length());
    qDebug()<<"thetaj="<<thetaj;

    double pij=powerInter*gainInter*gainUAV*pow(miuj,2)*pow(lamda/(4*M_PI*Rj),2)*fuFunction(thetaj,thetaj,lamda,length);
    qDebug()<<powerInter<<" "<<gainUAV<<" "<<gainInter<<" "<<pow(miuj,2)<<" "<<pow(lamda/(4*M_PI*Rj),2)<<" "<<fuFunction(thetaj,thetaj,lamda,length)<<" ";
    return pij;
}

double EnvironmentWidget::fuFunction(double theta,double alpha,double lamda,double length)
{
    if(theta==0.0)
    {
        return 0;
    }
    double p=M_PI*2/lamda*length/2;
    double a=(cos(p*cos(theta))-cos(p))/sin(theta);

    return a;
}



void EnvironmentWidget::getData(int t,const QVector3D& angle)
{

    double gainUAV=UAVGain;//无人机天线增益
    double gainGCS=gainUAV;//GCS天线增益
    double powerGCS=1.0;//GCS传输能量
//    QVector3D positionUAV(60,0,5);//无人机初始位置
    double frequencyInter=InterFrequency;//干扰频率
    double frequencyGCS=3.5e10;//GCS操作频率
    QVector3D positionInter=this->positionInter;//干扰源位置
    double PowerInter=interPower;//干扰源传输能量
    double GainInter=10.0;//干扰源天线增益
//    QVector3D angle(-10,0,15);
//    angle*=M_PI/180;
    double vel=velocity;
    double roll,pitch,yaw;
    roll=angle[0];pitch=angle[1];yaw=angle[2];


    QVector3D velocity(vel*cos(pitch)*cos(yaw),vel*cos(pitch)*sin(yaw),vel*sin(pitch));
    QVector3D antannaUAV(-cos(roll)*sin(pitch)*cos(yaw)-sin(roll)*sin(yaw),
           -cos(roll)*sin(pitch)*sin(yaw)+sin(roll)*cos(yaw),
            cos(roll)*cos(pitch));
    double miu=antannaUAV.z();
//    QVector3D currentPostionUAV=positionUAV+velocity*0.005*t;
    QVector3D vectorItoU=positionInter-position;
    double R=position.length();
    double Rj=vectorItoU.length();
    qDebug()<<"Rj="<<Rj;
    QVector3D aj=vectorItoU;
//    aj.setZ(aj.z()/Rj);
    aj.normalize();
    QVector3D vector=QVector3D::crossProduct(aj,QVector3D(0,0,1));
    QVector3D ae=QVector3D::crossProduct(vector,aj);
    ae.normalize();
    double miuj=QVector3D::dotProduct(ae,antannaUAV);
    double temp=QVector3D::dotProduct(aj,antannaUAV);
    double thetaj=M_PI-acos(temp);
    double theta=acos(position.z()/position.length());

    double Pis=10*log10(powerGCS)+10*log10(gainGCS)+10*log10(gainUAV)
            +20*log10(miu)+20*log10(FunctionFg(theta))+20*log10(FunctionFg(M_PI_2))
            -20*log10(position.length())-20*log10(frequencyGCS)+147.56;


    double Pij=10*log10(PowerInter)+10*log10(GainInter)+10*log10(gainUAV)
            +20*log10(miuj)+20*log10(abs(cos(M_PI_2*cos(thetaj))/sin(thetaj)))
            -20*log10(Rj)-20*log10(frequencyInter)+147.56;



    double rainAtt=cacualteRainParameter(InterFrequency*1e-9,aj.z(),qDegreesToRadians(anglePolariziton),rain);
    double rainLos=rainAtt*Rj*1e-3;
    qDebug()<<R;
    qDebug()<<Pis;
    qDebug()<<Pij;
    qDebug()<<Pij-Pis;
    qDebug()<<Rj;
    qDebug()<<rainLos;

    plotWidget[0]->graph(0)->addData(0.005*t,R);
    plotWidget[1]->graph(0)->addData(0.005*t,Pis);
    plotWidget[2]->graph(0)->addData(0.005*t,Pij);
    plotWidget[3]->graph(0)->addData(0.005*t,Pij-Pis);
    plotWidget[4]->graph(0)->addData(0.005*t,Rj);
    plotWidget[5]->graph(0)->addData(0.005*t,rainLos);
    for(int i=0;i<6;i++)
    {
        plotWidget[i]->graph(0)->rescaleAxes();
        plotWidget[i]->xAxis->setRange(0.005*t,8,Qt::AlignRight);
        plotWidget[i]->replot();
    }




}

double EnvironmentWidget::FunctionFg(double theta)
{
    if(theta==0.0)
    {
        return 1;
    }
    return cos(M_PI_2*cos(theta))/sin(theta);
}

//f 单位是GHz
double EnvironmentWidget::cacualteRainParameter(double frequency,double theta,double thetaPolarization,double rain)
{
    double miuH,miuV,viH,viV;
    if(frequency<=20&&frequency>=1)
    {
        miuH=3.8794*1e-5*pow(frequency,2.747-1.7941*qLn(frequency)+
                             1.181*pow(qLn(frequency),2)-0.202*pow(qLn(frequency),3));
        miuV=3.581*1e-5*pow(frequency,2.603-1.617*qLn(frequency)+
                            1.094*pow(qLn(frequency),2)-0.188*pow(qLn(frequency),3));
        viH=(pow(1.056*qLn(frequency)-1.926,2)+0.944)/(pow(1.114*qLn(frequency)-2.094,2)+0.7181);
        viV=(pow(1.025*qLn(frequency)-1.946,2)+0.905)/(pow(1.107*qLn(frequency)-2.158,2)+0.697);
    }
    else if(frequency>20)
    {
        miuH=(8.2522*1e-5*pow(frequency,2))/(1-0.015*qLn(frequency)+6.203*1e-5*pow(frequency,2));
        miuV=(7.913*1e-5*pow(frequency,2))/(1-0.187*qLn(frequency)+5.936*1e-5*pow(frequency,2));
        viH=0.683+0.502/(1+2.095*1e-4*pow(frequency,2.287));
        viV=0.683+0.449/(1+1.87*1e-4*pow(frequency,2.28));
    }
    else {
        miuH=miuV=viH=viV=0;
    }
    double miu=(miuH+miuV+(miuH-miuV)*pow(cos(theta),2)*cos(2*thetaPolarization))/2;
    double vi=(miuH*viH+miuV*viV+(miuH-miuV)*pow(cos(theta),2)*cos(2*thetaPolarization))/2;
    return miu*pow(rain,vi);
}
