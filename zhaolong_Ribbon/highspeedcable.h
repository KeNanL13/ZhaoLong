#ifndef HIGHSPEEDCABLE_H
#define HIGHSPEEDCABLE_H


#include <cable.h>
#include <QString>
#include <QtMath>

class HighSpeedCable : public Cable
{
    Q_OBJECT
public:
    explicit HighSpeedCable(QObject *parent = nullptr);
    void CaculateS_Parameters();
    void CableModelBuiud();
    void setName(QString name);
    void setFixturePath(QString path);
    void setIsFixture(bool isFix);
    void setType(int type);
    QVector<QVector<double>> cascadeFixtureAndCable(QString path1,QString path2,QVector<double>x);
private:
    bool isFixture=false;
    QString fixturePath;
    QString s4PName;
    int m_type;

signals:

public slots:



};

#endif // HIGHSPEEDCABLE_H
