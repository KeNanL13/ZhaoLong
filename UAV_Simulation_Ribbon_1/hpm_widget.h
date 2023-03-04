#ifndef HPM_WIDGET_H
#define HPM_WIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QtCharts>
#include <QSplineSeries>
#include <hpm_source.h>

namespace Ui {
class HPM_Widget;
}

class HPM_Widget : public QWidget
{
    Q_OBJECT

public:
    explicit HPM_Widget(QLineEdit*time,QWidget *parent = nullptr);
    ~HPM_Widget();

    void leftWidgetAnimation(int index,bool isOut);
    void setTimeLine(QLineEdit*);
    void exportData();
    QChart* getChart();

private:
    Ui::HPM_Widget *ui;
    QSplitter * splitter;
    QChart * chart;
    HPM_Source *hpmSource;
    QByteArray state;
    void setChart(int i);
    QVector<QLineEdit*> list;
    bool isFitAll(QVector<QLineEdit*>inputList);
    bool isFitAll(QVector<QVector<QLineEdit*>>);
    int combinationNum=1;
    QList<QWidget*>widgetList;
    QVector<QVector<QLineEdit*>>combinationInputLists;
    QVector<int> types;
    QLineEdit* m_TimeLine;
    void CombinationInputEditChange(const QString &string);
};

#endif // HPM_WIDGET_H
