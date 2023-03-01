#ifndef PARAMETERWIDGET_H
#define PARAMETERWIDGET_H

#include <QWidget>

namespace Ui {
class ParameterWidget;
}

class ParameterWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ParameterWidget(QWidget *parent = nullptr);
    ParameterWidget(int type,QStringList parameters,QWidget *parent = nullptr);
    ~ParameterWidget();

private:
    Ui::ParameterWidget *ui;
};

#endif // PARAMETERWIDGET_H
