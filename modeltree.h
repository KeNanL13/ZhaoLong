#ifndef MODELTREE_H
#define MODELTREE_H
#include <QString>
#include <QVector>
#include <QDebug>
#include <QStandardItem>
#include <QMouseEvent>

class ModelTree
{
public:
    ModelTree();
    QStandardItemModel * getParallelCableModel(QVector<QString> parameters);//获得平行线缆模型树
    QStandardItemModel * getFixtureAndCableModel(QVector<QString> parameters);//获得夹具和线缆合成模型树
    QStandardItemModel * getTWPcableModel(QVector<QString> parameters);//获得双绞线模型树
    QStandardItemModel * getHighSpeedModel(QVector<QString> parameters);//获得高速线模型树
    QStandardItemModel * getConstructModel(QVector<double> parameters);
    QStandardItemModel * getConfigurationModel(QVector<double> parameters);
    static int lengthofVector(QVector<QString> vector);//获得字符串向量的长度
    static QVector<QString> divideVector(int start,int length,QVector<QString> parameters);//按照初始位置，长度来划分一个字符串向量
    QVector<QStandardItem*> getParameterVector();//获得QStandardItem的指针向量。
private:
    void createTree(QVector<QString> information,QVector<QString> Parameters,QStandardItem* itemTop);//有两层的建立树
    void createTree(QVector<QString> information,QStandardItemModel* model);//一层的建立树
    void createTree(QVector<QString> information,QStandardItem * item);
    QList<QStandardItem *> TopList;//顶层Item List
    QList<QStandardItem *> parameterList;// 第二层Item List
};
#endif // MODELTREE_H
