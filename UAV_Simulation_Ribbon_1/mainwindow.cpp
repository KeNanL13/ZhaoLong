#include "mainwindow.h"
#include <SAFramelessHelper.h>
#include <QGraphicsDropShadowEffect>
#include <QFileDialog>
#include <hpm_widget.h>


#include <QActionGroup>

MainWindow::MainWindow(QWidget *parent) :
     SARibbonMainWindow(parent)
{
    SAFramelessHelper* helper = framelessHelper();
    helper->setBorderWidth(5);
    helper->setRubberBandOnResize(false);
    setWindowIcon(QIcon(":/Resouce/icons/application.svg"));
    this->ribbonBar()->setWindowTitleTextColor(QColor(255,255,255));
//    this->ribbonBar()->setRibbonStyle(SARibbonBar::OfficeStyleTwoRow);
    this->ribbonBar()->setContentsMargins(0, 0, 0, 0);
    this->resize(800,600);
    this->setMinimumWidth(500);
//    this->ribbonBar()->applicationButton()->setVisible(false);
    this->setWindowTitle("UAV高功率微波毁伤效应软件");
//    QPushButton * applicationButton=new QPushButton(this);
//    applicationButton->setIcon(QIcon(":/Resouce/icons/application.svg"));
//    this->ribbonBar()->setApplicationButton(applicationButton);
    this->ribbonBar()->setFont(QFont("微软雅黑",13));
    connect(this->ribbonBar(),&SARibbonBar::applicationButtonClicked,this,[=](){
        if(!isShowTwo)
        {
            this->ribbonBar()->setRibbonStyle(SARibbonBar::OfficeStyleTwoRow);
            SARibbonToolButton::setLiteStyleEnableWordWrap(false);
        }
        else {
            this->ribbonBar()->setRibbonStyle(SARibbonBar::OfficeStyle);
        }
        isShowTwo=!isShowTwo;
    });
//    this->ribbonBar()->setTabBarBaseLineColor(QColor(0,0,0));
//    this->ribbonBar()



//    SARibbonToolButton::setLiteStyleEnableWordWrap(false);
    //总标签分类
    SARibbonCategory*categoryHpm=this->ribbonBar()->addCategoryPage(tr("高功率微波源"));
    SARibbonCategory*categoryEnvironment=this->ribbonBar()->addCategoryPage(tr("对抗环境"));
    SARibbonCategory*categoryModel=this->ribbonBar()->addCategoryPage(tr("无人机模型"));
//    SARibbonCategory*categorySimulation=this->ribbonBar()->addCategoryPage(tr("仿真"));
    connect(this->ribbonBar(),&SARibbonBar::currentRibbonTabChanged,this,&MainWindow::OnRibbonTabChanged);

    //标签1：高功率微波 Pannel2 ：设置 创建
    SARibbonPannel*pannelHpm2=categoryHpm->addPannel("设置");
    QLabel * label=new QLabel("总时间(ns):");
    pannelHpm2->addWidget(label,SARibbonPannelItem::Large);
    SARibbonLineEdit* hpmTimeLine=new SARibbonLineEdit(this);
    pannelHpm2->addWidget(hpmTimeLine,SARibbonPannelItem::Large);
    QAction * hpmClear=new QAction("清除波形");
    hpmClear->setIcon(QIcon(":/Resouce/icons/clear.svg"));

    pannelHpm2->addLargeAction(hpmClear);
    QAction * hpmExport=new QAction("导出数据");
    hpmExport->setIcon(QIcon(":/Resouce/icons/clear.svg"));

    pannelHpm2->addLargeAction(hpmExport);
    //标签2：攻击环境 pannel1：参数设置
    SARibbonPannel*pannelEnvironment1=categoryEnvironment->addPannel("参数设置");
    this->pannelAddLargeAction(pannelEnvironment1,"姿态角设置",":/Resouce/icons/angel.png");
    this->pannelAddLargeAction(pannelEnvironment1,"无人机参数",":/Resouce/icons/uav.svg");
    this->pannelAddLargeAction(pannelEnvironment1,"干扰源",":/Resouce/icons/hpm.svg");
    this->pannelAddLargeAction(pannelEnvironment1,"环境设置",":/Resouce/icons/Environment2.svg");
    SARibbonPannel*pannelEnvironment2=categoryEnvironment->addPannel("模型查看");
    this->pannelAddLargeAction(pannelEnvironment2,"无人机",":/Resouce/icons/UAV1.svg");
    this->pannelAddLargeAction(pannelEnvironment2,"辐射源",":/Resouce/icons/HpmSource.svg");
    SARibbonPannel * pannelEnvironment3=categoryEnvironment->addPannel("飞行模拟");
    this->pannelAddLargeAction(pannelEnvironment3,"运行",":/Resouce/icons/run.svg");
    this->pannelAddLargeAction(pannelEnvironment3,"暂停",":/Resouce/icons/pause.svg");
    this->pannelAddLargeAction(pannelEnvironment3,"重置",":/Resouce/icons/reset.svg");
    this->pannelAddLargeAction(pannelEnvironment3,"毁伤评估",":/Resouce/icons/evaluate.svg");

    //标签1：高功率微波 Pannel1 ：波形选择 创建
    SARibbonPannel*pannelHpm1=categoryHpm->addPannel("波形选择");
    SARibbonGallery* galleryHpm=pannelHpm1->addGallery();
    QList<QAction*> hpmActionList;
    QAction * action1=new QAction("双指数脉冲");
    action1->setIcon(QIcon(":/Resouce/icons/doubleExp.png"));
    QAction * action2=new QAction("三指数脉冲");
    action2->setIcon(QIcon(":/Resouce/icons/TriExp.png"));
    QAction * action3=new QAction("高斯脉冲");
    action3->setIcon(QIcon(":/Resouce/icons/Gauss.png"));
    QAction * action4=new QAction("方波脉冲");
    action4->setIcon(QIcon(":/Resouce/icons/Rect.png"));
    QAction * action5=new QAction("自定义脉冲");
    action5->setIcon(QIcon(":/Resouce/icons/define.png"));
    QAction * action6=new QAction("组合脉冲");
    action6->setIcon(QIcon(":/Resouce/icons/combine.png"));
    QAction * action7=new QAction("正弦脉冲");
    action7->setIcon(QIcon(":/Resouce/icons/sinwave.png"));
    hpmActionList<<action1<<action2<<action3<<action4<<action7<<action5<<action6;
    actionGalleryGroup=galleryHpm->addCategoryActions("脉冲波形",hpmActionList);
    actionGalleryGroup->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithText);
    actionGalleryGroup->setGridMinimumWidth(80);
    galleryHpm->setCurrentViewGroup(actionGalleryGroup);
    //标签3：无人机模型 pannel2：显示模式
    SARibbonPannel*pannelModel2=categoryModel->addPannel("显示模式");
    this->pannelAddLargeAction(pannelModel2,"着色模式",":/Resouce/icons/plane.svg");
    this->pannelAddLargeAction(pannelModel2,"网格模式",":/Resouce/icons/mesh.svg");
    this->pannelAddLargeAction(pannelModel2,"线框模式",":/Resouce/icons/wireframe.svg");
    //标签3：无人机模型 pannel3：视图变换
    SARibbonPannel*pannelModel3=categoryModel->addPannel("视图变换");
    this->pannelAddLargeAction(pannelModel3,"正视图",":/Resouce/icons/Front.png");
    this->pannelAddLargeAction(pannelModel3,"左视图",":/Resouce/icons/Left.png");
    this->pannelAddLargeAction(pannelModel3,"右视图",":/Resouce/icons/Right.png");
    this->pannelAddLargeAction(pannelModel3,"俯视图",":/Resouce/icons/Top.png");
    this->pannelAddLargeAction(pannelModel3,"仰视图",":/Resouce/icons/Button.png");
    this->pannelAddLargeAction(pannelModel3,"后视图",":/Resouce/icons/Back.png");
    this->pannelAddLargeAction(pannelModel3,"Fit All",":/Resouce/icons/FitAll.svg");
    //标签3：无人机模型 pannel1 模型选择
    SARibbonPannel*pannelModel1=categoryModel->addPannel("模型选择");
    SARibbonGallery* galleryModel=pannelModel1->addGallery();
    QList<QAction*> modelActionList;
    QAction * actionModel1=new QAction("无人机类型1");
    QAction * actionModel2=new QAction("无人机类型2");
    QAction * actionModel3=new QAction("无人机类型3");
    QAction * actionModel4=new QAction("无人机类型4");
    QAction * actionModel5=new QAction("无人机类型5");
    QAction * actionModel6=new QAction("无人机类型6");
    QAction * actionModel7=new QAction("无人机类型7");

    modelActionList<<actionModel1<<actionModel2<<actionModel3<<actionModel4<<actionModel5<<actionModel6<<actionModel7;;
    ModelGroup1=galleryModel->addCategoryActions("无人机模型",modelActionList);
    ModelGroup1->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithWordWrapText);
    ModelGroup1->setGridMinimumWidth(80);
    modelActionList.clear();
    QAction * actionModelAntanna1=new QAction("天线类型1");
    QAction * actionModelAntanna2=new QAction("天线类型2");
    QAction * actionModelAntanna3=new QAction("天线类型3");


    modelActionList<<actionModelAntanna1<<actionModelAntanna2<<actionModelAntanna3;
    ModelGroup2=galleryModel->addCategoryActions("天线模型",modelActionList);
    ModelGroup2->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithWordWrapText);
    ModelGroup2->setGridMinimumWidth(80);
    modelActionList.clear();

    QAction * actionModelCable1=new QAction("线缆类型1");
    QAction * actionModelCable2=new QAction("线缆类型2");
    QAction * actionModelCable3=new QAction("线缆类型3");

    modelActionList<<actionModelCable1<<actionModelCable2<<actionModelCable3;
    ModelGroup3=galleryModel->addCategoryActions("线缆模型",modelActionList);
    ModelGroup3->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithWordWrapText);
    ModelGroup3->setGridMinimumWidth(80);
    modelActionList.clear();
    galleryModel->setCurrentViewGroup(ModelGroup1);





    //标签4：仿真 panel1
//    SARibbonPannel*pannelSimulation=categorySimulation->addPannel("仿真选项");
//    this->pannelAddLargeAction(pannelSimulation,"仿真设置");
//    this->pannelAddLargeAction(pannelSimulation,"运行");
//    QAction* loadQSS=new QAction("加载主题");
//    connect(loadQSS,&QAction::triggered,this,&MainWindow::loadTheme);
//    pannelSimulation->addLargeAction(loadQSS);
    //加载皮肤qss

    this->loadTheme(QDir::currentPath()+QDir::separator()+"my.qss");
    //设置内容窗口
    MainWidget=new QStackedWidget();
    this->setCentralWidget(MainWidget);
    HPM_Widget *hpmWidget=new HPM_Widget(hpmTimeLine);
    MainWidget->addWidget(hpmWidget);
    envirWidget=new EnvironmentWidget();
    MainWidget->addWidget(envirWidget);
    modelWidget=new ModelWidget;
    MainWidget->addWidget(modelWidget);
    simulationWidget=new SimulationWidget;
    MainWidget->addWidget(simulationWidget);
    //设置波形aciton
    connect(actionGalleryGroup,&SARibbonGalleryGroup::triggered,this,&MainWindow::OnActionGalleryGroup);//设置波形按钮
    connect(ModelGroup1,&SARibbonGalleryGroup::triggered,this,&MainWindow::onActionGalleryModelUAVGroup);//设置模型按钮
    connect(this,&MainWindow::UAVModelShow,modelWidget,&ModelWidget::loadUAVModel);

    connect(this,&MainWindow::leftWidgetshow_Hpm,hpmWidget,&HPM_Widget::leftWidgetAnimation);
    connect(this,&MainWindow::leftWidgetshow_Envir,envirWidget,&EnvironmentWidget::leftWidgetAnimation);
    connect(this,&MainWindow::leftWidgetshow_Simu,simulationWidget,&SimulationWidget::leftWidgetAnimation);
//    pannelSimulation->actions()[0]->setCheckable(true);
//    connect(pannelSimulation->actions()[0],&QAction::triggered,this,[=](){
//        emit this->leftWidgetshow_Simu(0,pannelSimulation->actions()[0]->isChecked());
//    });
    //设置action组
    for(auto x:pannelEnvironment1->actions())
    {
        x->setCheckable(true);
        connect(x,&QAction::triggered,this,[=](){
            for(auto y :pannelEnvironment1->actions())
            {
                if(y==x)continue;
                y->setChecked(false);
            }
            int index=pannelEnvironment1->actionIndex(x);
            emit this->leftWidgetshow_Envir(index,x->isChecked());
        });
    }



    connect(hpmClear,&QAction::triggered,this,[=](){
        hpmWidget->getChart()->removeAllSeries();
    });
    connect(pannelEnvironment2->actions()[0],&QAction::triggered,envirWidget,&EnvironmentWidget::selectUAV);
    connect(pannelEnvironment2->actions()[1],&QAction::triggered,envirWidget,&EnvironmentWidget::selectHPM);
    connect(pannelModel2->actions()[0],&QAction::triggered,modelWidget,&ModelWidget::setShadingDisplay);
    pannelModel2->actions()[1]->setCheckable(true);
    connect(pannelModel2->actions()[1],&QAction::triggered,this,[=](){
        modelWidget->leftWidgetAnimation(0,!pannelModel2->actions()[1]->isChecked());
    });
    connect(pannelModel2->actions()[2],&QAction::triggered,modelWidget,&ModelWidget::setWireFrameDisplay);
    for(auto x :pannelModel3->actions())
    {
        connect(x,&QAction::triggered,this,[=](){
            modelWidget->setProject(pannelModel3->actionIndex(x));
        });
    }
    connect(pannelEnvironment3->actions()[0],&QAction::triggered,envirWidget,[=](){
        envirWidget->startTimer(20);
    });
    pannelEnvironment3->actions()[1]->setCheckable(true);
    connect(pannelEnvironment3->actions()[1],&QAction::triggered,envirWidget,[=](){
        envirWidget->stopSimulation(pannelEnvironment3->actions()[1]->isChecked());
    });
    connect(pannelEnvironment3->actions()[2],&QAction::triggered,envirWidget,[=](){
        envirWidget->resetALL();
    });
    connect(pannelEnvironment3->actions()[3],&QAction::triggered,envirWidget,[=](){
//        envirWidget->createNewPlot();
        envirWidget->evaluationPlot();
    });
    connect(hpmExport,&QAction::triggered,this,[=](){
        hpmWidget->exportData();
        QMessageBox::information(this,"导出数据","成功导出数据！");
    });



}

//MainWindow::~MainWindow()
//{

//}

void MainWindow::pannelAddLargeAction(SARibbonPannel *panel, QString actionName,QString iconPath)
{
    QAction * action=new QAction(actionName);
    action->setIcon(QIcon(iconPath));
    panel->addLargeAction(action);
}

void MainWindow::pannelAddLargeAction(SARibbonPannel *panel, QString actionName)
{
    QAction * action=new QAction(actionName);
    panel->addLargeAction(action);
}

void MainWindow::loadTheme()
{

    QFile f("ribbon.qss");
    if (!f.exists()) {
        QString fdir = QFileDialog::getOpenFileName(this, tr("select qss file"));
        if (fdir.isEmpty()) {
            return;
        }
        f.setFileName(fdir);
    }
    if (!f.open(QIODevice::ReadWrite)) {
        return;
    }
    QString qss(f.readAll());
    this->setStyleSheet(qss);
}

void MainWindow::loadTheme(QString path)
{
    qDebug()<<path;
    QFile f("ribbon.qss");
    if (!f.exists()) {
        QString fdir = path;
        if (fdir.isEmpty()) {
            return;
        }
        f.setFileName(fdir);
    }
    if (!f.open(QIODevice::ReadWrite)) {
        return;
    }
    QString qss(f.readAll());
    this->setStyleSheet(qss);
}

void MainWindow::OnRibbonTabChanged(int index)
{
    MainWidget->setCurrentIndex(index);
    envirWidget->getOccWidget()->getView()->MustBeResized();
    modelWidget->getCableWidget()->getView()->MustBeResized();
    modelWidget->getAntannaWidget()->getView()->MustBeResized();
    modelWidget->getModelTreeWidget()->getView()->MustBeResized();
}

void MainWindow::OnActionGalleryGroup(QAction *action)
{
    emit this-> leftWidgetshow_Hpm( actionGalleryGroup->getActionGroup()->actions().indexOf(action),true);
}

void MainWindow::onActionGalleryModelUAVGroup(QAction *action)
{
    QString path;

    switch (ModelGroup1->getActionGroup()->actions().indexOf(action)) {
    case 0:path=QDir::currentPath()+QDir::separator()+"Models/Bayraktar TB-2.STEP";
        break;
    case 1:path=QDir::currentPath()+QDir::separator()+"Models/Boeing F A-18 E F Super Hornet.step";
        break;
    case 2:path=QDir::currentPath()+QDir::separator()+"Models/boge_solid.stp";
        break;
    case 3:path=QDir::currentPath()+QDir::separator()+"Models/dji drone body A1.stp";
        break;
    case 4:path=QDir::currentPath()+QDir::separator()+"Models/GTM drone body s27 v13.step";
        break;
    case 5:path=QDir::currentPath()+QDir::separator()+"Models/Lockheed Martin F-35 Ligtning II v2.step";
        break;
    case 6:path=QDir::currentPath()+QDir::separator()+"Models/wurenji.STEP";
        break;
    default:path="";
        break;
    }

    emit UAVModelShow(path);
}




