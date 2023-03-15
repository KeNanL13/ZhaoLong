#include "splash.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QBoxLayout>

#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>
#include <QMovie>



Splash::Splash(QWidget *parent) : MyShadowWidget (parent)
{

    setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);

    QVBoxLayout * layout=new QVBoxLayout();
    //    mainWidget=new QWidget;
    QLabel * pictureLabel=new QLabel();

    pictureLabel->setScaledContents(true);
    pictureLabel->setPixmap(QPixmap(":/res/picture/p1.jpg"));
//    QMovie *movie=new QMovie("C:/Users/liukenan/Desktop/car.gif");
//    pictureLabel->setMovie(movie);

    layout->addWidget(pictureLabel);
    layout->setContentsMargins(0,0,0,0);
    getMainWindow()->setLayout(layout);
//    pictureLabel->setFixedSize(800,600);
    opacity=new QGraphicsOpacityEffect();
    opacity->setOpacity(0.99);
    this->setGraphicsEffect(opacity);
    textLabel=new QLabel(this);

    textLabel->setFont(defaultFont);
    textLabel->setStyleSheet("color:#ffffff;");
    textLabel->hide();
//    movie->start();
}

void Splash::CloseSplash(QWidget *widget)
{
    QPropertyAnimation * fade=new QPropertyAnimation(opacity,"opacity");
    fade->setDuration(1500);
    fade->setEasingCurve(QEasingCurve::OutQuad);
    fade->setStartValue(opacity->opacity());
    fade->setEndValue(0.0);
    fade->start(QAbstractAnimation::DeleteWhenStopped);
    connect(fade,&QPropertyAnimation::finished,[=](){
        widget->show();
        widget->raise();
        this->close();
    });
}

void Splash::AddMessage(QString msg)
{
    textLabel->show();
    textLabel->setText(msg);
    QFontMetrics f(defaultFont);
    textLabel->setText(msg);
    int msgLength=f.width(msg);

    textLabel->move(this->width()/2-msgLength/2,this->height()*0.8);
}

void Splash::setNextWidget(QWidget *widget)
{
    nextWidget=widget;

}



void Splash::showEvent(QShowEvent *event)
{
   MyShadowWidget::showEvent(event);
   resize(800,600);
   int width=QApplication::desktop()->rect().width();
   int height=QApplication::desktop()->rect().height();

   move((width-this->width())/2,(height-this->height())/2);
   qDebug()<<this->width();
   qDebug()<<this->height();

}

