#ifndef SOLVER_CABLE_H
#define SOLVER_CABLE_H

#include <QObject>
#include <zhaolongFunction.h>
#include <settingwidget_base.h>


class Solver_Cable : public QObject
{
    Q_OBJECT
public:
    explicit Solver_Cable(QObject *parent = nullptr);
    ~Solver_Cable();
    void init();
    void solver_HighSpeedCable(QVector<double>parameters,QVector<QString>path);
private:
    QVector<QVector<double>> cascadeFixtureAndCable(QString path1,QString path2,QVector<double>x);
signals:
    void caculateDone(QVector<QVector<double>>data,QVector<QString>path,QString name);
    void loadInData(QVector<double>inputParamter,QVector<QString>,SettingWidget_Base::CableType,QString name);
    void transMessage(QString msg);
    void finished();

public slots:
};

#endif // SOLVER_CABLE_H
