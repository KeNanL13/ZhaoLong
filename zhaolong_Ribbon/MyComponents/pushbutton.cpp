#include "pushbutton.h"
#include <QAnimationGroup>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include <QRegularExpression>
#include <QDebug>

PushButton::PushButton(QWidget *child, QWidget *parent)
    :QWidget(parent),childWidget(child)
{
    initializeUI();
}

void PushButton::initializeUI()
{
    generatorColor(defaultColorScheme);


    //Add margin for the child widget
    stretchLayout=new QHBoxLayout();
    stretchLayout->setContentsMargins(contentMargin);
    stretchLayout->setSpacing(0);
    stretchLayout->setAlignment(Qt::AlignCenter);
    setLayout(stretchLayout);
    if(childWidget)
    {
        stretchLayout->addWidget(childWidget);
        childWidget->show();
        childWidgetOriginalGeometry=childWidget->geometry();
    }
    //Initialize background widget
    backgroundWidget=new QWidget(this);
    backgroundWidget->resize(size());
    backgroundWidget->setObjectName("backgroundWidget");
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");

    backgroundWidget->lower();
    backgroundWidget->show();

    //Initialize indicator
    indicator=new QWidget(this);
    switch (indicatorPostion){
    case BtnPos_Left:
        indicator->resize(indicatorWidth,activatedLengthRatio*height());
        indicator->move(indicatorSpacing,(0.5-activatedLengthRatio/2.0)*height());
        break;
    case BtnPos_Right:
        indicator->resize(indicatorWidth,activatedLengthRatio*height());
        indicator->move(width()-indicatorSpacing-indicatorWidth,(0.5-activatedLengthRatio/2.0)*height());
        break;
    case BtnPos_Top:
        indicator->resize(activatedLengthRatio*width(),indicatorWidth);
        indicator->move((0.5-activatedLengthRatio/2.0)*width(),indicatorSpacing);
        break;
    case BtnPos_Bottom:
        indicator->resize(activatedLengthRatio*width(),indicatorWidth);
        indicator->move((0.5-activatedLengthRatio/2.0)*width(),height()-indicatorWidth-indicatorSpacing);
        break;
    }
    indicator->setObjectName("indicator");
    indicator->setStyleSheet("QWidget#indicator{background-color:"+indicatorColor.name(QColor::HexArgb)+";"
                             "border-radius:"+QString::number((float)indicatorWidth/2)+"px;}");
    indicatorEffect=new QGraphicsOpacityEffect(indicator);
    indicatorEffect->setOpacity(0);
    indicator->setGraphicsEffect(indicatorEffect);
    indicator->show();
    //Enable mouse tracking
    setMouseTracking(true);


}

void PushButton::generatorColor(QColor colorScheme)
{
    backgroundColor=colorScheme.lighter(120);
    backgroundColor.setAlpha(0);
    hoverColor=colorScheme.lighter(120);
    hoverColor.setAlpha(40);
    pressedColor=colorScheme.lighter(120);
    pressedColor.setAlpha(50);
    selectedColor=colorScheme.lighter(120);
    selectedColor.setAlpha(35);
    indicatorColor=colorScheme;
}

void PushButton::enterEvent(QEvent *event)
{
    if(!enabled)
    {
        return;
    }
    setCursor(Qt::PointingHandCursor);
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    QParallelAnimationGroup * indicatorEnterAnimation=new QParallelAnimationGroup(this);
    QPropertyAnimation* indicatorGrowLength = new QPropertyAnimation(indicator,"geometry",this);
    QPropertyAnimation * indicatorFadeIn=new QPropertyAnimation(indicatorEffect,"opacity",this);
    indicatorGrowLength->setDuration(150);
    indicatorGrowLength->setEasingCurve(QEasingCurve::OutQuad);
    indicatorFadeIn->setDuration(100);
    indicatorFadeIn->setEasingCurve(QEasingCurve::OutQuad);
    indicatorGrowLength->setStartValue(indicator->geometry());
    switch(indicatorPostion){
    case BtnPos_Left:
        indicatorGrowLength->setEndValue(QRect(
                                             indicatorSpacing,
                                             (0.5-hoveredLengthRadio/2)*height(),
                                             indicatorWidth,
                                             hoveredLengthRadio*height()
                                             ));
        break;
    case BtnPos_Right:
        indicatorGrowLength->setEndValue(QRect(
                                             width()-indicatorWidth-indicatorSpacing,
                                             (0.5-hoveredLengthRadio/2)*height(),
                                             indicatorWidth,
                                             hoveredLengthRadio*height()
                                             ));
        break;
    case BtnPos_Top:
        indicatorGrowLength->setEndValue(QRect(
                                             (0.5-hoveredLengthRadio/2)*width(),
                                              indicatorSpacing,
                                             hoveredLengthRadio*width(),
                                             indicatorWidth
                                             ));
        break;
    case BtnPos_Bottom:
        indicatorGrowLength->setEndValue(QRect(
                                             (0.5-hoveredLengthRadio/2)*width(),
                                             height()-indicatorWidth-indicatorSpacing,
                                             hoveredLengthRadio*width(),
                                             indicatorWidth
                                             ));
        break;
    }
    indicatorFadeIn->setStartValue(indicatorEffect->opacity());
    indicatorFadeIn->setEndValue(0.999);
    indicatorEnterAnimation->addAnimation(indicatorGrowLength);
    indicatorEnterAnimation->addAnimation(indicatorFadeIn);
    indicatorEnterAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    hovered=true;
    emit onHover();
}

void PushButton::leaveEvent(QEvent *event)
{
    if(!enabled)
    {
        return;
    }
    setCursor(Qt::ArrowCursor);

    if(selected)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+selectedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
    else{
         backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
    QParallelAnimationGroup * indicatorLeaveAnimation=new QParallelAnimationGroup(this);
    QPropertyAnimation * indicatorShrinkLength=new QPropertyAnimation(indicator,"geometry",this);
    QPropertyAnimation *indicatorFadeOut=new QPropertyAnimation(indicatorEffect,"opacity",this);
    indicatorShrinkLength->setDuration(150);
    indicatorShrinkLength->setEasingCurve(QEasingCurve::OutQuad);
    indicatorFadeOut->setDuration(100);
    indicatorFadeOut->setEasingCurve(QEasingCurve::OutQuad);
    indicatorShrinkLength->setStartValue(indicator->geometry());
    switch(indicatorPostion){
    case BtnPos_Left:
        indicatorShrinkLength->setEndValue(QRect(
                                             indicatorSpacing,
                                             (0.5-activatedLengthRatio/2)*height(),
                                             indicatorWidth,
                                             activatedLengthRatio*height()
                                             ));
        break;
    case BtnPos_Right:
        indicatorShrinkLength->setEndValue(QRect(
                                             width()-indicatorWidth-indicatorSpacing,
                                             (0.5-activatedLengthRatio/2)*height(),
                                             indicatorWidth,
                                             activatedLengthRatio*height()
                                             ));
        break;
    case BtnPos_Top:
        indicatorShrinkLength->setEndValue(QRect(
                                             (0.5-activatedLengthRatio/2)*width(),
                                              indicatorSpacing,
                                             activatedLengthRatio*width(),
                                             indicatorWidth
                                             ));
        break;
    case BtnPos_Bottom:
        indicatorShrinkLength->setEndValue(QRect(
                                             (0.5-activatedLengthRatio/2)*width(),
                                             height()-indicatorWidth-indicatorSpacing,
                                             activatedLengthRatio*width(),
                                             indicatorWidth
                                             ));
        break;
    }
    indicatorFadeOut->setStartValue(indicatorEffect->opacity());
    indicatorFadeOut->setEndValue(selected?0.999:0);
    indicatorLeaveAnimation->addAnimation(indicatorShrinkLength);
    indicatorLeaveAnimation->addAnimation(indicatorFadeOut);
    indicatorLeaveAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    pressed=false;
    hovered=false;
}

void PushButton::mousePressEvent(QMouseEvent *event)
{
    if(!enabled)
    {
        return;
    }
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    QPropertyAnimation * indicatorShrinkLength=new QPropertyAnimation(indicator,"geometry",this);
    indicatorShrinkLength->setDuration(100);
    indicatorShrinkLength->setEasingCurve(QEasingCurve::OutQuad);
    indicatorShrinkLength->setStartValue(indicator->geometry());
    switch(indicatorPostion){
    case BtnPos_Left:
        indicatorShrinkLength->setEndValue(QRect(
                                             indicatorSpacing,
                                             (0.5-pressedLengthRadio/2)*height(),
                                             indicatorWidth,
                                             hoveredLengthRadio*height()
                                             ));
        break;
    case BtnPos_Right:
        indicatorShrinkLength->setEndValue(QRect(
                                             width()-indicatorWidth-indicatorSpacing,
                                             (0.5-pressedLengthRadio/2)*height(),
                                             indicatorWidth,
                                             pressedLengthRadio*height()
                                             ));
        break;
    case BtnPos_Top:
        indicatorShrinkLength->setEndValue(QRect(
                                             (0.5-pressedLengthRadio/2)*width(),
                                              indicatorSpacing,
                                             pressedLengthRadio*width(),
                                             indicatorWidth
                                             ));
        break;
    case BtnPos_Bottom:
        indicatorShrinkLength->setEndValue(QRect(
                                             (0.5-pressedLengthRadio/2)*width(),
                                             height()-indicatorWidth-indicatorSpacing,
                                             pressedLengthRadio*width(),
                                             indicatorWidth
                                             ));
        break;
    }
    indicatorShrinkLength->start(QAbstractAnimation::DeleteWhenStopped);
    pressed=true;
    emit onPressed();
}

void PushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if(!enabled)
    {
        return;
    }
    qDebug()<<"Release ! : pressed="<<pressed;
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    QPropertyAnimation * indicatorGrowLength=new QPropertyAnimation(indicator,"geometry",this);
    indicatorGrowLength->setDuration(100);
    indicatorGrowLength->setEasingCurve(QEasingCurve::OutQuad);
    indicatorGrowLength->setStartValue(indicator->geometry());
    switch(indicatorPostion){
    case BtnPos_Left:
        indicatorGrowLength->setEndValue(QRect(
                                             indicatorSpacing,
                                             (0.5-hoveredLengthRadio/2)*height(),
                                             indicatorWidth,
                                             hoveredLengthRadio*height()
                                             ));
        break;
    case BtnPos_Right:
        indicatorGrowLength->setEndValue(QRect(
                                             width()-indicatorWidth-indicatorSpacing,
                                             (0.5-hoveredLengthRadio/2)*height(),
                                             indicatorWidth,
                                             hoveredLengthRadio*height()
                                             ));
        break;
    case BtnPos_Top:
        indicatorGrowLength->setEndValue(QRect(
                                             (0.5-hoveredLengthRadio/2)*width(),
                                              indicatorSpacing,
                                             hoveredLengthRadio*width(),
                                             indicatorWidth
                                             ));
        break;
    case BtnPos_Bottom:
        indicatorGrowLength->setEndValue(QRect(
                                             (0.5-hoveredLengthRadio/2)*width(),
                                             height()-indicatorWidth-indicatorSpacing,
                                             hoveredLengthRadio*width(),
                                             indicatorWidth
                                             ));
        break;
    }
    indicatorGrowLength->start(QAbstractAnimation::DeleteWhenStopped);
    if(pressed)
    {
        emit onClick();
    }
    pressed=false;
}

void PushButton::resizeEvent(QResizeEvent *event)
{
    backgroundWidget->setGeometry(0,0,width(),height());
    switch (indicatorPostion){
    case BtnPos_Left:
        if(pressed)
        {
            indicator->setGeometry(QRect(
                                       indicatorSpacing,
                                       (0.5-pressedLengthRadio/2)*height(),
                                       indicatorWidth,
                                       pressedLengthRadio*height()
                                       ));
        }else if(hovered){
            indicator->setGeometry(QRect(
                                       indicatorSpacing,
                                       (0.5-hoveredLengthRadio/2)*height(),
                                       indicatorWidth,
                                       hoveredLengthRadio*height()
                                       ));
        }else{
            indicator->setGeometry(QRect(
                                       indicatorSpacing,
                                       (0.5-activatedLengthRatio/2)*height(),
                                       indicatorWidth,
                                       hoveredLengthRadio*height()
                                       ));
        }
        break;
    case BtnPos_Right:
        if(pressed)
        {
            indicator->setGeometry(QRect(
                                       width()-indicatorWidth-indicatorSpacing,
                                       (0.5-pressedLengthRadio/2)*height(),
                                       indicatorWidth,
                                       pressedLengthRadio*height()
                                       ));
        }else if(hovered){
            indicator->setGeometry(QRect(
                                        width()-indicatorWidth-indicatorSpacing,
                                       (0.5-hoveredLengthRadio/2)*height(),
                                       indicatorWidth,
                                       hoveredLengthRadio*height()
                                       ));
        }else{
            indicator->setGeometry(QRect(
                                        width()-indicatorWidth-indicatorSpacing,
                                       (0.5-activatedLengthRatio/2)*height(),
                                       indicatorWidth,
                                       hoveredLengthRadio*height()
                                       ));
        }
        break;
    case BtnPos_Top:
        if(pressed)
        {
            indicator->setGeometry(QRect(
                                       (0.5-pressedLengthRadio/2)*width(),
                                       indicatorSpacing,
                                       pressedLengthRadio*width(),
                                       indicatorWidth
                                       ));
        }else if(hovered){
            indicator->setGeometry(QRect(
                                       (0.5-hoveredLengthRadio/2)*width(),
                                       indicatorSpacing,
                                       hoveredLengthRadio*width(),
                                       indicatorWidth
                                       ));
        }else{
            indicator->setGeometry(QRect(
                                       (0.5-activatedLengthRatio/2)*width(),
                                       indicatorSpacing,
                                       activatedLengthRatio*width(),
                                       indicatorWidth
                                       ));
        }
        break;
    case BtnPos_Bottom:
        if(pressed)
        {
            indicator->setGeometry(QRect(
                                       (0.5-pressedLengthRadio/2)*width(),
                                       height()-indicatorWidth-indicatorSpacing,
                                       pressedLengthRadio*width(),
                                       indicatorWidth
                                       ));
        }else if(hovered){
            indicator->setGeometry(QRect(
                                       (0.5-hoveredLengthRadio/2)*width(),
                                       height()-indicatorWidth-indicatorSpacing,
                                       hoveredLengthRadio*width(),
                                       indicatorWidth
                                       ));
        }else{
            indicator->setGeometry(QRect(
                                       (0.5-activatedLengthRatio/2)*width(),
                                       height()-indicatorWidth-indicatorSpacing,
                                       activatedLengthRatio*width(),
                                       indicatorWidth
                                       ));
        }
        break;
    }
}

void PushButton::select()
{
    if(pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }else if(hovered)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }else {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+selectedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }

    //First shrink then length the indicator,also fade in
    QSequentialAnimationGroup* indicatorSelectAnimation=new QSequentialAnimationGroup(this);
    QParallelAnimationGroup*indicatorShrinkAnimation=new QParallelAnimationGroup(this);
    QPropertyAnimation * indicatorFadeIn=new QPropertyAnimation(indicatorEffect,"opacity",this);
    QPropertyAnimation * indicatorShrinkLength=new QPropertyAnimation(indicator,"geometry",this);
    QPropertyAnimation * indicatorGrowLength=new QPropertyAnimation(indicator,"geometry",this);
    indicatorFadeIn->setDuration(100);
    indicatorFadeIn->setEasingCurve(QEasingCurve::OutQuad);
    indicatorShrinkLength->setDuration(100);
    indicatorShrinkLength->setEasingCurve(QEasingCurve::OutQuad);
    indicatorGrowLength->setDuration(100);
    indicatorGrowLength->setEasingCurve(QEasingCurve::OutQuad);
    indicatorFadeIn->setStartValue(indicatorEffect->opacity());
    indicatorFadeIn->setEndValue(0.999);
    indicatorShrinkLength->setStartValue(indicator->geometry());
    switch(indicatorPostion){
    case BtnPos_Left:
        indicatorShrinkLength->setEndValue(QRect(
                                                 indicatorSpacing,
                                                 (0.5-pressedLengthRadio/2)*height(),
                                                 indicatorWidth,
                                                 pressedLengthRadio*height()
                                                 ));
        indicatorGrowLength->setStartValue(QRect(
                                               indicatorSpacing,
                                               (0.5-pressedLengthRadio/2)*height(),
                                               indicatorWidth,
                                               pressedLengthRadio*height()
                                               ));
        indicatorGrowLength->setEndValue(QRect(
                                             indicatorSpacing,
                                             (0.5-activatedLengthRatio/2)*height(),
                                             indicatorWidth,
                                             activatedLengthRatio*height()
                                             ));
        break;
    case BtnPos_Right:
        indicatorShrinkLength->setEndValue(QRect(
                                                 width()-indicatorWidth-indicatorSpacing,
                                                 (0.5-pressedLengthRadio/2)*height(),
                                                 indicatorWidth,
                                                 pressedLengthRadio*height()
                                                 ));
        indicatorGrowLength->setStartValue(QRect(
                                               width()-indicatorWidth-indicatorSpacing,
                                               (0.5-pressedLengthRadio/2)*height(),
                                               indicatorWidth,
                                               pressedLengthRadio*height()
                                               ));
        indicatorGrowLength->setEndValue(QRect(
                                             width()-indicatorWidth-indicatorSpacing,
                                             (0.5-activatedLengthRatio/2)*height(),
                                             indicatorWidth,
                                             activatedLengthRatio*height()
                                             ));
        break;
    case BtnPos_Top:
        indicatorShrinkLength->setEndValue(QRect(
                                                 (0.5-pressedLengthRadio/2)*width(),
                                                 indicatorSpacing,
                                                 pressedLengthRadio*width(),
                                                 indicatorWidth
                                                 ));
        indicatorGrowLength->setStartValue(QRect(
                                               (0.5-pressedLengthRadio/2)*width(),
                                               indicatorSpacing,
                                               pressedLengthRadio*width(),
                                               indicatorWidth
                                               ));
        indicatorGrowLength->setEndValue(QRect(
                                             (0.5-activatedLengthRatio/2)*width(),
                                             indicatorSpacing,
                                             activatedLengthRatio*width(),
                                             indicatorWidth
                                             ));
        break;
    case BtnPos_Bottom:
        indicatorShrinkLength->setEndValue(QRect(
                                                 (0.5-pressedLengthRadio/2)*width(),
                                                 height()-indicator->height()-indicatorSpacing,
                                                 pressedLengthRadio*width(),
                                                 indicatorWidth
                                                 ));
        indicatorGrowLength->setStartValue(QRect(
                                               (0.5-pressedLengthRadio/2)*width(),
                                               height()-indicator->height()-indicatorSpacing,
                                               pressedLengthRadio*width(),
                                               indicatorWidth
                                               ));
        indicatorGrowLength->setEndValue(QRect(
                                             (0.5-activatedLengthRatio/2)*width(),
                                             height()-indicator->height()-indicatorSpacing,
                                             activatedLengthRatio*width(),
                                             indicatorWidth
                                             ));
        break;

    }
    indicatorShrinkAnimation->addAnimation(indicatorShrinkLength);
    indicatorShrinkAnimation->addAnimation(indicatorFadeIn);
    indicatorSelectAnimation->addAnimation(indicatorShrinkAnimation);
    indicatorSelectAnimation->addAnimation(indicatorGrowLength);
    indicatorSelectAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    selected=true;
}

void PushButton::deselect()
{
    if(!selected)
    {
        return;
    }
    if(pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }else if(hovered)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }else {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");

        //Cursor is currently not in the button,shrink and fade out the indicator
        QParallelAnimationGroup *indicatorDeselectAnimation=new QParallelAnimationGroup(this);
        QPropertyAnimation* indicatorFadeOut=new QPropertyAnimation(indicatorEffect,"opacity",this);
        QPropertyAnimation * indicatorShrinkLength=new QPropertyAnimation(indicator,"geometry",this);
        indicatorFadeOut->setDuration(100);
        indicatorFadeOut->setEasingCurve(QEasingCurve::OutQuad);
        indicatorShrinkLength->setDuration(100);
        indicatorShrinkLength->setEasingCurve(QEasingCurve::OutQuad);
        indicatorFadeOut->setStartValue(indicatorEffect->opacity());
        indicatorFadeOut->setEndValue(0);
        indicatorShrinkLength->setStartValue(indicator->geometry());
        switch(indicatorPostion)
        {
        case BtnPos_Left:
            indicatorShrinkLength->setEndValue(QRect(
                                                   indicatorSpacing,
                                                   (0.5-pressedLengthRadio/2)*height(),
                                                   indicatorWidth,
                                                   pressedLengthRadio*height()
                                                   ));
            break;
        case BtnPos_Right:
            indicatorShrinkLength->setEndValue(QRect(
                                                   width()-indicatorWidth-indicatorSpacing,
                                                   (0.5-pressedLengthRadio/2)*height(),
                                                   indicatorWidth,
                                                   pressedLengthRadio*height()
                                                   ));
            break;
        case BtnPos_Top:
            indicatorShrinkLength->setEndValue(QRect(
                                                   (0.5-pressedLengthRadio/2)*width(),
                                                   indicatorSpacing,
                                                   pressedLengthRadio*width(),
                                                   indicatorWidth
                                                   ));
            break;
        case BtnPos_Bottom:
            indicatorShrinkLength->setEndValue(QRect(
                                                   (0.5-pressedLengthRadio/2)*width(),
                                                   height()-indicatorWidth-indicatorSpacing,
                                                   pressedLengthRadio*width(),
                                                   indicatorWidth
                                                   ));
            break;
        }
        indicatorDeselectAnimation->addAnimation(indicatorFadeOut);
        indicatorDeselectAnimation->addAnimation(indicatorShrinkLength);
        indicatorDeselectAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    }
    selected=false;
}

void PushButton::setEnabled(bool enabled)
{
    if(enabled==this->enabled)
    {
        return;
    }
    if(enabled)
    {
        this->enabled=true;
        //Restore colors
        backgroundColor=restoredColor[0];
        hoverColor=restoredColor[1];
        pressedColor=restoredColor[2];
        selectedColor=restoredColor[3];
        indicatorColor=restoredColor[4];
        if(pressed)
        {
            backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");

        }
        else if(hovered)
        {
            backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");

        }
        else if(selected)
        {
            backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+selectedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");

        }
        else{
            backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");

        }
        indicator->setStyleSheet("QWidget#indicator{background-color:"+indicatorColor.name(QColor::HexArgb)+";"
                                 "border-radius:"+QString::number((float)indicatorWidth/2)+"px;}");
    }
    else{
        enabled=false;
        pressed=false;
        //Store color
        restoredColor[0]=backgroundColor;
        restoredColor[1]=hoverColor;
        restoredColor[2]=pressedColor;
        restoredColor[3]=selectedColor;
        restoredColor[4]=indicatorColor;
        //Set disable colors
        setColorScheme(QColor(200,200,200));
    }
}

void PushButton::setRadius(int radius)
{
    //get current style sheet
    QString styleSheet =backgroundWidget->styleSheet();
    styleSheet.remove(QRegularExpression("border-radius:\\d+px;"));
    styleSheet.append("border-radius:"+QString::number(radius)+"px;");

    //set new style sheet
    backgroundWidget->setStyleSheet(styleSheet);
    this->radius=radius;
}

void PushButton::setBackgroundColor(QColor color)
{
    backgroundColor=color;
    if(!selected &&!hovered && !pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
}

void PushButton::setHoverColor(QColor color)
{
    hoverColor=color;
    if(hovered&&!pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
}

void PushButton::setPressedColor(QColor color)
{
    pressedColor=color;
    if(pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
}

void PushButton::setSelectedColor(QColor color)
{
    selectedColor=color;
    if(selected&&!pressed &&!hovered)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+selectedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
}

void PushButton::setIndicatorColor(QColor color)
{
    indicatorColor=color;
    indicator->setStyleSheet("QWidget#indicator{background-color:" + indicatorColor.name(QColor::HexArgb) + ";"
               "border-radius:" + QString::number((float)indicatorWidth / 2) + "px;}");
}

void PushButton::setColorScheme(QColor primaryColor)
{
    generatorColor(primaryColor);
    if(pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
    else if(hovered)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
    else if(selected){
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+selectedColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
    else{
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(radius)+"px;}");
    }
    indicator->setStyleSheet("QWidget#indicator{background-color:" + indicatorColor.name(QColor::HexArgb) + ";"
                                                                                                            "border-radius:" + QString::number((float)indicatorWidth / 2) + "px;}");
}

QHBoxLayout *PushButton::getMainLayout() const
{
    return stretchLayout;
}

void PushButton::setAlignment(Qt::Alignment alignment)
{
    stretchLayout->setAlignment(alignment);
}

void PushButton::setMargin(QMargins margin)
{
    stretchLayout->setContentsMargins(margin);
}

void PushButton::setMargin(int left, int top, int right, int bottom)
{
    stretchLayout->setContentsMargins(left,top,right,bottom);
}

void PushButton::setIndicatorPosition(PushButton::BtnIndicatorPos position)
{
    indicatorPostion=position;
    float ratio;
    if(pressed)
    {
        ratio=pressedLengthRadio;
    }else if(hovered)
    {
        ratio=hoveredLengthRadio;
    }
    else {
        ratio=activatedLengthRatio;
    }

    switch(position){
    case BtnPos_Left:
        indicator->setGeometry(
                            indicatorSpacing,
                            (0.5 - ratio / 2) * height(),
                            indicatorWidth,
                            ratio * height()
                        );
        break;
    case BtnPos_Right:
        indicator->setGeometry(
                            width()-indicatorWidth-indicatorSpacing,
                            (0.5 - ratio / 2) * height(),
                            indicatorWidth,
                            ratio * height()
                        );
        break;
    case BtnPos_Top:
        indicator->setGeometry(
                            (0.5-ratio/2)*width(),
                            indicatorSpacing,
                            ratio*width(),
                            indicatorWidth
                        );
        break;
    case BtnPos_Bottom:
        indicator->setGeometry(
                            (0.5-ratio/2)*width(),
                            height()-indicatorSpacing-indicatorWidth,
                            ratio*width(),
                            indicatorWidth
                        );
        break;
    }
}

QWidget *PushButton::getChildWidget() const
{
    return childWidget;
}

void PushButton::setChildWidget(QWidget *widget)
{
    childWidget=widget;
    for(int i=0;i<stretchLayout->count();i++)
    {
        stretchLayout->removeItem(stretchLayout->itemAt(i));
    }
    if(childWidget!=nullptr)
    {
        stretchLayout->addWidget(childWidget);
//        childWidget->setObjectName("child");
//        childWidget->setStyleSheet("QWidget#child{background-color:ff00ff;}");
        childWidget->show();
        childWidgetOriginalGeometry=childWidget->geometry();
    }
}

bool PushButton::isSelected() const
{
    return selected;
}

