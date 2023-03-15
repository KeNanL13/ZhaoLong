#include "newcontentwidget.h"
#include <QPushButton>
#include <QPropertyAnimation>
#include <AIS_Shape.hxx>

#include <QGraphicsDropShadowEffect>

NewContentWidget::NewContentWidget(QWidget *parent) : QWidget(parent)
{
    //初始化OCCWidget
    occWidget=new OccView();
    occWidget->getView()->SetBgGradientColors(Quantity_NOC_LIGHTSKYBLUE, Quantity_NOC_LIGHTSKYBLUE4, Aspect_GFM_VER);
    //设置主窗口
    mainLayout=new QHBoxLayout();
    QVBoxLayout * occLayout=new QVBoxLayout;
    MyShadowWidget * shadowWidget=new MyShadowWidget(this);
    //shadowWidget setting
    occLayout->addWidget(occWidget);
    occLayout->setContentsMargins(10,10,10,10);
    shadowWidget->getMainWindow()->setLayout(occLayout);
    mainLayout->addWidget(shadowWidget);
    shadowWidget->setBorderWidgetLower(true);
    shadowWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    occWidget->setMinimumWidth(25);
    shadowWidget->setLayoutContentMargins(10,20,20,20);
    this->setLayout(mainLayout);

//    QGraphicsDropShadowEffect * dropShadow=new QGraphicsDropShadowEffect();
//    dropShadow->setBlurRadius(30);
//    this->setGraphicsEffect(dropShadow);


}

QVector<double> NewContentWidget::getInputParameter_Num()
{
    QVector<double> parameter;
    if(toolWidget!=nullptr &&toolWidget->getNumerInputCount()>0)
    {
        parameter=toolWidget->getInputNumber();
    }
    return parameter;
}

QVector<QString> NewContentWidget::getInputParameter_Text()
{
    QVector<QString> parameter;
    if(toolWidget!=nullptr  && toolWidget->getTextInputCount()>0)
    {
        parameter=toolWidget->getInputText();
    }
    return parameter;
}

void NewContentWidget::receiveInputMessage(QVector<QString> title,QVector<QString>value,QVector<QString>Metrics)
{
    emit transInfo(title,value,Metrics);
}

void NewContentWidget::sendInputMessage()
{
    if(toolWidget)
    {
        toolWidget->sendInputInformation();
    }
}

bool NewContentWidget::isInputComplete()
{
    if(toolWidget!=nullptr)
    {
        return toolWidget->isInputCompleted();
    }
}

void NewContentWidget::setProject(int i)
{
    switch (i) {
    case 0:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Front);
        occWidget->getView()->Update();
        break;
    case 1:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Left);
        occWidget->getView()->Update();
        break;
    case 2:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Right);
        occWidget->getView()->Update();
        break;
    case 3:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Top);
        occWidget->getView()->Update();
        break;
    case 4:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Bottom);
        occWidget->getView()->Update();
        break;
    case 5:occWidget->getView()->SetProj(V3d_TypeOfOrientation::V3d_TypeOfOrientation_Zup_Back);
        occWidget->getView()->Update();
        break;
    case 6:occWidget->getView()->FitAll();
        occWidget->getView()->Update();
        break;
    default:
        break;
    }
}


void NewContentWidget::showToolWidget(SettingWidget_Base::CableType type)
{
    if(toolWidget!=nullptr)
    {
        if(toolWidget->getType()!=type)
        {
            toolWidget->close();
            delete toolWidget;
            toolWidget=nullptr;
        }
    }
    if(toolWidget==nullptr)
    {
        switch (type) {
        case SettingWidget_Base::HighSpeedCable:toolWidget=new SettingWidget_HighSpeed();

            break;
        default:
            return;
            break;
        }
        toolWidget->setType(type);
        connect(toolWidget,&SettingWidget_Base::createShape,this,&NewContentWidget::displayShape);
        connect(toolWidget,&SettingWidget_Base::clearShape,this,&NewContentWidget::clearShape);
        connect(toolWidget,&SettingWidget_Base::transInputInfo,this,&NewContentWidget::receiveInputMessage);

        mainLayout->insertWidget(0,toolWidget);
        toolWidget->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);
        toolWidget->setLayoutContentMargins(20,20,10,20);
        opacity=new QGraphicsOpacityEffect (toolWidget);
        toolWidget->setGraphicsEffect(opacity);
        opacity->setOpacity(0.0);

    }

    QPropertyAnimation * opacityAnimation=new QPropertyAnimation(opacity,"opacity");
    opacityAnimation->setDuration(1000);
    opacityAnimation->setEasingCurve(QEasingCurve::Linear);
    opacityAnimation->setStartValue(opacity->opacity());
    opacityAnimation->setEndValue(0.99);
    opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    toolWidget->show();

}

void NewContentWidget::closeToolWidget()
{
    if(toolWidget==nullptr)
    {
        return;
    }
    QPropertyAnimation * opacityAnimation=new QPropertyAnimation(opacity,"opacity");
    opacityAnimation->setDuration(1000);
    opacityAnimation->setEasingCurve(QEasingCurve::Linear);
    opacityAnimation->setStartValue(opacity->opacity());
    opacityAnimation->setEndValue(0.0);
    opacityAnimation->start(QAbstractAnimation::DeleteWhenStopped);
    connect(opacityAnimation,&QPropertyAnimation::finished,[=](){
        toolWidget->hide();
    });
}

void NewContentWidget::occResize()
{
    if(occWidget!=nullptr)
    {
        occWidget->getView()->MustBeResized();
    }
}

void NewContentWidget::displayShape()
{
    if(toolWidget==nullptr)
    {
        return;
    }
    ShapeWithColorList list=toolWidget->getShape();
    occWidget->clearAll();

    for(auto x : list)
    {
        Handle(AIS_Shape) shape=new AIS_Shape(x.first);
        shape->SetColor(x.second);
        occWidget->getContext()->Display(shape,false);
    }
    occWidget->getView()->FitAll();
}

void NewContentWidget::clearShape()
{
    if(toolWidget==nullptr)
    {
        return;
    }
    occWidget->clearAll();
    occWidget->getView()->FitAll();
}

void NewContentWidget::showEvent(QShowEvent *event)
{
    occResize();
}
