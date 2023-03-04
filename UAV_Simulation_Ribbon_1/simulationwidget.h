#ifndef SIMULATIONWIDGET_H
#define SIMULATIONWIDGET_H

#include <QWidget>
#include <QSplitter>

namespace Ui {
class SimulationWidget;
}

class SimulationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationWidget(QWidget *parent = nullptr);
    ~SimulationWidget();
    void leftWidgetAnimation(int index,bool isOut);

private:
    Ui::SimulationWidget *ui;
    QByteArray state;
    QSplitter * splitter;
    QSplitter * splitterRight;

};

#endif // SIMULATIONWIDGET_H
