#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <SARibbonMainWindow.h>
#include <SARibbonCategory.h>
#include <SARibbonBar.h>
#include <SARibbonQuickAccessBar.h>
#include <SARibbonStyleOption.h>
#include <SARibbonGallery.h>
#include <SARibbonLineEdit.h>
#include <occview.h>
#include <QLabel>
#include <QModelIndex>
#include <QTextEdit>
#include <QFontMetrics>
#include <SARibbonStyleOption.h>
#include <SARibbonElementManager.h>
#include <SARibbonStyleOption.h>
#include <QStackedWidget>
#include <environmentwidget.h>
#include <modelwidget.h>
#include <simulationwidget.h>
class MainWindow : public SARibbonMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
//    ~MainWindow();
signals:
    void leftWidgetshow_Hpm(int i,bool isShow);
    void leftWidgetshow_Envir(int i,bool isShow);
    void leftWidgetshow_Simu(int i,bool isShow);
    void UAVModelShow(QString path);


private:
    void pannelAddLargeAction(SARibbonPannel*panel,QString actionName,QString iconPath);
    void pannelAddLargeAction(SARibbonPannel*panel,QString actionName);
    void loadTheme();
    void loadTheme(QString path);

    SARibbonGalleryGroup * actionGalleryGroup;
    SARibbonGalleryGroup * ModelGroup1;
    SARibbonGalleryGroup * ModelGroup2;
    SARibbonGalleryGroup * ModelGroup3;
    QStackedWidget*MainWidget;
    EnvironmentWidget * envirWidget;
    ModelWidget * modelWidget;
    SimulationWidget * simulationWidget;
    bool isShowTwo=false;

private slots:
    void OnRibbonTabChanged(int index);
    void OnActionGalleryGroup(QAction*action);
    void onActionGalleryModelUAVGroup(QAction* action);
};

#endif // MAINWINDOW_H
