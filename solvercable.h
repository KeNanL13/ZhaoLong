#ifndef SOLVERCABLE_H
#define SOLVERCABLE_H
#include <QDebug>
#include <QTabWidget>
#include <QtCharts>
#include <QObject>

#include <cascade_cable_and_connector_function.h>
#include <far_field_two_cables_function.h>
#include <TWP_far_filed_function.h>
#include <TBTWPfunction.h>
#include<zhaolong_cableFunction.h>


class SolverCable : public QObject
{
    Q_OBJECT
public:
        QVector<QVector<double>> result;
    explicit SolverCable(QObject *parent = nullptr);
    /**** matlab code ****/
    void System_SParametersFunction(QString path1,QString path2);//线缆和压具组成的系统S参数计算
    void ParallelCableFunction(double s,double H,double RW1,double RW2,
                                                   double L,double E0,double THETAE,double THETAP,double PHIP);//平行线线缆计算函数
    void TWP_CableFunction(double lz,double P,double S,double H,double RW1,double RW2,
                                               double E0,double THETAE,double THETAP,double PHIP);//双绞线线缆计算函数
    void HighSpeedFunction(double rw,double d,double rsh,double epsir ,double tanloss ,
                                               double tsh, double lz ,double sigmaal ,double sigmacu ,double slot_d);//高速线缆计算函数
    /********图画显示************/
     void ChartShow(QTabWidget* tabWidget,QVector<double> x,QVector<double>y);//函数作用：输入x和y，绘制出曲线，添加在tabwidget
     void ChartShow(QTabWidget* tabWidget,QVector<double> x,QVector<QVector<double>>y);//函数作用：输入x和多个y，绘制出曲线，添加在tabWidget中
signals:
     void caculateDone(QVector<QVector<double>>,QVector<QString>);

public slots:
};

#endif // SOLVERCABLE_H
