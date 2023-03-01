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
signals:
    void setProjectNameSig(QString ProJ_Name);

private:
    SARibbonGalleryGroup * cableGroup;
    QStackedWidget * stackWidget;
    contentWidget * mainWidget;
    recordWidget * tableWidget;
    SARibbonContextCategory*contextcategory;
    ChartWidget *result=nullptr;
    Cable* cable=nullptr;
    int currentIndex;
    QtMaterialDialog * dialog=nullptr;



signals:
    void resizeFinish();
};

#endif // MAINWINDOW_H
