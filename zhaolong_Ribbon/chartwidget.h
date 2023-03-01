#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QObject>
#include <QWidget>
#include <qcustomplot.h>
#include <QLayout>
#include <QMenu>
#include <QtMath>
#include <ExcelBase.h>
#include <QString>
#include <QTreeWidget>
#include <QTreeWidgetItem>

class ChartWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChartWidget(QWidget *parent = nullptr);
    explicit ChartWidget(QVector<QVector<double>> data,QVector<QString>name,QWidget *parent = nullptr);
    QCustomPlot * plot;

    void saveGraph();
    void addItem(QVector<QVector<double>>data,QVector<QString> name,QString title);
    void showGraph(QTreeWidgetItem*item );
    void removeGraph(QTreeWidgetItem*item);
    void removeItem();
    void readCSVFile(QString path);
    void setItemName(QString name);
    void setGraphColor(QColor color);
    bool isHasMainProject();
    bool isSelectItem();



signals:

public slots:
    void contextMenu(QPoint);
    void showGraph(int i);
    void removeGraph(int i);
    void mouseMoveSlot(QMouseEvent *event);
    void onAxisCliked(QCPAxis * axis,QCPAxis::SelectablePart part,QMouseEvent*event);
    void saveExcel();//9.12
    void changeX(bool );

    void onItemChanged(QTreeWidgetItem*item,int column);
    void onItemClicked(QTreeWidgetItem*item,int column);


private:
    void createData();
    void createMenu();
    QVector<QVector<double>> transverseVector(const QVector<QVector<double>>&data);
    int csvFileCount=0;
    QCPItemTracer *tracer;
    QVector<QVector<double>> data;
    QVector<QString> name;
    QVector<int> checkList;
     QMap<int,QCPGraph*> graphMap;
    QMenu * menu;
    bool isGhz=true;
    QSharedPointer<QCPAxisTickerLog> logTicker;
    QSharedPointer<QCPAxisTicker> Ticker;
    //TreeWidget
    QTreeWidget *treeWidget;
//    QVector<QString> titles;
//    QVector<QVector<QString>>paramaterNameLists;
    QMap<QTreeWidgetItem*,QVector<double>>MapItemToData;
    QMap<QTreeWidgetItem*,QVector<double>>MapTitleToX;
    QMap<QTreeWidgetItem*,QCPGraph*> graphMapItem;
    QTreeWidgetItem*currentTopItem=nullptr;
    QTreeWidgetItem*currentGraphItem=nullptr;
    QString IconPath=":/res/icon/Star.svg";

    // QWidget interface
protected:

};

#endif // CHARTWIDGET_H
