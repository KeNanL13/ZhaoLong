#include "mainwindow.h"

#include <SAFramelessHelper.h>
#include <SARibbonBar.h>
#include <QTimer>
#include <qtmaterialtextfield.h>
#include <QColorDialog>
#include <QMetaType>
#include <qtmaterialcircularprogress.h>
#include <QGraphicsOpacityEffect>
#include <QGraphicsDropShadowEffect>

MainWindow::MainWindow(QWidget *parent) :
    SARibbonMainWindow(parent)
{
    result=new ChartWidget();
    SAFramelessHelper * helper=framelessHelper();
    helper->setBorderWidth(5);
    helper->setRubberBandOnResize(false);
    this->setWindowIcon(QIcon(":/res/icon/titleIcon.svg"));
    this->ribbonBar()->setWindowTitleTextColor(QColor(255,255,255));
    //    this->ribbonBar()->setRibbonStyle(SARibbonBar::OfficeStyleTwoRow);
    this->ribbonBar()->setContentsMargins(0, 0, 0, 0);

    this->resize(1200,800);
    this->setMinimumWidth(500);
    //    this->ribbonBar()->applicationButton()->setVisible(false);
    this->setWindowTitle("线缆仿真软件");
    this->ribbonBar()->setFont(QFont("微软雅黑",13));
    //加载主题
    QString themePath=QApplication::applicationDirPath()+"/Theme/dark/my.qss";

    this->loadTheme(themePath);
    //总标签页
    SARibbonCategory*categoryMain=this->ribbonBar()->addCategoryPage(tr("主页"));
    SARibbonCategory*categoryModel=this->ribbonBar()->addCategoryPage(tr("模型"));
    contextcategory=this->ribbonBar()->addContextCategory(tr("结果"),QColor(22,97,171));
    SARibbonCategory* categoryResult=contextcategory->addCategoryPage(tr(""));

    SARibbonCategory*categoryRecord=this->ribbonBar()->addCategoryPage(tr("历史记录"));



    //标签1 主页
    SARibbonPannel*pannelMain1=categoryMain->addPannel("设置");
    QAction * actionSetting=new QAction("全局设置");
    actionSetting->setIcon(QIcon(":/res/icon/Setting2.svg"));
    pannelMain1->addLargeAction(actionSetting);

    QAction * actionRun=new QAction("运行");
    actionRun->setIcon(QIcon(":/res/icon/run.svg"));
    pannelMain1->addLargeAction(actionRun);

    SARibbonPannel*pannelMain2=categoryMain->addPannel("线缆类型选择");
    SARibbonGallery* galleryCable=pannelMain2->addGallery();
    QList<QAction*> ActionList;
    QAction * action1=new QAction("平行线");
    action1->setIcon(QIcon(":/res/icon/Control Cable.svg"));
    QAction * action2=new QAction("双绞线");
    action2->setIcon(QIcon(":/res/icon/Control Cable.svg"));
    QAction * action3=new QAction("高速线");
    action3->setIcon(QIcon(":/res/icon/Control Cable.svg"));

    ActionList<<action1<<action2<<action3;
    cableGroup=galleryCable->addCategoryActions("线缆类型",ActionList);
    cableGroup->setGalleryGroupStyle(SARibbonGalleryGroup::IconWithText);
    cableGroup->setGridMinimumWidth(80);
    galleryCable->setCurrentViewGroup(cableGroup);


    //标签2 模型
    SARibbonPannel * pannelModel1=categoryModel->addPannel("显示模式");
    this->pannelAddLargeAction(pannelModel1,"着色模式",":/res/icon/chuanshuxian.png");
    this->pannelAddLargeAction(pannelModel1,"网格模式",":/res/icon/wangge.png");
    this->pannelAddLargeAction(pannelModel1,"线框模式",":/res/icon/wireframe.svg");

    SARibbonPannel*pannelModel2=categoryModel->addPannel("视图变换");
    this->pannelAddLargeAction(pannelModel2,"正视图",":/res/icon/Front.png");
    this->pannelAddLargeAction(pannelModel2,"左视图",":/res/icon/Left.png");
    this->pannelAddLargeAction(pannelModel2,"右视图",":/res/icon/Right.png");
    this->pannelAddLargeAction(pannelModel2,"俯视图",":/res/icon/Top.png");
    this->pannelAddLargeAction(pannelModel2,"仰视图",":/res/icon/Button.png");
    this->pannelAddLargeAction(pannelModel2,"后视图",":/res/icon/Back.png");
    this->pannelAddLargeAction(pannelModel2,"Fit All",":/res/icon/FitAll.svg");

    //标签3 仿真结果
    SARibbonPannel * pannelResult1=categoryResult->addPannel("保存设置");
    this->pannelAddLargeAction(pannelResult1,"保存图片",":/res/icon/image.svg");
    this->pannelAddLargeAction(pannelResult1,"保存为Excel",":/res/icon/excel.svg");
    SARibbonPannel * pannelResult2=categoryResult->addPannel("图元变换");
    this->pannelAddLargeAction(pannelResult2,"线性坐标轴",":/res/icon/axis.svg");
    this->pannelAddLargeAction(pannelResult2,"指数坐标轴",":/res/icon/axis.svg");
    SARibbonPannel * pannelResult3=categoryResult->addPannel("列表操作");
    this->pannelAddLargeAction(pannelResult3,"删除",":/res/icon/delete.svg");
    this->pannelAddLargeAction(pannelResult3,"导入CSV数据",":/res/icon/csv.svg");
    this->pannelAddLargeAction(pannelResult3,"修改名称",":/res/icon/rename-box.svg");
    this->pannelAddLargeAction(pannelResult3,"修改颜色",":/res/icon/color.svg");
    //标签4 历史记录
    SARibbonPannel * pannelRecord1=categoryRecord->addPannel("设置");
    this->pannelAddLargeAction(pannelRecord1,"清空记录",":/res/icon/clear.svg");

    //    设置主界面
    stackWidget=new QStackedWidget();

    this->setCentralWidget(stackWidget);
    mainWidget=new NewContentWidget();
    stackWidget->addWidget(mainWidget);

    tableWidget=new recordWidget;
    stackWidget->addWidget(tableWidget);
    //设置切换Tab
    connect(this->ribbonBar(),&SARibbonBar::currentRibbonTabChanged,this,&MainWindow::OnRibbonTabChanged);
    //设置点击线缆组的槽函数
    connect(cableGroup,&SARibbonGalleryGroup::triggered,this,&MainWindow::onActionCableGroupTrigger);
    //设置运行按钮
    connect(actionRun,&QAction::triggered,this,&MainWindow::onActionRun);
    //设置历史记录中 清空记录按钮
    connect(pannelRecord1->actions()[0],&QAction::triggered,this,[=](){
        tableWidget->deleteAllData();
    });
    //设置ModelPanenl2 用于变换视角
    for(int i=0;i<pannelModel2->actions().size();i++)
    {
        connect(pannelModel2->actions()[i],&QAction::triggered,this,[=](){
            mainWidget->setProject(i);
        });
    }
    //记录界面点击运行
//    connect(tableWidget,&recordWidget::recordRun,this,&MainWindow::onRecordRun);/**********fix*******/
    //设置默认线缆
    //    this->onActionCableGroupTrigger(action3);
    //设置结果窗口Action功能
    connect(contextcategory->categoryPage(0)->pannelByIndex(0)->actions()[0],&QAction::triggered,result,&ChartWidget::saveGraph);
    connect(contextcategory->categoryPage(0)->pannelByIndex(0)->actions()[1],&QAction::triggered,result,&ChartWidget::saveExcel);
    connect(contextcategory->categoryPage(0)->pannelByIndex(1)->actions()[0],&QAction::triggered,this,[=](){
        result->changeX(true);
    });
    connect(contextcategory->categoryPage(0)->pannelByIndex(1)->actions()[1],&QAction::triggered,this,[=](){
        result->changeX(false);
    });
    connect(contextcategory->categoryPage(0)->pannelByIndex(2)->actions()[0],&QAction::triggered,this,[=](){
        result->removeItem();
    });
    connect(contextcategory->categoryPage(0)->pannelByIndex(2)->actions()[1],&QAction::triggered,this,[=](){
        QString path=QFileDialog::getOpenFileName(this,"CSV文件");
        if(path=="")return;
        result->readCSVFile(path);
    });
    connect(contextcategory->categoryPage(0)->pannelByIndex(2)->actions()[2],&QAction::triggered,this,[=](){
        if(result->isHasMainProject())
        {

            dialog->showDialog();
        }

    });
    connect(contextcategory->categoryPage(0)->pannelByIndex(2)->actions()[3],&QAction::triggered,this,[=](){
        if(result->isSelectItem())
        {
            QColor color=QColorDialog::getColor();
            result->setGraphColor(color);
        }

    });
    connect(this,&MainWindow::setProjectNameSig,result,&ChartWidget::setItemName);
    //初始化命名对话框
    this->ProjectNameDialogSetup();



    //初始化线缆求解器和对应线程
    solverThread=new QThread();
    solver_cable=new Solver_Cable();
    solver_cable->moveToThread(solverThread);

    //多线程资源管理
    connect(solverThread,&QThread::started,solver_cable,&Solver_Cable::init);
    connect(solverThread,&QThread::finished,solver_cable,&Solver_Cable::deleteLater);
    connect(solverThread,&QThread::finished,solverThread,&QThread::deleteLater);
    connect(solverThread,&QThread::destroyed,this,[=](){
        solverThread=nullptr;
    });
    connect(solver_cable,&Solver_Cable::destroyed,this,[=](){
        solver_cable=nullptr;
    });
    //连接相关任务
    qRegisterMetaType<QVector<double>>("QVector<double>");
    qRegisterMetaType<QVector<QString>>("QVector<QString>");
    connect(this,&MainWindow::highSpeedSignal,solver_cable,&Solver_Cable::solver_HighSpeedCable);
    connect(solver_cable,&Solver_Cable::caculateDone,this,&MainWindow::dealWithResults);


    solverThread->start();
    //传输信息到数据库
    connect(mainWidget,&NewContentWidget::transInfo,tableWidget,&recordWidget::insert);
    //接受数据库信号并运行数据
    connect(tableWidget,&recordWidget::recordRun,this,&MainWindow::onRecordRun);



}

MainWindow::~MainWindow()
{

}
void MainWindow::loadTheme(QString path)
{
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

void MainWindow::pannelAddLargeAction(SARibbonPannel *panel, QString actionName,QString iconPath)
{
    QAction * action=new QAction(actionName);
    action->setIcon(QIcon(iconPath));
    panel->addLargeAction(action);
}

void MainWindow::onActionCableGroupTrigger(QAction *action)
{
    int index=cableGroup->getActionGroup()->actions().indexOf(action);
    SettingWidget_Base::CableType type=SettingWidget_Base::None;
    switch (index) {
    case 0:type=SettingWidget_Base::SingleCable;break;
    case 1:type=SettingWidget_Base::TwistCable;break;
    case 2:type=SettingWidget_Base::HighSpeedCable;break;
    default:
        type=SettingWidget_Base::None;
        break;
    }

    mainWidget->showToolWidget(type);
    currentIndex=index;

}

void MainWindow::onActionRun()
{
    if(!mainWidget->isInputComplete() || runningFlag)
    {
        QMessageBox::warning(this,"警告","请输入完整的参数");
        return;
    }

    if(runningDialog==nullptr)
    {
        runningDialogSetup();
    }
    //开始运行
    runningFlag=true;
    //进入加载界面
    stackWidget->addWidget(result);
    this->ribbonBar()->showContextCategory(contextcategory);
    ribbonBar()->setCurrentIndex(3);
    runningDialog->showDialog();
    //数据处理
    QVector<double> data_num;
    QVector<QString>data_text;


    data_num=mainWidget->getInputParameter_Num();
    data_text=mainWidget->getInputParameter_Text();

    if(data_text.size()==0)
    {
        return ;
    }
    qDebug()<<currentIndex;
    if(currentIndex==2)
    {
        QString s4pPath;
        if(isDirExist(QString(QApplication::applicationDirPath()+"/S4P_File")))
        {
            s4pPath=QString(QApplication::applicationDirPath()+"/S4P_File/"+data_text[0]+".s4p");
            while(isFileExist(s4pPath))
            {
                s4pPath=s4pPath.split(".")[0]+"(1)"+".s4p";
            }
            s4pPath=s4pPath.split(".")[0];
            data_text.insert(1,s4pPath);
        }
    }
    qDebug()<<data_num;
    qDebug()<<data_text;

    switch (currentIndex) {
    case 0:
        break;
    case 1:
        break;
    case 2:

        emit highSpeedSignal(data_num,data_text);
        break;
    default:
        break;
    }

    //发送参数信号
    mainWidget->sendInputMessage();






    runningFlag=false;
}

void MainWindow::dealWithResults(QVector<QVector<double> > datas, QVector<QString> names, QString title)
{
    if(result==nullptr)return;

    result->addItem(datas,names,title);
//    stackWidget->addWidget(result);
////    stackWidget->setCurrentIndex(2);
//    this->ribbonBar()->showContextCategory(contextcategory);
//    this->ribbonBar()->setCurrentIndex(3);
}

void MainWindow::OnRibbonTabChanged(int index){
    switch (index) {
    case 0:stackWidget->setCurrentIndex(0);
        mainWidget->occResize();
        break;
    case 1:stackWidget->setCurrentIndex(0);
        mainWidget->occResize();
        break;
    case 2:stackWidget->setCurrentIndex(1);
        break;
    case 3:stackWidget->setCurrentIndex(2);
    default:
        break;
    }
}

void MainWindow::onRecordRun(int type, QStringList valueList)
{
    //进入加载页面
    if(runningDialog==nullptr)
    {
        runningDialogSetup();
    }
    stackWidget->addWidget(result);
    this->ribbonBar()->showContextCategory(contextcategory);
    ribbonBar()->setCurrentIndex(3);
    runningDialog->showDialog();

    QVector<double>dataNum;
    QVector<QString>dataText;
    dataText.push_back(valueList[1]);
    valueList.removeFirst();
    valueList.removeFirst();

    //针对高速线缆修改夹具路径和。s4p路径
    if(type==2)
    {
        QString s4pPath;
        if(isDirExist(QString(QApplication::applicationDirPath()+"/S4P_File")))
        {
            s4pPath=QString(QApplication::applicationDirPath()+"/S4P_File/"+dataText[0]+".s4p");
            while(isFileExist(s4pPath))
            {
                s4pPath=s4pPath.split(".")[0]+"(1)"+".s4p";
            }
            s4pPath=s4pPath.split(".")[0];
            dataText.push_back(s4pPath);
        }

    if(!this->isFileExist(QDir::currentPath()+"/Fixture/"+valueList.last()))
    {
        QMessageBox::warning(tableWidget,"警告","夹具位置不存在！");
        return;
    }
    dataText.push_back(QDir::currentPath()+"/"+valueList.last());
    valueList.removeLast();
    }
    for(auto x :valueList)
    {
        dataNum.push_back(x.toDouble());
    }



    //根据类型发送对应信号
    switch (type) {
    case 0:
        break;
    case 1:
        break;
    case 2:

        emit highSpeedSignal(dataNum,dataText);
        break;
    default:
        break;
    }
}

void MainWindow::ProjectNameDialogSetup()
{
    if(dialog!=nullptr)
    {
        delete dialog;
        dialog=nullptr;
    }
    dialog=new QtMaterialDialog;
    //    dialog->setParent(this);
    dialog->setParent(result);
    QWidget *widget=new QWidget();
    QHBoxLayout *layout=new QHBoxLayout;
    QtMaterialTextField *textLine=new QtMaterialTextField;
    textLine->setLabel("项目名称:");
    QtMaterialFlatButton * btn1=new QtMaterialFlatButton("确定");
    QtMaterialFlatButton * btn2=new QtMaterialFlatButton("取消");
    layout->addWidget(textLine);
    layout->addWidget(btn1);
    layout->addWidget(btn2);
    widget->setLayout(layout);
    QVBoxLayout * layout2=new QVBoxLayout;
    layout2->addWidget(widget);

    dialog->setWindowLayout(layout2);

    connect(btn2,&QtMaterialFlatButton::clicked,this,[=](){
        dialog->hideDialog();
        textLine->clear();
    });
    connect(btn1,&QtMaterialFlatButton::clicked,this,[=](){
        dialog->hideDialog();
        if(!textLine->text().isNull()&&!textLine->text().isEmpty())
        {
            emit setProjectNameSig(textLine->text());
        }
        textLine->clear();
    });
}

void MainWindow::runningDialogSetup()
{
    qDebug()<<"createRunningDialog";
    runningDialog=new QtMaterialDialog(result);

    QVBoxLayout * runningDialogLayout=new QVBoxLayout();
    QtMaterialCircularProgress * progress=new QtMaterialCircularProgress();
    progress->setSize(80);

    QLabel * tipLabel=new QLabel("Tips:Waiting for the result.");
    tipLabel->setFont(QFont("DengXian",12,QFont::Normal));

    QWidget* finishWidget=new QWidget;
    QHBoxLayout * layout=new QHBoxLayout;
    layout->setContentsMargins(0,0,0,0);
    layout->addStretch();

    QLabel * finishLabel=new QLabel;
    finishLabel->setPixmap(QPixmap(":/res/icon/finish.svg"));

    layout->addWidget(finishLabel);
    layout->addStretch();
    finishWidget->setLayout(layout);
    finishLabel->setFont(QFont("Font Awesome 6 Free Solid",14));
//    finishLabel->setText("\uf058");
//    QPalette red;
//    red.setColor(QPalette::WindowText,Qt::green);
//    finishLabel->setPalette(red);

//    finishLabel->hide();
    finishLabel->setAlignment(Qt::AlignCenter);
//    finishLabel->setFixedSize(80,80);

    QWidget * buttonWidget=new QWidget;
    QtMaterialFlatButton * btn1=new QtMaterialFlatButton("确定");
    QtMaterialFlatButton * btn2=new QtMaterialFlatButton("取消");
    QHBoxLayout * buttonWidgetLayout=new QHBoxLayout();
    buttonWidgetLayout->addWidget(btn1);
    buttonWidgetLayout->addWidget(btn2);
    buttonWidgetLayout->setSpacing(50);
    buttonWidgetLayout->setAlignment(Qt::AlignCenter);
    buttonWidget->setLayout(buttonWidgetLayout);

    runningDialogLayout->addWidget(progress);
    runningDialogLayout->addWidget(finishWidget);
    runningDialogLayout->addWidget(tipLabel);
    runningDialogLayout->addWidget(buttonWidget);

    tipLabel->setAlignment(Qt::AlignCenter);
    runningDialogLayout->addSpacing(8);
    runningDialogLayout->setAlignment(Qt::AlignCenter);

    runningDialog->setWindowLayout(runningDialogLayout);

    btn1->setBackgroundColor(QColor(16,174,194));
    btn1->setCornerRadius(8);
    btn1->setOverlayColor(QColor(16,174,194));
    btn1->setForegroundColor(QColor(16,174,194));

    btn2->setBackgroundColor(QColor(194,31,48));
    btn2->setCornerRadius(8);
    btn2->setOverlayColor(QColor(194,31,48));
    btn2->setForegroundColor(QColor(194,31,48));

    buttonWidget->hide();
    finishWidget->hide();

    connect(btn1,&QtMaterialFlatButton::clicked,this,[=](){
        runningDialog->hideDialog();
//        stackWidget->setCurrentIndex(2);
//        this->ribbonBar()->setCurrentIndex(3);
    });
    connect(btn2,&QtMaterialFlatButton::clicked,this,[=](){
        runningDialog->hideDialog();
    });
    connect(solver_cable,&Solver_Cable::finished,this,[=](){
        buttonWidget->show();
        tipLabel->setText("Tips:计算结束，点击确定查看结果！");
        finishWidget->show();
        progress->hide();

    });
}

bool MainWindow::isDirExist(QString fullPath)
{


    QDir dir(fullPath);
    if(dir.exists())
    {
        return true;
    }
    else{
        bool flag=dir.mkdir(fullPath);
        return flag;
    }

}

bool MainWindow::isFileExist(QString fullFileName)
{
    QFileInfo fileinfo(fullFileName);
    if(fileinfo.isFile())
    {
        return true;
    }
    return false;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    solverThread->quit();
    solverThread->wait();
}



