#ifndef ENVIRONMENTWIDGET_H
#define ENVIRONMENTWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <occview.h>
#include <QVector3D>
#include <QTimer>
#include <QtMath>
#include <qcustomplot.h>
#include <QWidget>

#include <XCAFPrs_AISObject.hxx>
#include <AIS_PlaneTrihedron.hxx>
#include <Geom_Plane.hxx>
#include <AIS_Line.hxx>
#include <AIS_Trihedron.hxx>
#include <Geom_Direction.hxx>
#include <AIS_Axis.hxx>
#include <AIS_Point.hxx>
#include <AIS_Plane.hxx>
#include <Geom_Line.hxx>
#include <AIS_Shape.hxx>
#include <BRepBuilderAPI_MakeShape.hxx>
#include <AdaptorVec_AIS.h>
#include <BRepPrimAPI_MakeBox.hxx>
#include <BRepLib_MakeWire.hxx>
#include <Graphic3d_Camera.hxx>

namespace Ui {
class EnvironmentWidget;
}
enum angleState{Fixed,Linear};
class EnvironmentWidget : public QWidget
{
    Q_OBJECT

public:
    explicit EnvironmentWidget(QWidget *parent = nullptr);
    ~EnvironmentWidget();

    void leftWidgetAnimation(int index,bool isOut);
    void selectUAV();
    void selectHPM();
    void startTimer(int interval);
    void ModelTranslate(QVector3D angle,QVector3D position);
    void interTranslate(QVector3D position,double angleInci,double anglePolarization);
    void resetALL();
    void stopSimulation(bool isStop);
    void createNewPlot();
    void evaluationPlot();
    double caculateThreshold(double pluseWidth);
    double cacalatePower();
    double fuFunction(double theta,double alpha,double lamda,double length);
    OccView * getOccWidget();

signals:


private:
    Ui::EnvironmentWidget *ui;
    QSplitter*splitter;
    OccView * occWidget;
    QByteArray state;
    QCustomPlot * plotWidget[6];
    QCustomPlot * evaluationWidget;
    //test
    QVector<double>test;


    //无人机模型
    Handle(XCAFPrs_AISObject) model;
    //干扰源和向量
    Handle(AIS_Shape)inter;
    Handle(AdaptorVec_AIS)vecIncident;
    Handle(AdaptorVec_AIS)vecPori;
    //模拟飞行
    Handle(AIS_Shape)moveWire;
    QVector<gp_Pnt>points;
    BRepLib_MakeWire *wireMaker;
    QTimer * timer;
    int time=0;
    int deadTime=4;

    //可视变化参数
    QVector3D angle ,position,angleLinear,positionInter;
    double angleIncident,anglePolariziton;
    //数据需要参数
    double velocity,UAVGain,InterFrequency,interPower;
    double rain;
    //useless paremeters
    double interWidth;
private:
    void loadModel(QString path);
    void getData(int t,const QVector3D& angle);
    double FunctionFg(double theta);
    double cacualteRainParameter(double frequency,double thetaPath,double thetaPolarization,double rainStrength);



private:

};

#endif // ENVIRONMENTWIDGET_H
