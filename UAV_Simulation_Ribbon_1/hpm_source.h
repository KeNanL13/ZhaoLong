#ifndef HPM_SOURCE_H
#define HPM_SOURCE_H
#include <QtCharts>
#include <QValueAxis>

class HPM_Source
{
public:
    HPM_Source(QChart* chart);
    void createBiExponetial(double t,double E,double a,double b);
    void createTriExponetial(QVector<QLineEdit*> input);
    void createGauss(double t,double a,double b,double theta);
    void createRect(double t,double t1,double T,double A);
    void createCombination(QVector<int>,QVector<QVector<double>>inputLists,double time);
    void createSinWave(double t,double A,double f);
    void createDefine(double t,double E,double up,double width,double down);

    QVector<double> getX(){
        return x;
    }
    QVector<double> getY(){
        return y;
    }



private:
    QVector<double> x;
    QVector<double> y;
    QChart * m_chart;
    QSplineSeries * series;

    QVector<double> caculatePluse(int type,QVector<double>inputList,QVector<double>x,double time);
};

#endif // HPM_SOURCE_H
