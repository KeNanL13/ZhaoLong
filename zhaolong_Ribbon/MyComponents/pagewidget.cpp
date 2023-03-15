#include "pagewidget.h"
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>
#include <QDebug>

PageWidget::PageWidget(QWidget *parent) : QWidget(parent)
{
    //Construct and set main layout
    stretchLayout =new QVBoxLayout(this);
    stretchLayout->setContentsMargins(0,0,0,0);
    stretchLayout->setSpacing(0);
    setLayout(stretchLayout);

    //Construct content widget
    contentWidget=new QWidget(this);
    stretchLayout->addWidget(contentWidget);
    contentWidget->show();

    //Add opacity effect to real content
    pageOpacityEffect=new QGraphicsOpacityEffect(contentWidget);
    pageOpacityEffect->setOpacity(0);
    contentWidget->setGraphicsEffect(pageOpacityEffect);

    //Move offstage
    move(originPagePosition+QPoint(0,150));
    hide();
}

void PageWidget::onStage()
{
    //Move up and fade in

    QParallelAnimationGroup * onStageAnimation=new QParallelAnimationGroup(this);
    QPropertyAnimation * moveAnimation=new QPropertyAnimation(this,"pos");
    QPropertyAnimation * fadeInAnimation=new QPropertyAnimation(pageOpacityEffect,"opacity");
    moveAnimation->setDuration(600);
    moveAnimation->setEasingCurve(QEasingCurve::OutExpo);
    moveAnimation->setStartValue(pos());
    moveAnimation->setEndValue(originPagePosition);

    fadeInAnimation->setDuration(500);
    fadeInAnimation->setEasingCurve(QEasingCurve::InQuad);
    fadeInAnimation->setStartValue(pageOpacityEffect->opacity());
    fadeInAnimation->setEndValue(0.999);
    onStageAnimation->addAnimation(moveAnimation);
    onStageAnimation->addAnimation(fadeInAnimation);
    onStageAnimation->start(QAbstractAnimation::DeleteWhenStopped);


    show();
}

void PageWidget::offStage()
{
    //Move up and fade in
    QParallelAnimationGroup * offStageAnimation=new QParallelAnimationGroup(this);
//    QPropertyAnimation * moveAnimation=new QPropertyAnimation(this,"pos");
    QPropertyAnimation * fadeInAnimation=new QPropertyAnimation(pageOpacityEffect,"opacity");
//    moveAnimation->setDuration(600);
//    moveAnimation->setEasingCurve(QEasingCurve::OutExpo);
//    moveAnimation->setStartValue(pos());
//    moveAnimation->setEndValue(originPagePosition);

    fadeInAnimation->setDuration(200);
    fadeInAnimation->setEasingCurve(QEasingCurve::InQuad);
    fadeInAnimation->setStartValue(pageOpacityEffect->opacity());
    fadeInAnimation->setEndValue(0.0);
//    onStageAnimation->addAnimation(moveAnimation);
    offStageAnimation->addAnimation(fadeInAnimation);
    offStageAnimation->start(QAbstractAnimation::DeleteWhenStopped);


    connect(offStageAnimation,&QParallelAnimationGroup::finished,[=](){
        move(originPagePosition+QPoint(0,150));
        hide();
    });
}
