#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <pushbutton.h>
#include <pagewidget.h>

#include <lineeditwidget.h>
#include <slider.h>
#include <sidebar.h>
#include <QLabel>
#include <QSplitter>
#include <QLinearGradient>
#include <QGradientStops>
#include <framelesswidget.h>

#include <qtmaterialtextfield.h>
#include <qtmaterialscrollbar.h>
#include <QScrollArea>

#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QGraphicsOpacityEffect>



#include <QComboBox>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    resize(800,600);
    setMouseTracking(true);
//    QVBoxLayout * layout=new QVBoxLayout(this);
//    this->setLayout(layout);
//    this->setBackgroundRole(QPalette::ColorRole::Highlight);
    this->setObjectName("main");
//    this->setStyleSheet("QMainWindow#main{"
//                        "background-color:white;"
//                        "}");
    QWidget * mainWidget=new QWidget(this);
    setCentralWidget(mainWidget);
    QHBoxLayout * mainLayout=new QHBoxLayout;
    mainWidget->setLayout(mainLayout);


//    FrameLessWidget * widget1=new FrameLessWidget(15,0);
////    QWidget *widget=new QWidget;
//    QVBoxLayout* leftLayout=new QVBoxLayout;
//    leftLayout->addWidget(new QLabel("label1"));
//    leftLayout->addWidget(new QLabel("label2"));
//    leftLayout->addWidget(new QLabel("label3"));
////    widget1->setBorderColor(QColor(255,15,123));
////    widget1->getMainWidget()->setLayout(leftLayout);
//    widget1->getWindowWidget()->setLayout(leftLayout);
////    widget->setLayout(leftLayout);

//     widget2=new RoundedCornerWidget();
////    QWidget * widget2=new QWidget();
//    QVBoxLayout* rightLayout=new QVBoxLayout;
//    view=new OccView();
//    view->getView()->SetBgGradientColors(Quantity_NOC_SKYBLUE,Quantity_NOC_SKYBLUE4,Aspect_GFM_VER);
////    view->getView()->SetBackgroundColor(Quantity_Color(62.0/256.0,158.0/256.0,212.0/256.0,Quantity_TypeOfColor::Quantity_TOC_RGB));
//    rightLayout->addWidget(view);
//    rightLayout->setContentsMargins(0,0,0,0);
////    widget2->getMainWidget()->setLayout(rightLayout);


////    widget2->setBorderColor(QColor()
////    widget2->setBorderColor(QColor(62,158,212));
////    widget2->setLayout(rightLayout);
//    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
//    connect(widget2,&RoundedCornerWidget::windowShowed,[=](){
//        qDebug()<< "after windowShow";
//        QString styleSheet=
//                "QWidget#borderWidget{background-color:#00FFFFFF;border:2px solid qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(62, 158, 211, 255), stop:1 rgba(17, 41, 66, 255)) "
//                "border-radius:15 px;}";
//        widget2->setBorderStyleSheet(styleSheet);
//    });

//    QGraphicsDropShadowEffect * shadowEffect=new QGraphicsDropShadowEffect();
//    shadowEffect->setColor(QColor(0,0,0));
//    shadowEffect->setOffset(0,0);
//    shadowEffect->setBlurRadius(30);
//    widget2->getMainWidget()->setGraphicsEffect(shadowEffect);

//    FrameLessWidget * widget3= new FrameLessWidget(15,0);
//    widget3->getWindowWidget()->setLayout(rightLayout);

//    mainLayout->addWidget(widget1);
//    mainLayout->addSpacing(8);
//    mainLayout->addWidget(widget3);
//    mainLayout->setSpacing(20);


    shadowWidgetLeft=new MyShadowWidget();
    QVBoxLayout * leftLayout=new QVBoxLayout;
    QtMaterialTextField * textLine1=new QtMaterialTextField;
    textLine1->setLabel("线缆半径(mm)");

    textLine1->setMaximumWidth(200);
    textLine1->setMaximumHeight(50);
    QtMaterialTextField * textLine2=new QtMaterialTextField;
    textLine2->setMaximumWidth(200);
    textLine2->setLabel("线缆长度(mm)");
    QtMaterialTextField * textLine3=new QtMaterialTextField;
    textLine3->setMaximumWidth(200);
    textLine3->setLabel("材料参数(mm)");
    QtMaterialTextField * textLine4=new QtMaterialTextField;
    textLine4->setLabel("text");
    textLine4->setMaximumWidth(200);
    QtMaterialTextField * textLine5=new QtMaterialTextField;
    textLine5->setLabel("1");

    textLine5->setMaximumWidth(200);
    QtMaterialTextField * textLine6=new QtMaterialTextField;
    textLine6->setLabel("2");

    textLine6->setMaximumWidth(200);
    QtMaterialTextField * textLine7=new QtMaterialTextField;
    textLine7->setLabel("3");

    textLine7->setMaximumWidth(200);
    QtMaterialTextField * textLine8=new QtMaterialTextField;
    textLine8->setLabel("4");

    textLine8->setMaximumWidth(200);
    QtMaterialTextField * textLine9=new QtMaterialTextField;
    textLine9->setLabel("5");

    textLine9->setMaximumWidth(200);

    textLine8->setMaximumWidth(200);
    QtMaterialTextField * textLine10=new QtMaterialTextField;
    textLine10->setLabel("6");

    textLine10->setMaximumWidth(200);

    textLine10->setMaximumWidth(200);
    QtMaterialTextField * textLine11=new QtMaterialTextField;
    textLine11->setLabel("7");

    textLine11->setMaximumWidth(200);
    leftLayout->addWidget(textLine1);
    leftLayout->addWidget(textLine2);
    leftLayout->addWidget(textLine3);
    leftLayout->addWidget(textLine4);
    leftLayout->addWidget(textLine5);
    leftLayout->addWidget(textLine6);
    leftLayout->addWidget(textLine7);
    leftLayout->addWidget(textLine8);
    leftLayout->addWidget(textLine9);
    leftLayout->addWidget(textLine10);
    leftLayout->addWidget(textLine11);
//    leftLayout->addStretch(1);
    leftLayout->setSpacing(10);

//    shadowWidgetLeft->getMainWindow()->setLayout(leftLayout);
    QScrollArea * scrollArea=new QScrollArea();
    QtMaterialScrollBar * Hor_Scorll=new QtMaterialScrollBar();
    QtMaterialScrollBar * Ver_Scorll=new QtMaterialScrollBar();
    Hor_Scorll->setBackgroundColor(QColor(211,211,211));
    Hor_Scorll->setCanvasColor(QColor(255,255,255));
    Hor_Scorll->setHideOnMouseOut(true);
    Ver_Scorll->setHideOnMouseOut(false);

    Ver_Scorll->setBackgroundColor(QColor(255,255,255));
    Hor_Scorll->setSliderPosition(Qt::Horizontal);
    QWidget * scrollContentWidget=new QWidget();
    scrollContentWidget->setObjectName("scrollContentWidget");
    scrollContentWidget->setStyleSheet("QWidget#scrollContentWidget{background-color : #ffffff;}");
    scrollContentWidget->setLayout(leftLayout);
    scrollArea->setWidget(scrollContentWidget);
    scrollArea->setVerticalScrollBar(Ver_Scorll);
    scrollArea->setHorizontalScrollBar(Hor_Scorll);
    QVBoxLayout * scrollLayout=new QVBoxLayout;
    scrollLayout->addWidget(scrollArea);
    scrollLayout->setContentsMargins(0,0,0,0);
    scrollArea->setStyleSheet("QScrollArea{background-color:#ffffff;}");


    shadowWidgetLeft->getMainWindow()->setLayout(scrollLayout);
    shadowWidgetRight=new MyShadowWidget(this);
    view=new OccView;
    QVBoxLayout * occLayout=new QVBoxLayout;
    occLayout->setContentsMargins(10,10,10,10);
    occLayout->addWidget(view);
    shadowWidgetRight->getMainWindow()->setLayout(occLayout);
//    view->raise();
    shadowWidgetRight->setLayoutContentMargins(15,30,30,30);
    shadowWidgetLeft->setLayoutContentMargins(30,30,15,30);
    shadowWidgetRight->setShift(2);
    shadowWidgetRight->setBorderWidgetLower(true);

    shadowWidgetRight->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    shadowWidgetLeft->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Preferred);

//    QSplitter *splitter=new QSplitter;
//    splitter->addWidget(shadowWidgetLeft);
//    splitter->addWidget(shadowWidgetRight);

//    mainLayout->addWidget(splitter);
    mainLayout->addWidget(shadowWidgetLeft);
    mainLayout->addWidget(shadowWidgetRight);
//    mainLayout->setAlignment(shadowWidgetLeft,Qt::AlignBottom);
//    mainLayout->setAlignment(Qt::AlignBottom);

    leftOpacity=new QGraphicsOpacityEffect;
    leftOpacity->setOpacity(0.0);
    shadowWidgetLeft->setGraphicsEffect(leftOpacity);

    shadowWidgetLeft->hide();
    connect(ui->actionIn,&QAction::triggered,this,&MainWindow::moveIn);
    connect(ui->actionOut,&QAction::triggered,this,&MainWindow::moveOut);








}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::moveIn()
{
    QParallelAnimationGroup * Group=new QParallelAnimationGroup;
    QPropertyAnimation * opacity=new QPropertyAnimation(leftOpacity,"opacity");



    opacity->setDuration(300);
    opacity->setEasingCurve(QEasingCurve::Linear);
    opacity->setStartValue(leftOpacity->opacity());
    opacity->setEndValue(0.99);

    Group->addAnimation(opacity);
    shadowWidgetLeft->show();
    Group->start(QAbstractAnimation::DeleteWhenStopped);

}

void MainWindow::moveOut()
{
    QParallelAnimationGroup * Group=new QParallelAnimationGroup;
    QPropertyAnimation * opacity=new QPropertyAnimation(leftOpacity,"opacity");



    opacity->setDuration(300);
    opacity->setEasingCurve(QEasingCurve::Linear);
    opacity->setStartValue(leftOpacity->opacity());
    opacity->setEndValue(0.0);

    Group->addAnimation(opacity);
    connect(opacity,&QPropertyAnimation::finished,[=](){
        shadowWidgetLeft->hide();
    });
    Group->start(QAbstractAnimation::DeleteWhenStopped);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
//     view->getView()->MustBeResized();

}

void MainWindow::showEvent(QShowEvent *event)
{
    view->getView()->MustBeResized();


}
