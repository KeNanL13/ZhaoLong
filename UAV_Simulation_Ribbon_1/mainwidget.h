#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QMainWindow>
#include <SARibbonMainWindow.h>
#include <SARibbonCategory.h>
#include <SARibbonBar.h>
#include <SARibbonStyleOption.h>

class MainWidget : public SARibbonMainWindow
{
    Q_OBJECT
public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWIDGET_H
