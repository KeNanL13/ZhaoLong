#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <SARibbonMainWindow.h>
#include <SARibbonContextCategory.h>
#include <SARibbonGallery.h>
#include <SARibbonGalleryGroup.h>
#include <SARibbonPannel.h>
#include <QStackedWidget>
#include <contentwidget.h>
#include <highspeedcable.h>
#include <chartwidget.h>
#include <recordwidget.h>
#include <qtmaterialdialog.h>
#include <qtmaterialflatbutton.h>


#include <newcontentwidget.h>

#include <QThread>
#include <solver_cable.h>

class MainWindow : public SARibbonMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void loadTheme(QString path);
    void pannelAddLargeAction(SARibbonPannel *panel, QString actionName,QString iconPath);
    void onActionCableGroupTrigger(QAction*);
    void onActionRun();
//    void dealWithResults(QVector<QVector<double>>,QVector<QString>);
    void dealWithResults(QVector<QVector<double>>datas,QVector<QString>names,QString title);
    void OnRibbonTabChanged(int index);
    void onRecordRun(int type,QStringList parameters);
    void ProjectNameDialogSetup();
    void runningDialogSetup();
    bool isDirExist(QString);
    bool isFileExist(QString);
signals:
    void setProjectNameSig(QString ProJ_Name);

private:
    SARibbonGalleryGroup * cableGroup;
    QStackedWidget * stackWidget;
    NewContentWidget * mainWidget;
    recordWidget * tableWidget;
    SARibbonContextCategory*contextcategory;
    ChartWidget *result=nullptr;
    Cable* cable=nullptr;
    int currentIndex;
    //对话窗口
    QtMaterialDialog * dialog=nullptr;
    QtMaterialDialog * runningDialog=nullptr;

    //线缆线程与计算类
    QThread * solverThread=nullptr;
    Solver_Cable * solver_cable=nullptr;
    bool runningFlag=false;





signals:
    void highSpeedSignal(QVector<double> parameters, QVector<QString> path);
    void resizeFinish();


    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
