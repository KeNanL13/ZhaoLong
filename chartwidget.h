#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QObject>
#include <QWidget>
#include <qcustomplot.h>
#include <QLayout>
#include <QMenu>
#include <QtMath>
class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    explicit ChartWidget(QVector<QVector<double>> data,QVector<QString>name,QWidget *parent = nullptr);
    QCustomPlot * plot;



signals:

public slots:
    void contextMenu(QPoint);
    void showGraph(int i);
    void removeGraph(int i);
    void mouseMoveSlot(QMouseEvent *event);
private:
    void createData();
    void createMenu();
    QCPItemTracer *tracer;
    QVector<QVector<double>> data;
    QVector<QString> name;
    QVector<int> checkList;
     QMap<int,QCPGraph*> graphMap;
    QMenu * menu;

    // QWidget interface
protected:

};

#endif // CHARTWIDGET_H
