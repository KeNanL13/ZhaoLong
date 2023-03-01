#include "highspeedcable.h"
#include <QDebug>

HighSpeedCable::HighSpeedCable(QObject *parent) : Cable(parent)
{
    qDebug()<<"派生类的构造函数";
    m_size=12;
//    parameters.push_back(0.2075e-3);
//    parameters.push_back(1.42e-3);
//    parameters.push_back(0.71e-3);
//    parameters.push_back(2);
//    parameters.push_back(0.0005);
//    parameters.push_back(0.009e-3);
//    parameters.push_back(200e-3);
//    parameters.push_back(38160000);
//    parameters.push_back(58130000);
//    parameters.push_back(0.07e-3);
//    parameters.push_back(1e9);
//    parameters.push_back(4e10);
//    s4PName="test01";
}

void HighSpeedCable::CaculateS_Parameters()
{
    if(!this->IsParametersComplete())
    {
        return;
    }
    qDebug()<<"开始计算";
    results.clear();
    double rw=parameters[0];
    double d=parameters[1];
    double rsh=parameters[2];
    double epsir=parameters[3];
    double tanloss=parameters[4];
    double tsh=parameters[5];
    double lz=parameters[6];
    double sigmaal=parameters[7];
    double sigmacu=parameters[8];
    double slot_d=parameters[9];
    double f_min=parameters[10];
    double f_max=parameters[11];

    rsh=rsh*2;
    mwArray X(1,2000,mxDOUBLE_CLASS);
    mwArray SDD11(1,2000,mxDOUBLE_CLASS);
    mwArray SDD12(1,2000,mxDOUBLE_CLASS);
    mwArray SDD21(1,2000,mxDOUBLE_CLASS);
    mwArray SDD22(1,2000,mxDOUBLE_CLASS);

    mwArray SDC11(1,2000,mxDOUBLE_CLASS);
    mwArray SDC12(1,2000,mxDOUBLE_CLASS);
    mwArray SDC21(1,2000,mxDOUBLE_CLASS);
    mwArray SDC22(1,2000,mxDOUBLE_CLASS);

    mwArray SCD11(1,2000,mxDOUBLE_CLASS);
    mwArray SCD12(1,2000,mxDOUBLE_CLASS);
    mwArray SCD21(1,2000,mxDOUBLE_CLASS);
    mwArray SCD22(1,2000,mxDOUBLE_CLASS);

    mwArray SCC11(1,2000,mxDOUBLE_CLASS);
    mwArray SCC12(1,2000,mxDOUBLE_CLASS);
    mwArray SCC21(1,2000,mxDOUBLE_CLASS);
    mwArray SCC22(1,2000,mxDOUBLE_CLASS);

    mwArray RW(1,1,mxDOUBLE_CLASS);
    RW.SetData(&rw,1);
    mwArray D(1,1,mxDOUBLE_CLASS);
    D.SetData(&d,1);
    mwArray RSH(1,1,mxDOUBLE_CLASS);
    RSH.SetData(&rsh,1);
    mwArray EPSIR(1,1,mxDOUBLE_CLASS);
    EPSIR.SetData(&epsir,1);
    mwArray TANLOSS(1,1,mxDOUBLE_CLASS);
    TANLOSS.SetData(&tanloss,1);
    mwArray TSH(1,1,mxDOUBLE_CLASS);
    TSH.SetData(&tsh,1);
    mwArray LZ(1,1,mxDOUBLE_CLASS);
    LZ.SetData(&lz,1);
    mwArray SIGMAAL(1,1,mxDOUBLE_CLASS);
    SIGMAAL.SetData(&sigmaal,1);
    mwArray SIGMACU(1,1,mxDOUBLE_CLASS);
    SIGMACU.SetData(&sigmacu,1);
    mwArray SLOT_D(1,1,mxDOUBLE_CLASS);
    SLOT_D.SetData(&slot_d,1);
    mwArray Fmin(1,1,mxDOUBLE_CLASS);
    Fmin.SetData(&f_min,1);
    mwArray Fmax(1,1,mxDOUBLE_CLASS);
    Fmax.SetData(&f_max,1);
    mwArray type(1,1,mxINT32_CLASS);
    type.SetData(&m_type,1);

//    QString name="cable_S_Parameters";
    QByteArray w0=s4PName.toLatin1();
    char * char1=w0.data();
    qDebug()<<"test";
    zhaolong_cableFunction12_1(17,SDD11,SDD12,SDD21,SDD22,SDC11,SDC12,SDC21,SDC22,
                           SCD11,SCD12,SCD21,SCD22,SCC11,SCC12,SCC21,SCC22,
                           X,RW,D,RSH,EPSIR,TANLOSS,TSH,LZ,SIGMAAL,SIGMACU,SLOT_D,char1,Fmax,Fmin,type);
    qDebug()<<"test";
    QVector<QString> paraName;
    paraName<<"SDD11"<<"SDD12"<<"SDD21"<<"SDD22"
        <<"SDC11"<<"SDC12"<<"SDC21"<<"SDC22"
        <<"SCD11"<<"SCD12"<<"SCD21"<<"SCD22"
        <<"SCC11"<<"SCC12"<<"SCC21"<<"SCC22"<<"Zcm"<<"Zdm";
    if(isFixture)
    {
        results.clear();
        QVector<double> cascadeX;
        for(int i=1;i<=2000;i++)
        {
            cascadeX.push_back(X.Get(1,i));
        }
        results=cascadeFixtureAndCable(fixturePath,s4PName+".s4p",cascadeX);
        emit caculateDone(results,paraName,"高速线缆带夹具");

        emit loadInData("高速线",parameters,fixturePath);
        return;
    }

    QVector<double> y[19];

    double zdm=100;
    double zcm=25;
    for(int i=1;i<=2000;i++)
    {
        double sdd11=SDD11.Get(1,i);
        double scc11=SCC11.Get(1,i);
        y[0].push_back(X.Get(1,i));
        y[1].push_back(20*log10(SDD11.Get(1,i)));
        y[2].push_back(20*log10(SDD12.Get(1,i)));
        y[3].push_back(20*log10(SDD21.Get(1,i)));
        y[4].push_back(20*log10(SDD22.Get(1,i)));

        y[5].push_back(20*log10(SDC11.Get(1,i)));
        y[6].push_back(20*log10(SDC12.Get(1,i)));
        y[7].push_back(20*log10(SDC21.Get(1,i)));
        y[8].push_back(20*log10(SDC22.Get(1,i)));

        y[9].push_back(20*log10(SCD11.Get(1,i)));
        y[10].push_back(20*log10(SCD12.Get(1,i)));
        y[11].push_back(20*log10(SCD21.Get(1,i)));
        y[12].push_back(20*log10(SCD22.Get(1,i)));

        y[13].push_back(20*log10(SCC11.Get(1,i)));
        y[14].push_back(20*log10(SCC12.Get(1,i)));
        y[15].push_back(20*log10(SCC21.Get(1,i)));
        y[16].push_back(20*log10(SCC22.Get(1,i)));


        double Zc=(1+scc11)/(1-scc11)*zcm;
        double Zd=(1+sdd11)/(1-sdd11)*zdm;
        y[17].push_back(Zc);
        y[18].push_back(Zd);

    }
    for(auto x : y)
    {
        results.push_back(x);
    }


    qDebug()<<"计算结果";
    emit caculateDone(results,paraName,"高速线缆");
    emit loadInData("高速线",parameters,fixturePath);
}

void HighSpeedCable::CableModelBuiud()
{

}

void HighSpeedCable::setName(QString name)
{
    s4PName=name;
}

void HighSpeedCable::setFixturePath(QString path)
{
    this->fixturePath=path;
}

void HighSpeedCable::setIsFixture(bool isFix)
{
    this->isFixture=isFix;
}

void HighSpeedCable::setType(int type)
{
    m_type=type;
}

QVector<QVector<double> > HighSpeedCable::cascadeFixtureAndCable(QString path1, QString path2,QVector<double>x)
{
    QVector<QVector<double>>result;

    mwArray SDD1(1,2000,mxDOUBLE_CLASS);
    mwArray SDD2(1,2000,mxDOUBLE_CLASS);
    mwArray SDD3(1,2000,mxDOUBLE_CLASS);
    mwArray SDD4(1,2000,mxDOUBLE_CLASS);
    mwArray SDC1(1,2000,mxDOUBLE_CLASS);
    mwArray SDC2(1,2000,mxDOUBLE_CLASS);
    mwArray SDC3(1,2000,mxDOUBLE_CLASS);
    mwArray SDC4(1,2000,mxDOUBLE_CLASS);
    mwArray SCD1(1,2000,mxDOUBLE_CLASS);
    mwArray SCD2(1,2000,mxDOUBLE_CLASS);
    mwArray SCD3(1,2000,mxDOUBLE_CLASS);
    mwArray SCD4(1,2000,mxDOUBLE_CLASS);
    mwArray SCC1(1,2000,mxDOUBLE_CLASS);
    mwArray SCC2(1,2000,mxDOUBLE_CLASS);
    mwArray SCC3(1,2000,mxDOUBLE_CLASS);
    mwArray SCC4(1,2000,mxDOUBLE_CLASS);
    QByteArray ba0 = path1.toLatin1();
    QByteArray ba1 = path2.toLatin1();
    char* chr0 = ba0.data();
    char* chr1 = ba1.data();

    cascade_cable_and_connector_function12_1(16,SDD1,SDD2,SDD3,SDD4,SCD1,SCD2,SCD3,SCD4,SDC1,SDC2,SDC3,SDC4,SCC1,SCC2,SCC3,SCC4,chr0,chr1);

//                cascade_cable_and_connector_function(2,X,SDD1,chr0,chr1);
    QVector<double> y[19];
    double zdm=100;
    double zcm=25;
        for(int i=1;i<=2000;i++)
        {
            y[0].push_back(x[i-1]);
            y[1].push_back(20*log10(SDD1.Get(1,i)));
            y[2].push_back(20*log10(SDD2.Get(1,i)));
            y[3].push_back(20*log10(SDD3.Get(1,i)));
            y[4].push_back(20*log10(SDD4.Get(1,i)));
            y[5].push_back(20*log10(SCD1.Get(1,i)));
            y[6].push_back(20*log10(SCD2.Get(1,i)));
            y[7].push_back(20*log10(SCD3.Get(1,i)));
            y[8].push_back(20*log10(SCD4.Get(1,i)));
            y[9].push_back(20*log10(SDC1.Get(1,i)));
            y[10].push_back(20*log10(SDC2.Get(1,i)));
            y[11].push_back(20*log10(SDC3.Get(1,i)));
            y[12].push_back(20*log10(SDC4.Get(1,i)));
            y[13].push_back(20*log10(SCC1.Get(1,i)));
            y[14].push_back(20*log10(SCC2.Get(1,i)));
            y[15].push_back(20*log10(SCC3.Get(1,i)));
            y[16].push_back(20*log10(SCC4.Get(1,i)));
            double sdd11=SDD1.Get(1,i);
            double scc11=SCC1.Get(1,i);

            double Zc=(1+scc11)/(1-scc11)*zcm;
            double Zd=(1+sdd11)/(1-sdd11)*zdm;
            y[17].push_back(Zc);
            y[18].push_back(Zd);
        }
     for(auto x : y)
     {
         result.push_back(x);
     }
     return result;
}
