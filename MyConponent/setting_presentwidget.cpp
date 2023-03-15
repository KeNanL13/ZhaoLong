#include "setting_presentwidget.h"


Setting_PresentWidget::Setting_PresentWidget(int radius, QString name, QWidget *parent):SlidePage (radius,name,parent)
{

}

void Setting_PresentWidget::createPage(int type,QString name,QVector<QString> names, QVector<QString> parameters, QVector<QString> Metrics)
{
    if(names.size()!=parameters.size())
    {
        return;
    }
    QStack<LineEditWidget*>stack;
    QString typeName;
    switch (type) {
    case 0:typeName="平行线";
        break;
    case 1:typeName="双绞线";
        break;
    case 2:typeName="高速线";
        break;
    default:
        break;
    }

    LineEditWidget*lineType=getLineEditWidget("线缆类型",typeName,"");
    stack.push(lineType);
    LineEditWidget*lineName=getLineEditWidget("实例名称",name,"");
    stack.push(lineName);


    for(int i=0;i<names.size();i++)
    {

        LineEditWidget * line=getLineEditWidget(names[i],parameters[i],Metrics[i]);
        stack.push(line);
    }

    while(!stack.isEmpty())
    {
        AddContent(stack.pop());
    }

}


LineEditWidget *Setting_PresentWidget::getLineEditWidget(QString label,QString value,QString Metrics)
{
    LineEditWidget * line=new LineEditWidget;
    QLabel *label1=new QLabel(label+":");

    label1->setFont(font);


    line->getMainLayout()->insertWidget(0,label1);
    line->getMainLayout()->insertSpacing(1,8);


    line->setBackgroundColor(QColor(0,0,0,0));
    line->setHoverColor(QColor(0,0,0,10));
    line->setPressedColor(QColor(0,0,0,20));


    line->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Preferred);
//    line->setFont(font);

    line->setText(value+Metrics);
    line->setEnable(false);
//    line->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Maximum);
//    QFontMetrics f(font);
//    line->setMaximumHeight(f.height()+20);
    return line;
}
