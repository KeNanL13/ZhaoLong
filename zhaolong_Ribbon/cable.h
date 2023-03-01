#ifndef CABLE_H
#define CABLE_H

#include <QObject>
#include <QVector>
#include <zhaolongFunction.h>
class Cable : public QObject
{
    Q_OBJECT
public:
    explicit Cable(QObject *parent = nullptr);
    ~Cable();
    virtual void CaculateS_Parameters()=0;
    virtual void CableModelBuiud()=0;
    virtual void setName(QString name)=0;
    QVector<double> getParameters(){
        return parameters;
    }
    void setParameters(QVector<double> para){
        parameters=para;
    }
    bool IsParametersComplete();
protected:
    QVector<double> parameters;
    QVector<QVector<double>>results;
    int m_size;

signals:
    void caculateDone(QVector<QVector<double>>,QVector<QString>,QString name);
    void loadInData(QString type,QVector<double>paramter,QString fixturePath);
public slots:
};

#endif // CABLE_H
