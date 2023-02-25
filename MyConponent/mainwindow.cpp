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


    RoundedCornerWidget * widget1=new RoundedCornerWidget();
//    QWidget *widget=new QWidget;
    QVBoxLayout* leftLayout=new QVBoxLayout;
    leftLayout->addWidget(new QLabel("label1"));
    leftLayout->addWidget(new QLabel("label2"));
    leftLayout->addWidget(new QLabel("label3"));
//    widget1->setBorderColor(QColor(255,15,123));
    widget1->getMainWidget()->setLayout(leftLayout);
//    widget->setLayout(leftLayout);

     widget2=new RoundedCornerWidget();
//    QWidget * widget2=new QWidget();
    QVBoxLayout* rightLayout=new QVBoxLayout;
    view=new OccView();
    view->getView()->SetBgGradientColors(Quantity_NOC_SKYBLUE,Quantity_NOC_SKYBLUE4,Aspect_GFM_VER);
//    view->getView()->SetBackgroundColor(Quantity_Color(62.0/256.0,158.0/256.0,212.0/256.0,Quantity_TypeOfColor::Quantity_TOC_RGB));
    rightLayout->addWidget(view);
    rightLayout->setContentsMargins(0,0,0,0);
    widget2->getMainWidget()->setLayout(rightLayout);


//    widget2->setBorderColor(QColor()
//    widget2->setBorderColor(QColor(62,158,212));
//    widget2->setLayout(rightLayout);
    widget2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    connect(widget2,&RoundedCornerWidget::windowShowed,[=](){
        qDebug()<< "after windowShow";
        QString styleSheet=
                "QWidget#borderWidget{background-color:#00FFFFFF;border:2px solid qlineargradient(spread:pad, x1:0.5, y1:0, x2:0.5, y2:1, stop:0 rgba(62, 158, 211, 255), stop:1 rgba(17, 41, 66, 255)) "
                "border-radius:15 px;}";
        widget2->setBorderStyleSheet(styleSheet);
    });

    mainLayout->addWidget(widget1);
    mainLayout->addSpacing(8);
    mainLayout->addWidget(widget2);
    mainLayout->setSpacing(20);

    connect(ui->actionResize,&QAction::triggered,this,[=](){
//        view->getView()->MustBeResized();

    });
//     view=new OccView(this);
//     setCentralWidget(view);






}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

}

void MainWindow::resizeEvent(QResizeEvent *event)
{
     view->getView()->MustBeResized();

}

void MainWindow::showEvent(QShowEvent *event)
{
    view->getView()->MustBeResized();


}
