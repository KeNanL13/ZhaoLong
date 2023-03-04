#include "hpm_source.h"

HPM_Source::HPM_Source(QChart* chart):m_chart(chart)
{

}

void HPM_Source::createBiExponetial(double t, double E, double a, double b)
{
    m_chart->removeAllSeries();
    x.clear();
    y.clear();
    series=new QSplineSeries;
    QVector<double> x;
    QVector<double> y;
    int precision=2000;
    double step=t/precision;
    for(int i=0;i<precision;i++)
    {
        series->append(step*i,E*(qExp(-a*step*i)-qExp(-b*step*i)));
        this->x.push_back(step*i);
        this->y.push_back(E*(qExp(-a*step*i)-qExp(-b*step*i)));
    }
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_chart->axisX()->setTitleText("时间/ns");
    m_chart->axisY()->setTitleText("电场强度/kV");
}

void HPM_Source::createTriExponetial(QVector<QLineEdit *> input)
{
    int num=0;
    for(auto x :input)
    {
        num++;
    }
    if(num!=13)
    {
        qDebug()<<num;
        qDebug()<<"数量不对";
        return;
    }
//     qDebug()<<num;
    m_chart->removeAllSeries();
    x.clear();
    y.clear();
    series=new QSplineSeries;
    double t=input[0]->text().toDouble();
    double a1=input[1]->text().toDouble();
    double b1=input[2]->text().toDouble();
    double t1=input[3]->text().toDouble();
    double w1=input[4]->text().toDouble();
    double a2=input[5]->text().toDouble();
    double b2=input[6]->text().toDouble();
    double t2=input[7]->text().toDouble();
    double w2=input[8]->text().toDouble();
    double a3=input[9]->text().toDouble();
    double b3=input[10]->text().toDouble();
    double t3=input[11]->text().toDouble();
    double w3=input[12]->text().toDouble();
    QVector<double> x;
    QVector<double> y;
    int precision=2000;
    double step=t/precision;
    for(int i=0;i<precision;i++)
    {

        double y0=a1*qExp(-2*pow((step*i-t1)/w1,2))/(b1*sqrt(M_PI_2))
                 +a2*qExp(-2*pow((step*i-t2)/w2,2))/(b2*sqrt(M_PI_2))
                 +a3*qExp(-2*pow((step*i-t3)/w3,2))/(b3*sqrt(M_PI_2));

        series->append(step*i,y0);
        this->x.push_back(step*i);
        this->y.push_back(y0);
    }
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_chart->axisX()->setTitleText("时间/ns");
    m_chart->axisY()->setTitleText("电场强度/kV");
}

void HPM_Source::createGauss(double t, double a, double b, double theta)
{
    m_chart->removeAllSeries();
    x.clear();
    y.clear();
    series=new QSplineSeries;
    QVector<double> x;
    QVector<double> y;
    int precision=2000;
    double step=t/precision;
    for(int i=0;i<precision;i++)
    {
        series->append(step*i,a*qExp(-pow((step*i-b),2)/(2*theta*theta)));
        this->x.push_back(step*i);
        this->y.push_back(a*qExp(-pow((step*i-b),2)/(2*theta*theta)));
    }
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_chart->axisX()->setTitleText("时间/ns");
    m_chart->axisY()->setTitleText("电场强度/kV");
}

void HPM_Source::createRect(double t, double t1, double T, double A)
{
    m_chart->removeAllSeries();
    x.clear();
    y.clear();
    series=new QSplineSeries;
    QVector<double> xR;
    QVector<double> yR;
    int precision=500;
    double step=T/precision;
    for(int i=0;i<precision;i++)
    {
        xR.push_back(step*i);
        if(step*i<=t1)
        {
            yR.push_back(A);
        }
        else{
            yR.push_back(0);
        }

    }

    int num=(int)t/T;
    QVector<double>x;
    QVector<double>y;
    for(int i=0;i<=num;i++)
    {
        for(int j=0;j<500;j++)
        {

            if(xR[j]+i*T<t)
            {
                series->append(xR[j]+i*T,yR[j]);
                this->x.push_back(xR[j]+i*T);
                this->y.push_back(yR[j]);
            }
            else {

                break;
            }
        }
    }
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();

    m_chart->axisX()->setTitleText("时间/ns");
    m_chart->axisY()->setTitleText("电场强度/kV");

}

void HPM_Source::createCombination(QVector<int>types, QVector<QVector<double> > inputLists, double time)
{
    m_chart->removeAllSeries();
    this->x.clear();
    y.clear();
    series=new QSplineSeries;
    if(types.size()!=inputLists.size()&&types.size()==0)
    {
        return;
    }
    int precision=500;
    QVector<double> x;
    double step=time/precision;
    for(int i=0;i<precision;i++)
    {
        double x0=i*step;
        x.push_back(x0);
    }
    QVector<QVector<double>>resultList;
    for(int i=0;i<types.size();i++)
    {
        QVector<double> result=this->caculatePluse(types[i],inputLists[i],x,time);
        qDebug()<<result.size();
        resultList.push_back(result);
    }

    int numI=types.size();
    int numJ=x.size();

    for(int j=0;j<numJ;j++)
    {
        double sum=1;
        for(int i=0;i<numI;i++)
        {
            sum*=resultList[i][j];
        }
        series->append(x[j],sum);
        this->x.push_back(x[j]);
        y.push_back(sum);
    }

    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_chart->axisX()->setTitleText("时间/ns");
    m_chart->axisY()->setTitleText("电场强度/kV");
}

void HPM_Source::createSinWave(double t,double A, double f)
{
    m_chart->removeAllSeries();
    this->x.clear();
    y.clear();
    series=new QSplineSeries;
    QVector<double> x;
    QVector<double> y;
    int precision=2000;
    double step=t/precision;
    for(int i=0;i<precision;i++)
    {
        series->append(step*i,A*sin(2*M_PI*f*step*i));
        this->x.append(step*i);
        this->y.append(A*sin(2*M_PI*f*step*i));
    }
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_chart->axisX()->setTitleText("时间/ns");
    m_chart->axisY()->setTitleText("电场强度/kV");
}

void HPM_Source::createDefine(double t,double E,double up,double width,double down)
{
    m_chart->removeAllSeries();
    this->x.clear();
    this->y.clear();
    series=new QSplineSeries;
    QVector<double> x;
    QVector<double> y;
    int precision=2000;
    double step=t/precision;
    for(int i=0;i<precision;i++)
    {
        if(step*i<=up)
        {
            series->append(step*i,E/up*step*i);
            this->x.append(step*i);
            this->y.append(E/up*step*i);

        }
        else if(step*i<=up+width)
        {
            series->append(step*i,E);
            this->x.append(step*i);
            this->y.append(E);
        }
        else if(step*i<=up+width+down)
        {
            series->append(step*i,-E/down*(step*i-(up+down+width)));
            this->x.append(step*i);
            this->y.append(-E/down*(step*i-(up+down+width)));
        }
        else {
            series->append(step*i,0);
            this->x.append(step*i);
            this->y.append(0);
        }
    }
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_chart->axisX()->setTitleText("时间/ns");
    m_chart->axisY()->setTitleText("电场强度/kV");
}

QVector<double> HPM_Source::caculatePluse(int type, QVector<double> inputList, QVector<double> x, double time)
{
    QVector<double> y;
    switch (type) {
    case 0://双指数
        if(inputList.size()!=3)
        { break;}
        for(double x0:x)
        {
        y.push_back(inputList[0]*(qExp(-inputList[1]*x0)-qExp(-inputList[2]*x0)));
        }
        break;
    case 1://三指数
        if(inputList.size()!=9)
        { break;}
        for(double x0:x)
        {
            y.push_back(inputList[0]*qExp(-2*pow((x0-inputList[1])/inputList[2],2))/(sqrt(M_PI_2))
                     +inputList[3]*qExp(-2*pow((x0-inputList[4])/inputList[5],2))/(sqrt(M_PI_2))
                     +inputList[6]*qExp(-2*pow((x0-inputList[7])/inputList[8],2))/(sqrt(M_PI_2)));
        }
        break;
    case 2://高斯
        if(inputList.size()!=3)
        { break;}
        for(double x0:x)
        {
            y.push_back(inputList[0]*qExp(-pow((x0-inputList[1]),2)/(2*inputList[2]*inputList[2])));
        }
        break;
    case 3://方波
        qDebug()<<x.size();
        if(inputList.size()!=3)
        {
            break;
        }
        for(double x0:x)
        {
            for(int i=0;i<=time/inputList[2];i++)
            {
                if(x0<=((i+1)*inputList[2])&&x0>=i*inputList[2])
                {
                    if(x0-i*inputList[2]<=inputList[1])
                    {
                        y.push_back(inputList[0]);
                    }
                    else
                    {
                        y.push_back(0);
                    }
                }

            }
        }
        break;
    case 4://正弦
        if(inputList.size()!=2)
        { break;}
        for(double x0:x)
        {
        y.push_back(inputList[0]*sin(2*M_PI*inputList[1]*x0));
        }
        break;
    case 5://自定义
//        if(step*i<=up)
//        {
//            series->append(step*i,E/up*step*i);
//        }
//        else if(step*i<=up+width)
//        {
//            series->append(step*i,E);
//        }
//        else if(step*i<=up+width+down)
//        {
//            series->append(step*i,-E/down*(step*i-(up+down+width)));
//        }
//        else {
//            series->append(step*i,0);
//        }

        if(inputList.size()!=4)
        { break;}
        for(double x0:x)
        {
            if(x0<=inputList[2])
            {
                y.push_back(inputList[0]/inputList[2]*x0);
            }
            else if(x0<=inputList[1]+inputList[2]){
                y.push_back(inputList[0]);
            }
            else if(x0<=inputList[1]+inputList[2]+inputList[3]){
                y.push_back(-inputList[0]/inputList[3]*(x0-(inputList[1]+inputList[2]+inputList[3])));
            }
            else {
                y.push_back(0);
            }
        }
        break;
    default:
        for(double x0:x)
        {
            y.push_back(0);
        }
        break;
    }
    return y;
}
