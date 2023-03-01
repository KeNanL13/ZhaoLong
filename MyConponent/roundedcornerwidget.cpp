#include "roundedcornerwidget.h"
#include <QRegularExpression>
#include <QPainterPath>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QGraphicsDropShadowEffect>

RoundedCornerWidget::RoundedCornerWidget(QWidget *parent) : QWidget(parent)
{
    //Create main layout and main widget
    mainLayout=new QVBoxLayout(this);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    mainWidget=new QWidget(this);
    mainWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainLayout->addWidget(mainWidget);
    mainWidget->show();
    setLayout(mainLayout);
}

void RoundedCornerWidget::initializeWidgetUI()
{
    //Set up border widget
    borderWidget=new QWidget(this);
    borderWidget->setObjectName("borderWidget");
    QString borderWidgetStyleSheet=
            "QWidget#borderWidget{background-color:#00FFFFFF;border:2px solid"+borderColor.name(QColor::HexArgb)+";"
            "border-radius:"+QString::number(cornerRadius)+"px;}";
    borderWidget->setStyleSheet(borderWidgetStyleSheet);
    borderWidget->setAttribute(Qt::WA_TransparentForMouseEvents);
    borderWidget->move(0,0);
    borderWidget->resize(width(),height());
    borderWidget->show();
    borderWidget->lower();
//    borderWidget->hide();

    //Create a round cornered mask
    QPainterPath path;
//    QRect rect(50,50,mainWidget->width()-100,mainWidget->height()-100);
    path.addRoundedRect(this->rect(),cornerRadius,cornerRadius);

    QRegion region(path.toFillPolygon().toPolygon());


    mainWidget->setMask(region);



}

void RoundedCornerWidget::showEvent(QShowEvent *event)
{
    qDebug()<<"RoundedCornerWidget show Event";
    QWidget::showEvent(event);

    if(initialized){
        return;
    }

    //Initialize widget UI
    initializeWidgetUI();

    initialized=true;
    emit windowShowed();
}

void RoundedCornerWidget::resizeEvent(QResizeEvent *event)
{
    if(borderWidget!=nullptr)
    {
        borderWidget->move(0,0);
        borderWidget->resize(width(),height());

    }

    if(mainWidget!=nullptr)
    {
        QPainterPath path;
        path.addRoundedRect(mainWidget->rect(),cornerRadius,cornerRadius);
        QRegion region(path.toFillPolygon().toPolygon());
        mainWidget->setMask(region);

    }
}

void RoundedCornerWidget::setCornerRadius(int radius)
{
    cornerRadius=radius;
    //Modify the cornel radius in the current style sheet of the border widget
    if(borderWidget!=nullptr)
    {
        QString styleSheet=borderWidget->styleSheet();
        styleSheet.replace(QRegularExpression("border-radius:\\d+px;"),
                 QString("border-radius:%1px;").arg(cornerRadius));
        borderWidget->setStyleSheet(styleSheet);
    }

    //Reset the mask of the main widget
    QPainterPath path;
    path.addRoundedRect(mainWidget->rect(),cornerRadius,cornerRadius);
    QRegion region(path.toFillPolygon().toPolygon());
    mainWidget->setMask(region);
}

void RoundedCornerWidget::setBorderColor(QColor color)
{
    //Set Color
    borderColor=color;

    //Modify the border color in the current style sheet of the border widget
    if(borderWidget!=nullptr)
    {
        QString styleSheet=borderWidget->styleSheet();
        styleSheet.replace(QRegularExpression("border:2px solid #\\w+;"),
                           QString("border:2px solid %1;").arg(borderColor.name(QColor::HexArgb)));
        borderWidget->setStyleSheet(styleSheet);
    }

}

void RoundedCornerWidget::setBorderStyleSheet(QString styleSheet)
{
//   qDebug()<<(borderWidget==nullptr);
    if(borderWidget!=nullptr)
    {
        qDebug()<<1;
         borderWidget->setStyleSheet(styleSheet);
    }

}

QWidget *RoundedCornerWidget::getMainWidget() const
{
    return mainWidget;
}
