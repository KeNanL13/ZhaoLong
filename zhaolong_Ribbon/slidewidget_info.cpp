#include "slidewidget_info.h"


SlideWidget_INFO::SlideWidget_INFO(int radius, QString name, QWidget *parent):SlidePage (radius,name,parent)
{

}

void SlideWidget_INFO::removeAll()
{
    RemoveContents(widgetList);
}

void SlideWidget_INFO::createPage(QStringList names,QStringList parameters,QStringList Metrics)
{
    //针对高速线单位做出改变
    if(parameters[0]=="高速线")
    {
        for(int i=2;i<8;i++)
        {
            parameters[i]=QString::number(parameters[i].toDouble()*1000.0);
        }
        for(int i=10;i<12;i++)
        {
            parameters[i]=QString::number(parameters[i].toDouble()*1e-9);
        }
    }
    if(names.size()!=parameters.size())
    {
        return;
    }
    widgetList.clear();
    QStack<LineEditWidget*>stack;


    for(int i=0;i<names.size();i++)
    {

        LineEditWidget * line=getLineEditWidget(names[i],parameters[i],Metrics[i]);
        stack.push(line);
        widgetList.append(line);
    }
//    AddContents(widgetList);

    while(!stack.isEmpty())
    {
        AddContent(stack.pop());
    }

}

LineEditWidget *SlideWidget_INFO::getLineEditWidget(QString label, QString value, QString Metrics)
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

    line->setText(value+"  "+Metrics);
    line->setEnable(false);
    line->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Maximum);
    QFontMetrics f(font);
    line->setMaximumHeight(f.height()+20);
    return line;
}
