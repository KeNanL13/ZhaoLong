#include "mainwidget.h"
#include <SAFramelessHelper.h>

MainWidget::MainWidget(QWidget *parent) : SARibbonMainWindow(parent)
{
    SAFramelessHelper * helper=this->framelessHelper();
    helper->setWidgetResizable(true);
}
