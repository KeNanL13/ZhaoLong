#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_cableselectdialog.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    occWidget=new OccView(this);
    QVBoxLayout* layoutGlWid = new QVBoxLayout();
    layoutGlWid->addWidget(occWidget);
    ui->tab_Model->setLayout(layoutGlWid);
    ui->tabWidget->removeTab(1);
    ui->tabWidMenu->setCurrentIndex(0);
    windowInit();
}

//界面UI初始化;
void MainWindow::windowInit()
{
    this->resize(1800,900);
//    this->showFullScreen();
//    this->setWindowState(Qt::WindowMaximized);
//    this->showMaximized();

/**********************设置进度条*************************/
    progressBar=new QProgressBar(this);
    QLabel * progressLabel=new QLabel("进度条：");
    progressBar->setTextVisible(false);
    progressBar->setMaximumWidth(200);
    ui->statusbar->addWidget(progressBar);
    ui->statusbar->addWidget(progressLabel);

/**********************分割线设置*************************/
    ui->pTextEditInfo->appendPlainText("Start new project!");
    //用作分割线
    QAction* separator1 = new QAction(this);
    separator1->setSeparator(true);
    QAction* separator2 = new QAction(this);
    separator2->setSeparator(true);
    QAction* separator3 = new QAction(this);
    separator3->setSeparator(true);
    QAction* separator4 = new QAction(this);
    separator4->setSeparator(true);
    QAction* separator5 = new QAction(this);
    separator5->setSeparator(true);

/**********************整体布局*************************/
    QVBoxLayout * mainLayout=new QVBoxLayout(this);
    QSplitter * splitterV1=new QSplitter(this);
    splitterV1->setOrientation(Qt::Vertical);
    splitterV1->addWidget(ui->scrollArea_1);
    splitterV1->addWidget(ui->tabWidConfig);
    splitterV1->setStretchFactor(0,2);
    splitterV1->setStretchFactor(1,3);

    QSplitter * splitterV2=new QSplitter(this);
    splitterV2->setOrientation(Qt::Vertical);
    splitterV2->addWidget(ui->scrollArea_3);
    splitterV2->addWidget(ui->scrollArea_4);
    splitterV2->setStretchFactor(0,5);
    splitterV2->setStretchFactor(1,1);

    QSplitter * splitterH1=new QSplitter(this);
    splitterH1->setOrientation(Qt::Horizontal);
    splitterH1->addWidget(splitterV1);
    splitterH1->addWidget(splitterV2);
    splitterH1->setStretchFactor(0,1);
    splitterH1->setStretchFactor(1,5);

    mainLayout->addWidget(ui->tabWidMenu);
    mainLayout->addWidget(splitterH1);
    mainLayout->setStretch(0,1);
    mainLayout->setStretch(1,9);
    this->centralWidget()->setLayout(mainLayout);

/**********************侧边栏布局*************************/
    menuConfigs = new QMenu("",this);
    actStdConfig = new QAction("Standard configuration");
    actMultiportS = new QAction("Mutliport S-parameter");
    actCharacteristicModes = new QAction("Characteristic modes");
    menuConfigs->addAction(actStdConfig);
    menuConfigs->addAction(actMultiportS);
    menuConfigs->addAction(actCharacteristicModes);
    ui->tBtnConfigs->setMenu(menuConfigs);
    ui->tBtnConfigs->setPopupMode(QToolButton::MenuButtonPopup);

    menuConstruction = new QMenu("",this);
    actAddVariableCons = new QAction("Add variable");
    actAddPointCons = new QAction("Add point");
    actMediaCons = new QAction("Media");
    actFieldDataCons = new QAction("Field data");
    actAddWorkPlaneCons = new QAction("Add workplane");
    actCableDefinitionCons = new QAction("Cable defination");
    actPort = new QAction("Port");
    actMeshRefinement = new QAction("Mesh refinement");
    actPlaneGround = new QAction("Plane/ground");
    actFiniteArrays = new QAction("Finite arrays");
    actOptimisation = new QAction("Optimisation");
    menuConstruction->addAction(actAddVariableCons);
    menuConstruction->addAction(actAddPointCons);
    menuConstruction->addAction(actMediaCons);
    menuConstruction->addAction(actFieldDataCons);
    menuConstruction->addAction(actAddWorkPlaneCons);
    menuConstruction->addAction(actCableDefinitionCons);
    menuConstruction->addAction(separator1);
    menuConstruction->addAction(actPort);
    menuConstruction->addAction(actMeshRefinement);
    menuConstruction->addAction(actPlaneGround);
    menuConstruction->addAction(actFiniteArrays);
    menuConstruction->addAction(separator2);
    menuConstruction->addAction(actOptimisation);
    ui->tBtnItems->setMenu(menuConstruction);
    ui->tBtnItems->setPopupMode(QToolButton::MenuButtonPopup);

    menuConfig1 = new QMenu("",this);
    actSolverSettings = new QAction("Solver Settings");
    actFreqPerConfig = new QAction("Frequency per configuration");
    actSrcPerConfig = new QAction("Sources per configuration");
    actLoadsPerConfig = new QAction("Loads per configuration");
    actPowerPerConfig = new QAction("Power per configuration");
    menuConfig1->addAction(actSolverSettings);
    menuConfig1->addAction(separator3);
    menuConfig1->addAction(actFreqPerConfig);
    menuConfig1->addAction(actSrcPerConfig);
    menuConfig1->addAction(actLoadsPerConfig);
    menuConfig1->addAction(actPowerPerConfig);
    ui->tBtnConfig1->setMenu(menuConfig1);
    ui->tBtnConfig1->setPopupMode(QToolButton::MenuButtonPopup);

    menuConfig2 = new QMenu("",this);
    actAddVariableConfig = new QAction("Add variable");
    actAddPointConfig = new QAction("Add point");
    actMediaConfig = new QAction("Media");
    actFieldDataConfig = new QAction("Field data");
    actAddWorkPlaneConfig = new QAction("Add workplane");
    actCableDefinitionConfig = new QAction("Cable definition");
    actFrequency = new QAction("Frequency");
    actAddRequest = new QAction("Add request");
    actSource = new QAction("Source");
    actAddLoad = new QAction("Add load");
    actNetwork = new QAction("Network");
    actPower = new QAction("Power");
    menuConfig2->addAction(actAddVariableConfig);
    menuConfig2->addAction(actAddPointConfig);
    menuConfig2->addAction(actMediaConfig);
    menuConfig2->addAction(actFieldDataConfig);
    menuConfig2->addAction(actAddWorkPlaneConfig);
    menuConfig2->addAction(actCableDefinitionConfig);
    menuConfig2->addAction(separator4);
    menuConfig2->addAction(actFrequency);
    menuConfig2->addAction(actAddRequest);
    menuConfig2->addAction(separator5);
    menuConfig2->addAction(actSource);
    menuConfig2->addAction(actAddLoad);
    menuConfig2->addAction(actNetwork);
    menuConfig2->addAction(actPower);
    ui->tBtnConfig2->setMenu(menuConfig2);
    ui->tBtnConfig2->setPopupMode(QToolButton::MenuButtonPopup);

    //Home布局
    menuImport = new QMenu("Import",this);
    actCADFEKOModel = new QAction("CADFEKO Model(*.cfx)");
    menuImport->addAction(actCADFEKOModel);
    actKBLFile = new QAction("KBL File(*.kbl)");
    menuImport->addAction(actKBLFile);
    actOsgFile=new QAction("OSG Model(*.osg)");
    menuImport->addAction(actOsgFile);
    actGeometryI = new QAction("Geometry");
    menuImport->addAction(actGeometryI);
    actMeshI = new QAction("Mesh");
    menuImport->addAction(actMeshI);

    ui->tBtnImport->setMenu(menuImport);
    ui->tBtnImport->setPopupMode(QToolButton::MenuButtonPopup);

    menuExport = new QMenu("Export",this);
    actGeometryE = new QAction("Geometry");
//    actGeometryE->setMenu();
    menuExport->addAction(actGeometryE);
    actMeshE = new QAction("Mesh");
//    actMeshE->setMenu();
    menuExport->addAction(actMeshE);
    actMeshBoundary = new QAction("Mesh Boundary");
//    actMeshBoundary->setMenu();
    menuExport->addAction(actMeshBoundary);
    ui->tBtnExport->setMenu(menuExport);
    ui->tBtnExport->setPopupMode(QToolButton::MenuButtonPopup);

    menuSchematic = new QMenu("Schematic",this);
    actNetworkSchematic = new QAction("Network Schematic");
    menuSchematic->addAction(actNetworkSchematic);
    ui->tBtnSchematic->setMenu(menuSchematic);
    ui->tBtnSchematic->setPopupMode(QToolButton::MenuButtonPopup);

    menuApplicationMacro = new QMenu("Application Macro",this);
    actMacroLibrary = new QAction("Macro Library...");
    menuApplicationMacro->addAction(actMacroLibrary);
    actParameterSweep = new QAction("Parameter Sweep:Create models");
    menuApplicationMacro->addAction(actParameterSweep);
    actOptenniLab = new QAction("Optenni Lab:Port match");
    menuApplicationMacro->addAction(actOptenniLab);
    ui->tBtnAppMacro->setMenu(menuApplicationMacro);
    ui->tBtnAppMacro->setPopupMode(QToolButton::MenuButtonPopup);

/**********************列表树*************************/
    configsModel = new QStandardItemModel(ui->listConfigs);
    configs1 = new QStandardItem("Standard configuration");
    configsModel->appendRow(configs1);
    ui->listConfigs->setModel(configsModel);
    //Construction 树
    ModelTree modelTree;
    QVector<double> parameters;
    parameters.push_back(eps0);parameters.push_back(mu0);parameters.push_back(pi);
    constructModel=modelTree.getConstructModel(parameters);

    ui->treeViewItems->setHeaderHidden(true);
    ui->treeViewItems->setModel(constructModel);
    //Configure 树
    configModel=modelTree.getConfigurationModel(parameters);
    ui->treeViewConfig->setHeaderHidden(true);
    ui->treeViewConfig->setModel(configModel);

/**********************功能连接*************************/
    //点击关闭按钮,关闭tab的功能
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&MainWindow::closeTab);
    //读取STEP文件功能
    connect(actOsgFile,&QAction::triggered,[=](){
        QString w1=QFileDialog::getOpenFileName(this,"Find Step","E:/");
        if(w1.isNull())
        {
            return;
        }
        this->loadStepModel(w1);
    });
    //视图按钮
    connect(ui->tBtnViewLeft,&QToolButton::clicked,[=](){
        occWidget->getView()->SetProj(V3d_TypeOfOrientation_Zup_Left);
        occWidget->getView()->Update();
    });
    connect(ui->tBtnViewBack,&QToolButton::clicked,[=](){
        occWidget->getView()->SetProj(V3d_TypeOfOrientation_Zup_Back);
        occWidget->getView()->Update();
    });
    connect(ui->tBtnViewRight,&QToolButton::clicked,[=](){
        occWidget->getView()->SetProj(V3d_TypeOfOrientation_Zup_Right);
        occWidget->getView()->Update();
    });
    connect(ui->tBtnViewTop,&QToolButton::clicked,[=](){
        occWidget->getView()->SetProj(V3d_TypeOfOrientation_Zup_Top);
        occWidget->getView()->Update();
    });
    connect(ui->tBtnViewBottom,&QToolButton::clicked,[=](){
        occWidget->getView()->SetProj(V3d_TypeOfOrientation_Zup_Bottom);
        occWidget->getView()->Update();
    });
    connect(ui->tBtnVIewFront,&QToolButton::clicked,[=](){
        occWidget->getView()->SetProj(V3d_TypeOfOrientation_Zup_Front);
        occWidget->getView()->Update();
    });
    connect(ui->tBtnViewFit,&QToolButton::clicked,[=](){
        occWidget->getView()->FitAll();
        occWidget->getView()->Update();
    });
}

MainWindow::~MainWindow()
{
//    threadRun->quit();
//    threadRun->wait();
    delete ui;
}

/**********************点击线缆按钮,触发模型选择选项对话*************************/
void MainWindow::on_tBtnCables_clicked()
{
    cableDialog=new CableSelectDialog();
    cableDialog->setWindowModality(Qt::ApplicationModal);
    cableDialog->show();
    cableDialog->setAttribute(Qt::WA_DeleteOnClose);
    //当线缆模型选择对话框选择完以后，发送对应的线缆模型信号，其中包括线缆类型和模型路径，使用calbeTreeShow函数接收
    connect(cableDialog,&CableSelectDialog::CableSignal,this,&MainWindow::cableTreeShow);
}


/******************************************模型树和模型显示*********************************************/
void MainWindow::cableTreeShow(enum CableSelectDialog::modelType model,QString stepModelPath)
{
    modelType=model;
    if(detailModel!=nullptr)
    {
        parameterVector.clear();
        detailModel->~QStandardItemModel();
    }
    ModelTree modeltree;
    for ( auto x : cableDialog->parameters)
    {
        m_Parameters.push_back(x);
    }
    cableDialog->parameters.clear();
    switch (modelType) {
    case CableSelectDialog::ParallelCable:
         detailModel=modeltree.getParallelCableModel(m_Parameters);
        break;
    case CableSelectDialog::SystemS_parameters:
        detailModel=modeltree.getFixtureAndCableModel(m_Parameters);
        break;
    case CableSelectDialog::TWP_Cable:
        detailModel=modeltree.getTWPcableModel(m_Parameters);
        break;
    case CableSelectDialog::HighSpped:
        detailModel=modeltree.getHighSpeedModel(m_Parameters);
        break;
    default:
        break;
    }
    parameterVector=modeltree.getParameterVector();
    ui->treeViewDetails->setModel(detailModel);
    m_Parameters.clear();

    //显示模型
    loadStepModel(stepModelPath);
    //跳转到运行按钮
    ui->tabWidMenu->setCurrentIndex(6);
}

/************************关闭TabWidget页面************************/
void MainWindow::closeTab(int i)
{
    //第一页是occ模型显示，不用关闭
    if(i==0)
    {
        return;
    }
    ui->tabWidget->removeTab(i);
    ui->tabWidget->widget(i)->deleteLater();
}

/************************用来接收计算结果，并显示出来，同时还有进度条的更新************************/
void MainWindow::updataTabWidget(QVector<QVector<double>> result,QVector<QString>name)
{

    ChartShow(ui->tabWidget,result,name);
    progressBar->setRange(0,100);
    progressBar->setValue(100);
    progressBar->setFormat(tr("完成"));
    QTimer::singleShot(3000,[=](){
        progressBar->setValue(0);
        progressBar->setFormat(tr(" "));
    });

}

/************************运行按钮，另外开一个计算线程来计算************************/
void MainWindow::on_tBtnRun_clicked()
{
    //开创计算线程并新建一个线缆求解器
    SolverCable  *solver=new SolverCable;
    threadRun=new QThread(this);
    solver->moveToThread(threadRun);
    threadRun->start();
    //关联信号与计算函数
    connect(this,&MainWindow::runSystemS_parameters,solver,&SolverCable::System_SParametersFunction);
    connect(this,&MainWindow::runParallel,solver,&SolverCable::ParallelCableFunction);
    connect(this,&MainWindow::runTWP,solver,&SolverCable::TWP_CableFunction);
    connect(this,&MainWindow::runHighSpped,solver,&SolverCable::HighSpeedFunction);

    //计算结束后处理
    connect(solver,&SolverCable::caculateDone,this,&MainWindow::updataTabWidget,Qt::QueuedConnection);
    connect(solver,&SolverCable::caculateDone,[=](){
        solver->deleteLater();
        threadRun->quit();
    });
    //对于不同的模型类型，发送不同的信号
    switch (modelType)
    {
    case CableSelectDialog::SystemS_parameters:
        emit runSystemS_parameters(parameterVector[0]->text(),parameterVector[1]->text());
        break;
    case CableSelectDialog::ParallelCable:
        emit runParallel(parameterVector[0]->text().toDouble(),parameterVector[1]->text().toDouble(),
                parameterVector[2]->text().toDouble(),parameterVector[3]->text().toDouble(),
                parameterVector[4]->text().toDouble(),parameterVector[5]->text().toDouble(),
                parameterVector[6]->text().toDouble(),parameterVector[7]->text().toDouble(),
                parameterVector[8]->text().toDouble());
        break;
    case CableSelectDialog::TWP_Cable:
        emit runTWP(parameterVector[0]->text().toDouble(),parameterVector[1]->text().toDouble(),
                parameterVector[2]->text().toDouble(),parameterVector[3]->text().toDouble(),
                parameterVector[4]->text().toDouble(),parameterVector[5]->text().toDouble(),
                parameterVector[6]->text().toDouble(),parameterVector[7]->text().toDouble(),
                parameterVector[8]->text().toDouble(),parameterVector[9]->text().toDouble());
        break;

    case CableSelectDialog::HighSpped:
        if(parameterVector[7]->text().mid(0,1)=="铝")
        {
            parameterVector[7]->setText("38160000");
        }
        if(parameterVector[8]->text().mid(0,1)=="铜")
        {
            parameterVector[8]->setText("58130000");
        }
        emit runHighSpped(parameterVector[0]->text().toDouble()*0.001,parameterVector[1]->text().toDouble()*0.001,
                parameterVector[2]->text().toDouble()*0.001,parameterVector[3]->text().toDouble(),
                parameterVector[4]->text().toDouble(),parameterVector[5]->text().toDouble()*0.001,
                parameterVector[6]->text().toDouble()*0.001,parameterVector[7]->text().toDouble(),
                parameterVector[8]->text().toDouble(),parameterVector[9]->text().toDouble()*0.001);
        break;
    default: break;
    }
        progressBar->setRange(0,0);
        progressBar->setFormat(tr("运行中"));
}

void MainWindow::loadStepModel(QString path)
{
    if(path.isEmpty())
    {
        occWidget->getContext()->RemoveAll(Standard_True);
        return;
    }
    occRead * occreader=new occRead(occWidget->getContext());
    QThread * threadLoadModel=new QThread(this);
    occreader->moveToThread(threadLoadModel);
    threadLoadModel->start();
    connect(this,&MainWindow::readStepSignal,occreader,&occRead::ReadStep);
    connect(occreader,&occRead::readDone,this,&MainWindow::updateTree,Qt::QueuedConnection);
    connect(occreader,&occRead::readDone,[=](){
        occreader->deleteLater();
        threadLoadModel->quit();
    });
    emit this->readStepSignal(path);
}




void MainWindow::ChartShow(QTabWidget *tabWidget,QVector<QVector<double>> data,QVector<QString>name)
{
    ChartWidget * chartWidget=new ChartWidget(data,name);
    tabWidget->addTab(chartWidget,"S-Parameters");
    tabWidget->setCurrentIndex(tabWidget->indexOf(chartWidget));
}

void MainWindow::updateTree(QStandardItem*item)
{
    Handle(AIS_ViewCube)axisCube=new AIS_ViewCube();
    Handle(Graphic3d_TransformPers) gtrans=new Graphic3d_TransformPers(
                Graphic3d_TMF_TriedronPers,
                Aspect_TOTP_RIGHT_UPPER,
                Graphic3d_Vec2i(85, 85));
    axisCube->SetTransformPersistence(gtrans);
    axisCube->SetAutoHilight(true);
    axisCube->SetFixedAnimationLoop (false);
    axisCube->SetAutoStartAnimation(true);
    occWidget->getContext()->Display(axisCube,Standard_True);
    occWidget->getView()->FitAll();
    constructModel->clear();
    ModelTree modelTree;
    QVector<double> parameters;
    parameters.push_back(eps0);parameters.push_back(mu0);parameters.push_back(pi);
    constructModel=modelTree.getConstructModel(parameters);
    constructModel->appendRow(item);
    ui->treeViewItems->setModel(constructModel);
}
