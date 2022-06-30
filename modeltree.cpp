#include "modeltree.h"

ModelTree::ModelTree()
{

}

QStandardItemModel *ModelTree::getParallelCableModel(QVector<QString> parameters)
{
    parameterList.clear();
    //输入树的顶层参数：
    QVector<QString> topInfo{"线缆参数","远场激励"};
    //输入树的次层参数：
    QVector<QString> information1{"线缆之间距离","线缆中心离地面的高度","线缆1半径","线缆2半径","线缆长度"};
    QVector<QString> information2{"电场强度","极化角度","入射方向thetaE","入射方向phiP"};
    int num1=lengthofVector(information1);
    int num2=lengthofVector(information2);
    int num3=lengthofVector(parameters);
    if(num3!=num1+num2)
    {
        qDebug()<<"输入参数的长度不相同";
        return nullptr;
    }

    QVector<QString> parameter1=divideVector(0,num1,parameters);
    QVector<QString> parameter2=divideVector(num1,num2,parameters);

    QVector<QVector<QString>> information;
    information.push_back(information1);
    information.push_back(information2);
    QVector<QVector<QString>> parameter;
    parameter.push_back(parameter1);
    parameter.push_back(parameter2);

    QStandardItemModel * modelP=new QStandardItemModel;
    modelP->setColumnCount(2);
    createTree(topInfo,modelP);
    int n=0;
    for(auto x : TopList)
    {

        createTree(information[n],parameter[n],x);
        n++;
    }
    TopList.clear();
    return modelP;
}

QStandardItemModel *ModelTree::getFixtureAndCableModel(QVector<QString> parameters)
{
    parameterList.clear();
    //输入树的顶层参数：
    QVector<QString> topInfo{"输入文件路径"};
    //输入树的次层参数：
    QVector<QString> information1{"夹具文件路径","线缆文件路径"};
    int num1=lengthofVector(information1);
    int num3=lengthofVector(parameters);
    if(num3!=num1)
    {
        qDebug()<<"输入参数的长度不相同";
        return nullptr;
    }

    QVector<QString> parameter1=divideVector(0,num1,parameters);

    QVector<QVector<QString>> information;
    information.push_back(information1);
    QVector<QVector<QString>> parameter;
    parameter.push_back(parameter1);

    QStandardItemModel * modelP=new QStandardItemModel;
    modelP->setColumnCount(2);
    createTree(topInfo,modelP);
    int n=0;
    for(auto x : TopList)
    {

        createTree(information[n],parameter[n],x);
        n++;
    }
    TopList.clear();
    return modelP;
}

QStandardItemModel *ModelTree::getTWPcableModel(QVector<QString> parameters)
{
    parameterList.clear();
    //输入树的顶层参数：
    QVector<QString> topInfo{"线缆参数","远场激励"};
    //输入树的次层参数：
    QVector<QString> information1{"线缆初始长度","线缆缠绕系数","线缆间距","线缆距地高度","线缆1半径","线缆2半径"};
    QVector<QString> information2{"电场强度","极化角度","入射方向thetaE","入射方向phiP"};
    int num1=lengthofVector(information1);
    int num2=lengthofVector(information2);
    int num3=lengthofVector(parameters);
    if(num3!=num1+num2)
    {
        qDebug()<<"输入参数的长度不相同";
        return nullptr;
    }

    QVector<QString> parameter1=divideVector(0,num1,parameters);
    QVector<QString> parameter2=divideVector(num1,num2,parameters);

    QVector<QVector<QString>> information;
    information.push_back(information1);
    information.push_back(information2);
    QVector<QVector<QString>> parameter;
    parameter.push_back(parameter1);
    parameter.push_back(parameter2);

    QStandardItemModel * modelP=new QStandardItemModel;
    modelP->setColumnCount(2);
    createTree(topInfo,modelP);
    int n=0;
    for(auto x : TopList)
    {

        createTree(information[n],parameter[n],x);
        n++;
    }
    TopList.clear();
    return modelP;
}

QStandardItemModel *ModelTree::getHighSpeedModel(QVector<QString> parameters)
{
    parameterList.clear();
    //输入树的顶层参数：
    QVector<QString> topInfo{"线缆参数"};
    //输入树的次层参数：
    QVector<QString> information1{"线缆半径","信号线距离","屏蔽层半径","介电膜相对介电常数","损耗正切","屏蔽层厚度",
                                 "线缆总长","屏蔽层电导率","线缆电导率","沟槽宽度"};
    int num1=lengthofVector(information1);
    int num3=lengthofVector(parameters);
    if(num3!=num1)
    {
        qDebug()<<"输入参数的长度不相同";
        qDebug()<<num3<<" "<<num1;
        return nullptr;
    }

    QVector<QString> parameter1=divideVector(0,num1,parameters);

    QVector<QVector<QString>> information;
    information.push_back(information1);
    QVector<QVector<QString>> parameter;
    parameter.push_back(parameter1);

    QStandardItemModel * modelP=new QStandardItemModel;
    modelP->setColumnCount(2);
    createTree(topInfo,modelP);
    int n=0;
    for(auto x : TopList)
    {

        createTree(information[n],parameter[n],x);
        n++;
    }
    TopList.clear();
    return modelP;
}

QStandardItemModel *ModelTree::getConstructModel(QVector<double> parameters)
{

    parameterList.clear();
    //输入树的顶层参数：
    QVector<QString> topInfo{"Definitions","Model"};
    //输入树的次层参数：
    QVector<QString> information1{"Variable","Media","Work planes"};
    QVector<QString> information11{"c0=1/sqrt(eps0*mu0)",QString("eps0=%1").arg(parameters[0]),
                                  QString("mu0=%1").arg(parameters[1]),QString("pi=%1").arg(parameters[2]),
                                  "zf0=sqrt(mu0/eps0)"};
    QVector<QString> information12{"Perfect electric conductor","Perfect magnetic conductor","Free space"};
    QVector<QString> information13{"Global XY [Default]","Global XZ","GLobal YZ"};
    QVector<QString> information2{"Geometry"};

    QVector<QVector<QString>> informationSecond;
    informationSecond.push_back(information1);
    informationSecond.push_back(information2);

    QVector<QVector<QString>> informationThird;
    informationThird.push_back(information11);
    informationThird.push_back(information12);
    informationThird.push_back(information13);

    QStandardItemModel * modelP=new QStandardItemModel;
    createTree(topInfo,modelP);
    int n=0;
    for(auto x : TopList)
    {

        createTree(informationSecond[n],x);
        n++;
    }
    TopList.clear();
    for(auto x : parameterList)
    {
        TopList<<x;
    }
    parameterList.clear();
        n=0;
    for(auto x : TopList)
    {

        if(n<3){
        createTree(informationThird[n],x);}
                n++;

    }

    parameterList.clear();
    TopList.clear();
    return modelP;
}

QStandardItemModel *ModelTree::getConfigurationModel(QVector<double> parameters)
{

    parameterList.clear();
    //输入树的顶层参数：
    QVector<QString> topInfo{"Definitions","Global","Configuration specific"};
    //输入树的次层参数：
    QVector<QString> information1{"Variable","Media","Work planes"};
    QVector<QString> information11{"c0=1/sqrt(eps0*mu0)",QString("eps0=%1").arg(parameters[0]),
                                  QString("mu0=%1").arg(parameters[1]),QString("pi=%1").arg(parameters[2]),
                                  "zf0=sqrt(mu0/eps0)"};
    QVector<QString> information12{"Perfect electric conductor","Perfect magnetic conductor","Free space"};
    QVector<QString> information13{"Global XY [Default]","Global XZ","GLobal YZ"};
    QVector<QString> information2{"Frequency [0 Hz]","Source"};
    QVector<QString> information3{"Requests"};

    QVector<QVector<QString>> informationSecond;
    informationSecond.push_back(information1);
    informationSecond.push_back(information2);
    informationSecond.push_back(information3);

    QVector<QVector<QString>> informationThird;
    informationThird.push_back(information11);
    informationThird.push_back(information12);
    informationThird.push_back(information13);
    QStandardItemModel * modelP=new QStandardItemModel;
    createTree(topInfo,modelP);
    int n=0;
    //顶层item赋予下一层
    for(auto x : TopList)
    {

        createTree(informationSecond[n],x);
        n++;
    }
    TopList.clear();
    //将下一层作为新的顶层
    for(auto x : parameterList)
    {
        TopList<<x;
    }
    parameterList.clear();
    n=0;
    //再为下一层赋予新的底层
    for(auto x : TopList)
    {

        if(n<3){
        createTree(informationThird[n],x);}
                n++;

    }

    parameterList.clear();
    TopList.clear();
    return modelP;
}

int ModelTree::lengthofVector(QVector<QString> vector)
{
    int n=0;
    for(auto x : vector)
    {
        n++;
    }
    return n;
}

QVector<QString> ModelTree::divideVector(int start, int length, QVector<QString> parameters)
{
    QVector<QString> parameter;
    for(int n=start;n<start+length;n++)
    {
        parameter.push_back(parameters[n]);
    }
    return parameter;
}

QVector<QStandardItem *> ModelTree::getParameterVector()
{
     QVector<QStandardItem*> parameter;
     for(auto x : parameterList)
     {
         parameter.push_back(x);
     }
     return parameter;
}

void ModelTree::createTree(QVector<QString> information, QVector<QString> Parameters, QStandardItem *itemTop)
{

    for(int m=0;m<lengthofVector(information);m++)
    {
        QStandardItem * item=new QStandardItem(information[m]);
        item->setEditable(false);
        QStandardItem * item1=new QStandardItem(Parameters[m]);
        QList<QStandardItem *>list;
        list<<item<<item1;
        parameterList<<item1;
        itemTop->appendRow(list);
    }
}

void ModelTree::createTree(QVector<QString> information, QStandardItemModel *model)
{
    for(int m =0;m<lengthofVector(information);m++)
    {
        QStandardItem * item=new QStandardItem(information[m]);
        model->appendRow(item);
        TopList<<item;
    }
}

void ModelTree::createTree(QVector<QString> information, QStandardItem *itemScond)
{
    for(int m =0;m<lengthofVector(information);m++)
    {
        QStandardItem * item=new QStandardItem(information[m]);
        itemScond->appendRow(item);
        parameterList<<item;
    }
}

