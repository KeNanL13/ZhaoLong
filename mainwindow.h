#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSplitter>
#include <QLayout>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QtMath>
#include <QtCharts>
#include <QProgressBar>
#include <QTabWidget>
#include <QThread>
#include <QProgressBar>

#include <STEPControl_Reader.hxx>
#include <TopoDS_Shape.hxx>
#include <AIS_Shape.hxx>

#include <cableselectdialog.h>
#include <cascade_cable_and_connector_function.h>
#include <far_field_two_cables_function.h>
#include <TWP_far_filed_function.h>
#include <TBTWPfunction.h>
#include<zhaolong_cableFunction.h>
#include <occview.h>

#include <modeltree.h>
#include <solvercable.h>
#include <occread.h>
#include <chartwidget.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void windowInit();
    ~MainWindow();
    QThread * threadRun;
    QThread * threadRead;
    QProgressBar * progressBar;
signals:
    void runSystemS_parameters(QString path1, QString path2);
    void runParallel(double s, double H, double RW1, double RW2, double L, double E0, double THETAE, double THETAP, double PHIP);
    void runTWP(double lz, double P, double S, double H, double RW1, double RW2, double E0, double THETAE, double THETAP, double PHIP);
    void runHighSpped(double rw, double d, double rsh, double epsir, double tanloss, double tsh, double lz, double sigmaal, double sigmacu, double slot_d);
    void readStepSignal(QString);
private slots:
    void on_tBtnCables_clicked();//打开线缆模型选择对话框

    void cableTreeShow(enum CableSelectDialog::modelType model,QString stepModelPath);

    void closeTab(int i);//关闭tabwidget
    void updataTabWidget(QVector<QVector<double>>,QVector<QString>);//根据计算结果更新tabwidget
    void on_tBtnRun_clicked();//运行按钮
    void updateTree(QStandardItem*);

private:
    Ui::MainWindow *ui;
//    osgViewer::Viewer *viewer;
    CableSelectDialog * cableDialog;
    QVector<QString> m_Parameters;
    QVector<QStandardItem*> parameterVector;
    OccView * occWidget;
    //Home
    QMenu * menuImport;
    QAction* actCADFEKOModel;
    QAction* actOsgFile;
    QAction* actKBLFile;
    QAction* actGeometryI;
    QAction* actMeshI;

    QMenu* menuExport;
    QAction* actGeometryE;
    QAction* actMeshE;
    QAction* actMeshBoundary;

    QMenu* menuSchematic;
    QAction* actNetworkSchematic;

    QMenu* menuApplicationMacro;
    QAction* actMacroLibrary;
    QAction* actParameterSweep;
    QAction* actOptenniLab;
    //侧边栏
    QMenu* menuConfigs;
    QAction* actStdConfig;
    QAction* actMultiportS;
    QAction* actCharacteristicModes;

    QMenu* menuConstruction;
    QAction* actAddVariableCons;
    QAction* actAddPointCons;
    QAction* actMediaCons;
    QAction* actFieldDataCons;
    QAction* actAddWorkPlaneCons;
    QAction* actCableDefinitionCons;
    QAction* actPort;
    QAction* actMeshRefinement;
    QAction* actPlaneGround;
    QAction* actFiniteArrays;
    QAction* actOptimisation;

    QMenu* menuConfig1;
    QAction* actSolverSettings;
    QAction* actFreqPerConfig;
    QAction* actSrcPerConfig;
    QAction* actLoadsPerConfig;
    QAction* actPowerPerConfig;

    QMenu* menuConfig2;
    QAction* actAddVariableConfig;
    QAction* actAddPointConfig;
    QAction* actMediaConfig;
    QAction* actFieldDataConfig;
    QAction* actAddWorkPlaneConfig;
    QAction* actCableDefinitionConfig;
    QAction* actFrequency;
    QAction* actAddRequest;
    QAction* actSource;
    QAction* actAddLoad;
    QAction* actNetwork;
    QAction* actPower;

    // TreeView Item
    QStandardItemModel* configsModel;
    QStandardItem* configs1;
    double c0=1/sqrt(eps0*mu0);//真空中光速
    double eps0=8.85418781761e-12;//真空中绝对介电常数
    double mu0=pi*4e-7;//真空中绝对介电常数
    const double pi=3.14159265358979323846;//圆周率pi的值
    double zf0=sqrt(mu0/eps0);//zf0的取值
    QStandardItemModel * constructModel;//Construct Tree
    QStandardItemModel * configModel;// Configuration Tree
    QStandardItemModel * detailModel=nullptr;// Input or the detail Tree

    CableSelectDialog::modelType modelType=CableSelectDialog::None;//模型类型


    void loadStepModel(QString);//加载Step模型函数
    /********图画显示************/
    void ChartShow(QTabWidget *tabWidget,QVector<QVector<double>> data,QVector<QString>name);

};
#endif // MAINWINDOW_H
