#include "mainwindow.h"

#include <SAFramelessHelper.h>
#include <SARibbonBar.h>
#include <QTimer>
#include <qtmaterialtextfield.h>
#include <QColorDialog>

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
    this->resize(800,600);
    this->setMinimumWidth(500);
//    this->ribbonBar()->applicationButton()->setVisible(false);
    this->setWindowTitle("线缆仿真软件");
    this->ribbonBar()->setFont(QFont("微软雅黑",13));
    //加载主题
    QString themePath=QDir::currentPath()+QDir::separator()+"my.qss";
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
    action1->setIcon(QIcon(":/Resouce/icons/doubleExp.png"));
    QAction * action2=new QAction("双绞线");
    action2->setIcon(QIcon(":/Resouce/icons/TriExp.png"));
    QAction * action3=new QAction("高速线");
    action3->setIcon(QIcon(":/Resouce/icons/Gauss.png"));

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
    this->pannelAddLargeAction(pannelResult3,"修改名称","");
    this->pannelAddLargeAction(pannelResult3,"修改颜色","");
    //标签4 历史记录
    SARibbonPannel * pannelRecord1=categoryRecord->addPannel("设置");
    this->pannelAddLargeAction(pannelRecord1,"清空记录",":/res/icon/clear.svg");

//    设置主界面
    stackWidget=new QStackedWidget();

    this->setCentralWidget(stackWidget);
    mainWidget=new contentWidget();
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
    connect(tableWidget,&recordWidget::recordRun,this,&MainWindow::onRecordRun);
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

    this->ProjectNameDialogSetup();
    QTimer::singleShot(100,this,[=](){
        mainWidget->getView()->MustBeResized();
    });
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

    mainWidget->changeCablePage(index);

    if(index==currentIndex)
    {
        return;
    }
    else{
        if(cable!=nullptr)
        {
            delete cable;
            cable=nullptr;
        }
        switch (index) {
        case 0:
            break;
        case 1:
            break;
        case 2:
            cable=new HighSpeedCable;
            connect(cable,&Cable::loadInData,tableWidget,&recordWidget::insert);
            break;
        default:
            break;
        }
        connect(cable,&Cable::caculateDone,this,&MainWindow::dealWithResults);
        currentIndex=index;
    }
}

void MainWindow::onActionRun()
{
    if(cable==nullptr)
    {
        return;
    }
    if(currentIndex==2)
    {
        QString name;
        name=QFileDialog::getSaveFileName(this,"保存线缆S参数文件",".s4p","S_Parameters (*.s4p)");
        name=name.section(".s4p",0,0);
        cable->setName(name);
        HighSpeedCable * c=dynamic_cast<HighSpeedCable*>(cable);
        if(c!=nullptr)
        {
            c->setIsFixture(mainWidget->getFixtureCheckBox()->isChecked());
            c->setType(mainWidget->getHighSpeedType());
            if(mainWidget->getFixtureCheckBox()->isChecked())
            {
                if(mainWidget->getLineEditPath()->text().isNull()||mainWidget->getLineEditPath()->text().isEmpty())
                {
                 QMessageBox::warning(this,"错误提示","未输入夹具路径");
                 return;
                }
                c->setFixturePath(mainWidget->getLineEditPath()->text());
            }
        }


    }

    cable->setParameters(mainWidget->getInputParameters(currentIndex));
    cable->CaculateS_Parameters();

}

//void MainWindow::dealWithResults(QVector<QVector<double> >data, QVector<QString>name)
//{
//    if(result!=nullptr)
//    {
//        delete result;
//        result=nullptr;
//    }
//    qDebug()<<"计算完成";
//    result=new ChartWidget(data,name);
//    connect(contextcategory->categoryPage(0)->pannelByIndex(0)->actions()[0],&QAction::triggered,result,&ChartWidget::saveGraph);
//    connect(contextcategory->categoryPage(0)->pannelByIndex(0)->actions()[1],&QAction::triggered,result,&ChartWidget::saveExcel);
//    connect(contextcategory->categoryPage(0)->pannelByIndex(1)->actions()[0],&QAction::triggered,this,[=](){
//        result->changeX(true);
//    });
//    connect(contextcategory->categoryPage(0)->pannelByIndex(1)->actions()[1],&QAction::triggered,this,[=](){
//        result->changeX(false);
//    });
//    stackWidget->addWidget(result);
//    stackWidget->setCurrentIndex(2);
//    this->ribbonBar()->showContextCategory(contextcategory);
//    this->ribbonBar()->setCurrentIndex(3);
//}

void MainWindow::dealWithResults(QVector<QVector<double> > datas, QVector<QString> names, QString title)
{
    if(result==nullptr)return;

    result->addItem(datas,names,title);
    stackWidget->addWidget(result);
    stackWidget->setCurrentIndex(2);
    this->ribbonBar()->showContextCategory(contextcategory);
    this->ribbonBar()->setCurrentIndex(3);
}

void MainWindow::OnRibbonTabChanged(int index){
    switch (index) {
    case 0:stackWidget->setCurrentIndex(0);
        mainWidget->getView()->MustBeResized();
        break;
    case 1:stackWidget->setCurrentIndex(0);
        mainWidget->getView()->MustBeResized();
        break;
    case 2:stackWidget->setCurrentIndex(1);
        break;
    case 3:stackWidget->setCurrentIndex(2);
    default:
        break;
    }
}

void MainWindow::onRecordRun(int type, QStringList parameters)
{
    if(cable!=nullptr)
    {
        delete cable;
        cable=nullptr;
    }

    QVector<double>paramterList;
    switch (type) {
    case 2:cable=new HighSpeedCable();
        break;
    case 1:
        break;
    case 0:
        break;
    default:
        break;
    }
    connect(cable,&Cable::caculateDone,this,&MainWindow::dealWithResults);

    if(type==2)
    {
        QString name;
        bool isFixture;
        QString fixturePath;
        name="temp";
        cable->setName(name);
        HighSpeedCable * c=dynamic_cast<HighSpeedCable*>(cable);

        for(int i=0;i<parameters.size()-1;i++)
        {
            paramterList.push_back(parameters[i].toDouble());
        }
        if(parameters[parameters.size()-1].isNull()||parameters[parameters.size()-1].isEmpty())
        {
           isFixture=false;
        }
        else{
            isFixture=true;
            fixturePath=parameters[parameters.size()-1];
        }
        if(c!=nullptr)
        {
            c->setIsFixture(isFixture);
            if(isFixture)
            {
                c->setFixturePath(fixturePath);
            }
        }
    }
    cable->setParameters(paramterList);
    cable->CaculateS_Parameters();
    if(type==currentIndex)
    {
        return;
    }
    else{
        switch (currentIndex) {
        case 2:cable=new HighSpeedCable();
            break;
        case 1:
            break;
        case 0:
            break;
        default:
            break;
        }
        connect(cable,&Cable::caculateDone,this,&MainWindow::dealWithResults);
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



