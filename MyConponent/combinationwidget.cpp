#include "combinationwidget.h"
#include <QDebug>

CombinationWidget::CombinationWidget(QWidget *parent) : FrameLessWidget (20,0,parent)
{

    mainLayout=new QHBoxLayout(windowWidget);
    mainLayout->setContentsMargins(0,0,0,0);
    mainLayout->setSpacing(0);
    windowWidget->setLayout(mainLayout);

//    //Create placeholder widget for pages
    placeHolderWidget=new QWidget(windowWidget);
    placeHolderWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    placeHolderWidget->setMouseTracking(true);

//    //connect the resize event of the placeholder widget to the resizePages function using event filter
    placeHolderWidget->installEventFilter(this);

//    //Create sidebar
    sideBar=new sidebar(windowWidget);
    connect(sideBar,&sidebar::onPageChange,this,[=](PageWidget* previousPage,PageWidget*currentPage){
       if(previousPage==currentPage)
       {
           return;
       }
       if(previousPage!=nullptr){

           previousPage->offStage();
       }
       if(currentPage!=nullptr)
       {

           currentPage->onStage();
       }
    });

    sideBar->setMouseTracking(true);

//    //Add sidebar and placeholder widget to main layout
    mainLayout->addWidget(sideBar);
    mainLayout->addWidget(placeHolderWidget);

    //Create frist page and connect to side bar
    widget1=new AboutPage(placeHolderWidget);

    widget1->setMouseTracking(true);


    sideBar->addPage(widget1);

//    //Create second page
//    widget2=new PageWidget(placeHolderWidget);
//    widget2->setObjectName("widget2");
//    QString w2StyleSheet="QWidget#widget2{background-color :ffff3243 ;}";
//    widget2->setStyleSheet(w2StyleSheet);
//    widget2->setMouseTracking(true);
//    sideBar->addPage(widget2);

//    //Third page
//    widget3=new PageWidget(placeHolderWidget);
//    widget3->setObjectName("widget3");
//    QString w3StyleSheet="QWidget#widget3{background-color :ff1232ff ;}";
//    widget3->setStyleSheet(w3StyleSheet);
//    widget3->setMouseTracking(true);
//    sideBar->addPage(widget3);

//    emit finshInitial(this);

}

void CombinationWidget::resizePages(QResizeEvent *event)
{
    if(event==nullptr)
    {
        return;
    }

    //Get the size of the placeholder widget
    QSize size=event->size();

    //Resize the size of the placeHolder widget
    widget1->resize(size);
//    widget2->resize(size);
//    widget3->resize(size);

}

void CombinationWidget::showEvent(QShowEvent *event)
{
    FrameLessWidget::showEvent(event);

    widget1->resize(placeHolderWidget->size());

//    widget2->resize(placeHolderWidget->size());
//    widget3->resize(placeHolderWidget->size());
}

bool CombinationWidget::eventFilter(QObject *obj, QEvent *event)
{
    if(obj==nullptr || event==nullptr)
    {
        return false;
    }

    if(obj==placeHolderWidget){
        if(event->type()==QEvent::Resize){
            resizePages(static_cast<QResizeEvent*>(event));

        }
    }
    return FrameLessWidget::eventFilter(obj,event);
}
