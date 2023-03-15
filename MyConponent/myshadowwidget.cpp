#include "myshadowwidget.h"
#include <QRegularExpression>
#include <QDebug>

MyShadowWidget::MyShadowWidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    //Set the windowWidget
    stretchLayout=new QVBoxLayout(this);
    stretchLayout->setContentsMargins(30,30,30,30);
    windowWidget=new QWidget(this);
    windowWidget->setObjectName("windowWidget");
    windowWidget->setMouseTracking(true);
    stretchLayout->addWidget(windowWidget);
    windowWidget->show();
    setLayout(stretchLayout);

    //Set style sheet for window widget
    QString windowWidgetStyleSheet="QWidget#windowWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(cornerRadius)+"px;}";
    windowWidget->setStyleSheet(windowWidgetStyleSheet);
    //Set shadow
    windowShadow=new QGraphicsDropShadowEffect(windowWidget);
    windowShadow->setBlurRadius(30);
    windowShadow->setColor(QColor(0,0,0));
    windowShadow->setOffset(0,0);
    windowWidget->setGraphicsEffect(windowShadow);

    //
}

void MyShadowWidget::initialWidget()
{
    if(isInitial)
    {
        return;
    }
    QPainterPath path;
    path.addRoundedRect(windowWidget->rect(),cornerRadius-1,cornerRadius-1);
    QRegion region(path.toFillPolygon().toPolygon());
    windowWidget->setMask(region);

    windowBorder=new QWidget(this);
    windowBorder->setObjectName("windowBorder");
    QString windowBorderStyleSheet=
            "QWidget#windowBorder{background-color:#00FFFFFF;border:1.5px solid"+borderColor.name(QColor::HexArgb)+";border-radius:"+QString::number(cornerRadius)+"px;}";
    windowBorder->setStyleSheet(windowBorderStyleSheet);
    windowBorder->setAttribute(Qt::WA_TransparentForMouseEvents);
    windowBorder->move(windowWidget->pos()-QPoint(shift,shift));
    windowBorder->resize(windowWidget->size()+QSize(shift*2,shift*2));
    windowBorder->show();

    if(isBorderLower)
    {
        windowBorder->lower();

    }
//    windowWidget->raise();

    isInitial=true;
}

QWidget *MyShadowWidget::getMainWindow() const
{
    return windowWidget;
}

void MyShadowWidget::setShift(int shift)
{
    this->shift=shift;
    if(windowBorder!=nullptr){
        windowBorder->move(windowWidget->pos()-QPoint(shift,shift));
        windowBorder->resize(windowWidget->size()+QSize(shift*2,shift*2));
    }
}

void MyShadowWidget::setBorderWidth(float width)
{
    if(!windowBorder)
    {
        return;
    }
    QString styleSheet=windowBorder->styleSheet();
    qDebug()<<styleSheet;
    styleSheet.replace(QRegularExpression("border:\\d\\.\\d"),"border:"+QString::number(width));
    qDebug()<<styleSheet;
    windowBorder->setStyleSheet(styleSheet);
}

void MyShadowWidget::setLayoutContentMargins(int left, int top, int right, int bottom)
{
    stretchLayout->setContentsMargins(left,top,right,bottom);
}

void MyShadowWidget::setBorderWidgetLower(bool flag)
{
    isBorderLower=flag;
}



void MyShadowWidget::showEvent(QShowEvent *event)
{
    initialWidget();
    qDebug()<<this->width();
    qDebug()<<this->height();
}

void MyShadowWidget::resizeEvent(QResizeEvent *event)
{
    if(windowBorder!=nullptr){
        windowBorder->move(windowWidget->pos()-QPoint(shift,shift));
        windowBorder->resize(windowWidget->size()+QSize(shift*2,shift*2));
    }

    QPainterPath path;
    path.addRoundedRect(windowWidget->rect(),cornerRadius-1,cornerRadius-1);
    QRegion region(path.toFillPolygon().toPolygon());
    windowWidget->setMask(region);

}
