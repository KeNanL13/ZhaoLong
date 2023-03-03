#include "titlewidget.h"
#include "ui_titlewidget.h"

#include<QDesktopWidget>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

titleWidget::titleWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::titleWidget)
{
    ui->setupUi(this);

    this->setAttribute(Qt::WA_DeleteOnClose);
    setWindowFlags(Qt::FramelessWindowHint
                    | Qt::Tool
                    | Qt::WindowStaysOnTopHint
                    | Qt::WindowDoesNotAcceptFocus);
    move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    startUp();

}

titleWidget::titleWidget(QMainWindow *widget, QWidget *parent):
    widget(widget),
    QWidget (parent),
    ui(new Ui::titleWidget)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlag(Qt::FramelessWindowHint);
    move((QApplication::desktop()->width()-this->width())/2,(QApplication::desktop()->height()-this->height())/2);
    startUp();

}

titleWidget::~titleWidget()
{
    delete ui;
}

void titleWidget::startUp()
{
    QPropertyAnimation * ani=new QPropertyAnimation(this,"windowOpacity");
    ani->setDuration(3000);
    ani->setStartValue(1);
    ani->setKeyValueAt(0.5,1);
    ani->setEndValue(0);
    ani->setEasingCurve(QEasingCurve::Linear);
    ani->start(QAbstractAnimation::DeleteWhenStopped);
    connect(ani,&QPropertyAnimation::finished,this,[=](){

        widget->show();
        widget->setAttribute(Qt::WA_DeleteOnClose);
        this->close();
    });
}
