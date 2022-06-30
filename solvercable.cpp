#include "solvercable.h"

SolverCable::SolverCable(QObject *parent) : QObject(parent)
{

}

void SolverCable::System_SParametersFunction(QString path1, QString path2)
{
    cascade_cable_and_connector_functionInitialize();
    result.clear();
    mwArray X(1,2000,mxDOUBLE_CLASS);
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

    cascade_cable_and_connector_function(17,X,SDD1,SDD2,SDD3,SDD4,SCD1,SCD2,SCD3,SCD4,SDC1,SDC2,SDC3,SDC4,SCC1,SCC2,SCC3,SCC4,chr0,chr1);

//                cascade_cable_and_connector_function(2,X,SDD1,chr0,chr1);
    QVector<double> y[17];

        for(int i=1;i<=2000;i++)
        {
            y[0].push_back(X.Get(1,i));
            y[1].push_back(SDD1.Get(1,i));y[2].push_back(SDD2.Get(1,i));
            y[3].push_back(SDD3.Get(1,i));
            y[4].push_back(SDD4.Get(1,i));y[5].push_back(SCD1.Get(1,i));
            y[6].push_back(SCD2.Get(1,i));y[7].push_back(SCD3.Get(1,i));
            y[8].push_back(SCD4.Get(1,i));y[9].push_back(SDC1.Get(1,i));
            y[10].push_back(SDC2.Get(1,i));y[11].push_back(SDC3.Get(1,i));
            y[12].push_back(SDC4.Get(1,i));y[13].push_back(SCC1.Get(1,i));
            y[14].push_back(SCC2.Get(1,i));y[15].push_back(SCC3.Get(1,i));
            y[16].push_back(SCC4.Get(1,i));
        }
     for(auto x : y)
     {
         result.push_back(x);
     }
     QVector<QString> name;
     name<<"SDD11"<<"SDD12"<<"SDD21"<<"SDD22"
        <<"SDC11"<<"SDC12"<<"SDC21"<<"SDC22"
        <<"SCD11"<<"SCD12"<<"SCD21"<<"SCD22"
        <<"SCC11"<<"SCC12"<<"SCC21"<<"SCC22";
     emit caculateDone(result,name);
}

void SolverCable::ParallelCableFunction(double s, double H, double RW1, double RW2, double L, double E0, double THETAE, double THETAP, double PHIP)
{
    far_field_two_cables_functionInitialize();
    result.clear();
    mwArray X(1,500,mxDOUBLE_CLASS);
    mwArray ICM(1,500,mxDOUBLE_CLASS);
    mwArray IDM(1,500,mxDOUBLE_CLASS);
    mwArray S(1,1,mxDOUBLE_CLASS);

    S.SetData(&s,1);
    mwArray h(1,1,mxDOUBLE_CLASS);
    h.SetData(&H,1);
    mwArray rw1(1,1,mxDOUBLE_CLASS);
    rw1.SetData(&RW1,1);
    mwArray rw2(1,1,mxDOUBLE_CLASS);
    rw2.SetData(&RW2,1);
    mwArray l(1,1,mxDOUBLE_CLASS);
    l.SetData(&L,1);
    mwArray e0(1,1,mxDOUBLE_CLASS);
    e0.SetData(&E0,1);
    mwArray thetaE(1,1,mxDOUBLE_CLASS);
    thetaE.SetData(&THETAE,1);
    mwArray thetaP(1,1,mxDOUBLE_CLASS);
    thetaP.SetData(&THETAP,1);
    mwArray phiP(1,1,mxDOUBLE_CLASS);
    phiP.SetData(&PHIP,1);
    far_field_two_cables_function(3,X,ICM,IDM,S,h,rw1,rw2,l,e0,thetaE,thetaP,phiP);
//                cascade_cable_and_connector_function(2,X,SDD1,chr0,chr1);
    QVector<double> x;
    QVector<double> y1;
    QVector<double> y2;
    QVector<double> y[3];

    for(int i=1;i<=500;i++)
    {
        y[0].push_back(X.Get(1,i));
        y[1].push_back(ICM.Get(1,i));
        y[2].push_back(IDM.Get(1,i));
    }
    for(auto x : y)
    {
        result.push_back(x);
    }
    QVector<QString> name;
    name<<"ICM"<<"IDM";
    emit caculateDone(result,name);
}

void SolverCable::TWP_CableFunction(double lz, double P, double S, double H, double RW1, double RW2, double E0, double THETAE, double THETAP, double PHIP)
{
    TWP_far_filed_functionInitialize();
    result.clear();
    mwArray X(1,500,mxDOUBLE_CLASS);
    mwArray ICM(1,500,mxDOUBLE_CLASS);
    mwArray IDM(1,500,mxDOUBLE_CLASS);

    mwArray Lz(1,1,mxDOUBLE_CLASS);
    Lz.SetData(&lz,1);
    mwArray p(1,1,mxDOUBLE_CLASS);
    p.SetData(&P,1);
    mwArray s(1,1,mxDOUBLE_CLASS);
    s.SetData(&S,1);
    mwArray h(1,1,mxDOUBLE_CLASS);
    h.SetData(&H,1);
    mwArray rw1(1,1,mxDOUBLE_CLASS);
    rw1.SetData(&RW1,1);
    mwArray rw2(1,1,mxDOUBLE_CLASS);
    rw2.SetData(&RW2,1);
    mwArray e0(1,1,mxDOUBLE_CLASS);
    e0.SetData(&E0,1);
    mwArray thetaE(1,1,mxDOUBLE_CLASS);
    thetaE.SetData(&THETAE,1);
    mwArray thetaP(1,1,mxDOUBLE_CLASS);
    thetaP.SetData(&THETAP,1);
    mwArray phiP(1,1,mxDOUBLE_CLASS);
    phiP.SetData(&PHIP,1);
    TWP_far_filed_function(3,X,ICM,IDM,Lz,p,s,h,rw1,rw2,e0,thetaE,thetaP,phiP);
    QVector<double> y[3];
    for(int i=1;i<=500;i++)
    {
        y[0].push_back(X.Get(1,i));
        y[1].push_back(ICM.Get(1,i));
        y[2].push_back(IDM.Get(1,i));
    }
    for(auto x : y)
    {
        result.push_back(x);
    }
    QVector<QString> name;
    name<<"ICM"<<"IDM";
    emit caculateDone(result,name);
}

void SolverCable::HighSpeedFunction(double rw, double d, double rsh, double epsir, double tanloss, double tsh, double lz, double sigmaal, double sigmacu, double slot_d)
{
    zhaolong_cableFunctionInitialize();
    result.clear();
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

    QString name="cable_S_Parameters";
    QByteArray w0=name.toLatin1();
    char * char1=w0.data();
    zhaolong_cableFunction(17,SDD11,SDD12,SDD21,SDD22,SDC11,SDC12,SDC21,SDC22,
                           SCD11,SCD12,SCD21,SCD22,SCC11,SCC12,SCC21,SCC22,
                           X,RW,D,RSH,EPSIR,TANLOSS,TSH,LZ,SIGMAAL,SIGMACU,SLOT_D,char1);
    QVector<double> y[17];

    for(int i=1;i<=2000;i++)
    {
        y[0].push_back(X.Get(1,i));
        y[1].push_back(SDD11.Get(1,i));
        y[2].push_back(SDD12.Get(1,i));
        y[3].push_back(SDD21.Get(1,i));
        y[4].push_back(SDD22.Get(1,i));

        y[5].push_back(SDC11.Get(1,i));
        y[6].push_back(SDC12.Get(1,i));
        y[7].push_back(SDC21.Get(1,i));
        y[8].push_back(SDC22.Get(1,i));

        y[9].push_back(SCD11.Get(1,i));
        y[10].push_back(SCD12.Get(1,i));
        y[11].push_back(SCD21.Get(1,i));
        y[12].push_back(SCD22.Get(1,i));

        y[13].push_back(SCC11.Get(1,i));
        y[14].push_back(SCC12.Get(1,i));
        y[15].push_back(SCC21.Get(1,i));
        y[16].push_back(SCC22.Get(1,i));
    }
    for(auto x : y)
    {
        result.push_back(x);
    }
    QVector<QString> paraName;
    paraName<<"SDD11"<<"SDD12"<<"SDD21"<<"SDD22"
        <<"SDC11"<<"SDC12"<<"SDC21"<<"SDC22"
        <<"SCD11"<<"SCD12"<<"SCD21"<<"SCD22"
        <<"SCC11"<<"SCC12"<<"SCC21"<<"SCC22";
    emit caculateDone(result,paraName);
}
