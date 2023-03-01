#include "sliderpageexample.h"
#include "ui_sliderpageexample.h"
#include <QDebug>
#include <qtmaterialslider.h>
#include <qtmaterialdrawer.h>
#include <qtmaterialscrollbar.h>


SliderPageExample::SliderPageExample(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SliderPageExample)
{
    ui->setupUi(this);
    QWidget * mainWidget=new QWidget();
    setCentralWidget(mainWidget);
    //设置title

//    page1=new SlidePage(15,"参数查看",this);

//    textInputItem *  type=new textInputItem("线缆类型",page1);
//    type->setValue(QString("高速线"));

//    //设置具体参数
//    singleSelectGroup * group=new singleSelectGroup("layer",page1);
//    textInputItem * length=new textInputItem("线缆长度",page1);

//    length->setValue("1.2361 (mm)");
//    textInputItem * radius=new textInputItem("线缆长度",page1);
//    radius->setValue("1.2361 (mm)");
//    textInputItem * depth=new textInputItem("线缆长度",page1);
//    depth->setValue("1.2361 (mm)");
//    textInputItem * material=new textInputItem("线缆长度");
//    material->setValue("1.2361 (mm)");

//    //page 添加内容
//    page1->AddContent(material);
//    page1->AddContent(depth);
//    page1->AddContent(radius);
//    page1->AddContent(length);
//    page1->AddContent(group);
//    page1->AddContent(type);

    /**********QtMaterialDrawer***********/
    QtMaterialDrawer * slider=new QtMaterialDrawer(mainWidget);
    QVBoxLayout * layout=new QVBoxLayout();
    QScrollArea * scroll=new QScrollArea;
    QWidget * contentWidget=new QWidget;
//    widget->setWidget(contentWidget);
//    layout->addWidget(widget);
//    slider->setDrawerLayout(layout);

    QVBoxLayout * contentLayout=new QVBoxLayout;


//    textInputItem * line1=new textInputItem("text",contentWidget);
//    textInputItem * line2=new textInputItem("text",contentWidget);
//    textInputItem * line3=new textInputItem("text",contentWidget);
//    textInputItem * line4=new textInputItem("text",contentWidget);
//    textInputItem * line5=new textInputItem("text",contentWidget);
//    textInputItem * line6=new textInputItem("text",contentWidget);
    for(int i=0;i<20;i++)
    {
        QLineEdit * line=new QLineEdit(QString("%1").arg(i));
        contentLayout->addWidget(line);
    }


    contentWidget->setLayout(contentLayout);
//    layout->addWidget(contentWidget);
    QtMaterialScrollBar * bar1=new QtMaterialScrollBar;
    QtMaterialScrollBar * bar2=new QtMaterialScrollBar;
    bar1->setOrientation(Qt::Vertical);
    bar2->setOrientation(Qt::Horizontal);
    scroll->setVerticalScrollBar(bar1);
    scroll->setHorizontalScrollBar(bar2);

    scroll->setWidget(contentWidget);
    layout->addWidget(scroll);
    slider->setDrawerLayout(layout);

    //设置按钮触发page
    QPushButton * btn1=new QPushButton("trigger",mainWidget);
    btn1->move(mainWidget->width()/2-btn1->width()/2,mainWidget->height()/2-btn1->height()/2);

    slider->setClickOutsideToClose(true);
    slider->setOverlayMode(true);
    connect(btn1,&QPushButton::clicked,this,[=](){
//        page1->slideIn();
        slider->openDrawer();
    });


}

SliderPageExample::~SliderPageExample()
{
    delete ui;
}

void SliderPageExample::resizeEvent(QResizeEvent *event)
{
    if(page1!=nullptr)
    {
        qDebug()<<1;
        page1->resize(this->width() * 0.4 < page1->preferWidth ? page1->preferWidth  : this->width() * 0.4 , this->height());
    }
}