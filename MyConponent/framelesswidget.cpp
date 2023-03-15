#include "framelesswidget.h"
#include <QApplication>
#include <QPainterPath>
#include <QScreen>
#include <QLabel>
#include <QDebug>
#include <QMouseEvent>
#include <QPointF>
#include <QPoint>
#define MAX_MOUSE_MOVEMENT 300

FrameLessWidget::FrameLessWidget(int cornerRadius, unsigned int attributes, QWidget *parent)
    :  QWidget (parent),m_cornerRadius(cornerRadius),m_attributes((UiWindowAttributes)attributes)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint |Qt::WindowSystemMenuHint |Qt::WindowMinimizeButtonHint);
    setFocusPolicy(Qt::StrongFocus);
    setMouseTracking(true);
    setFocus();
    //Create and properly set real displayed window widget
    stretchLayout=new QVBoxLayout(this);
    stretchLayout->setContentsMargins(30,30,30,30);
    windowWidget=new QWidget(this);
    windowWidget->setObjectName("windowWidget");
    windowWidget->setMouseTracking(true);
    stretchLayout->addWidget(windowWidget);
    windowWidget->show();
    setLayout(stretchLayout);

    //Set style sheet for window widget
    QString windowWidgetStyleSheet="QWidget#windowWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";border-radius:"+QString::number(cornerRadius)+"px;}";
    windowWidget->setStyleSheet(windowWidgetStyleSheet);
    //Set shadow for window widget
    windowShadow=new QGraphicsDropShadowEffect(windowWidget);
    windowShadow->setBlurRadius(30);
    windowShadow->setColor(QColor(0,0,0));
    windowShadow->setOffset(0,0);
    windowWidget->setGraphicsEffect(windowShadow);

    //Create window control buttons container widget & its layout
    windowBtnWidget=new QWidget(windowWidget);
    windowBtnWidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    windowBtnWidget->setMouseTracking(true);
    windowBtnLayout=new QHBoxLayout(windowBtnWidget);
    windowBtnLayout->setContentsMargins(0,0,0,0);
    windowBtnLayout->setSpacing(10);
    windowBtnLayout->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    windowBtnWidget->setLayout(windowBtnLayout);

    //Create window control buttons
    minimizeBtn=new QPushButton(windowBtnWidget);
    maximizeBtn=new QPushButton(windowBtnWidget);
    closeBtn=new QPushButton(windowBtnWidget);

    minimizeBtn->setFixedSize(12,12);
    maximizeBtn->setFixedSize(12,12);
    closeBtn->setFixedSize(12,12);
    minimizeBtn->setStyleSheet("QPushButton{border-radius:6px;background-color:#c2c2c2;}"
                               "QPushButton:hover{background-color:#e98b2a;}");
    maximizeBtn->setStyleSheet("QPushButton{border-radius: 6px; background-color: #c2c2c2;}"
                               "QPushButton:hover{background-color: #2d6d4b;}");
    closeBtn->setStyleSheet("QPushButton{border-radius: 6px; background-color: #c2c2c2;}"
                            "QPushButton:hover{background-color: #ab3b3a;}");
    windowBtnLayout->addWidget(minimizeBtn);
    windowBtnLayout->addWidget(maximizeBtn);
    windowBtnLayout->addWidget(closeBtn);
    if((attributes & UiWindow_DisableMinSize)==0){
        minimizeBtn->show();
    }
    if((attributes & UiWindow_DisableMaxSize)==0){
        maximizeBtn->show();
    }
    if((attributes & UiWindow_DisableClose)==0){
        closeBtn->show();
    }
    connect(minimizeBtn,&QPushButton::clicked,this,&QWidget::showMinimized);
    connect(maximizeBtn,&QPushButton::clicked,this,&FrameLessWidget::controlWindowScale);
    connect(closeBtn,&QPushButton::clicked,this,&QWidget::close);
    resize(800,600);
}

FrameLessWidget::~FrameLessWidget()
{

}


void FrameLessWidget::showEvent(QShowEvent *event)
{
    //Initialize window UI after window is shown
    initialWindowUI();
}

void FrameLessWidget::initialWindowUI()
{
    if(initialized)
    {
        return;
    }
    //Create a round cornered mask for window widget
    QPainterPath path;
    path.addRoundedRect(windowWidget->rect(),m_cornerRadius-1,m_cornerRadius-1);
    QRegion region(path.toFillPolygon().toPolygon());
    windowWidget->setMask(region);
    //Create a border for window widget(in order to hide zigzagged edges)
    windowBorder=new QWidget(this);
    windowBorder->setObjectName("windowBorder");
    QString windowBorderStyleSheet=
            "QWidget#windowBorder{background-color:#00FFFFFF;border:1.5px solid"+borderColor.name(QColor::HexArgb)+";border-radius:"+QString::number(m_cornerRadius)+"px;}";
    windowBorder->setStyleSheet(windowBorderStyleSheet);
    windowBorder->setAttribute(Qt::WA_TransparentForMouseEvents);
    windowBorder->move(windowWidget->pos()-QPoint(1,1));
    windowBorder->resize(windowWidget->size()+QSize(2,2));
    windowBorder->show();
//    windowBorder->hide();


    //Move button widget to the top right of the window widget
    windowBtnWidget->move(windowWidget->width()-windowBtnWidget->width()-18,18);
    qDebug()<<"first:"<<windowWidget->width()<<"btn:"<<windowBtnWidget->geometry().bottom();
//     windowBtnWidget->move(18,windowWidget->height()-windowBtnWidget->height()-18);
    windowBtnWidget->show();
    windowBtnWidget->raise();
    initialized=true;
    qDebug()<<"主窗口的位置:"<<this->pos() <<"  主窗口的宽高:"<<this->width()<<","<<this->height();
    qDebug()<<"主窗口的Rect:"<<this->rect();
    qDebug()<<"windowWidget的位置:"<<windowWidget->pos() <<"  主窗口的宽高:"<<windowWidget->width()<<","<<windowWidget->height();
    qDebug()<<"windowWidget的Rect:"<<windowWidget->frameGeometry().left()<<","<<windowWidget->frameGeometry().right()<<","<<windowWidget->frameGeometry().top()<<","<<windowWidget->frameGeometry().bottom()<<","<<windowWidget-> frameGeometry().topRight();
    qDebug()<<"windowBorder的位置:"<<windowBorder->pos() <<"  主窗口的宽高:"<<windowBorder->width()<<","<<windowBorder->height();
    qDebug()<<"主窗口的Rect:"<<windowBorder->geometry().left()<<","<<windowBorder->geometry().right()<<","<<windowBorder->geometry().top()<<","<<windowBorder->geometry().bottom();
}

void FrameLessWidget::resizeEvent(QResizeEvent *event)
{
    //Resize window border
    if(windowBorder!=nullptr){
        windowBorder->move(windowWidget->pos()-QPoint(1,1));
        windowBorder->resize(windowWidget->size()+QSize(2,2));
    }
    //Resize window mask
    QPainterPath path;
    path.addRoundedRect(windowWidget->rect(),m_cornerRadius-1,m_cornerRadius-1);
    QRegion region(path.toFillPolygon().toPolygon());
    windowWidget->setMask(region);

    //Move button widget to the top right of the window widget
    windowBtnWidget->move(windowWidget->width()-windowBtnWidget->width()-18,18);

//    windowBtnWidget->move(18,windowWidget->height()-windowBtnWidget->height()-18);
}

void FrameLessWidget::controlWindowScale()
{
    if((m_attributes & UiWindow_DisableMaxSize)!=0){
        return;
    }
    if(!maximized){
        lastWindowGeometry=frameGeometry();
//        qDebug()<<"Maximizing window:";
//        qDebug()<<"[+]current window position:"<<x()<<","<<y();
//        qDebug()<<"[+]current window size:"<<width()<<","<<height();
//        qDebug()<<"[+]current geometry:"<<lastWindowGeometry.x()<<","<<lastWindowGeometry.y()<<","<<lastWindowGeometry.width()<<","<<lastWindowGeometry.height();
//        qDebug()<<"[+]current window widget position:"<<windowWidget->x()<<","<<windowWidget->y();
//        qDebug()<<"[+]current window widget size:"<<windowWidget->width()<<","<<windowWidget->height();
//        qDebug()<<"[+]current window border postion:"<<windowBorder->x()<<","<<windowBorder->y();
//        qDebug()<<"[+]current window border size:"<<windowBorder->width()<<","<<windowBorder->height();

        windowShadow->setEnabled(false);
        windowBorder->hide();
        QString windowWidgetStyleSheet="QWidget#windowWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";}";
        windowWidget->setStyleSheet(windowWidgetStyleSheet);

        stretchLayout->setContentsMargins(0,0,0,0);

        showMaximized();

        QPainterPath path;
        path.addRect(windowWidget->rect());
        QRegion mask(path.toFillPolygon().toPolygon());
        windowWidget->setMask(mask);

        maximized=true;
    }
    else{
        stretchLayout->setContentsMargins(30,30,30,30);

        showNormal();

        resize(lastWindowGeometry.size());
        move(lastWindowGeometry.topLeft());

        windowShadow->setEnabled(true);
        windowBorder->show();
        QString windowWidgetStyleSheet= "QWidget#windowWidget{background-color:" + backgroundColor.name(QColor::HexArgb) + ";border-radius:" + QString::number(m_cornerRadius) + "px;}";
        windowWidget->setStyleSheet(windowWidgetStyleSheet);

        QPainterPath path;
        path.addRoundedRect(windowWidget->rect(),m_cornerRadius-1,m_cornerRadius-1);
        QRegion mask(path.toFillPolygon().toPolygon());
        windowWidget->setMask(mask);

//        qDebug()<<"Restoring window:";
//        qDebug()<<"[+]current window position:"<<x()<<","<<y();
//        qDebug()<<"[+]current window size:"<<width()<<","<<height();
//        qDebug()<<"[+]current geometry:"<<lastWindowGeometry.x()<<","<<lastWindowGeometry.y()<<","<<lastWindowGeometry.width()<<","<<lastWindowGeometry.height();
//        qDebug()<<"[+]current window widget position:"<<windowWidget->x()<<","<<windowWidget->y();
//        qDebug()<<"[+]current window widget size:"<<windowWidget->width()<<","<<windowWidget->height();

        maximized=false;
    }
}

void FrameLessWidget::updateMouseState(QMouseEvent *event)
{

    mouseState=MouseState_None;
    if((m_attributes & UiWindow_DisableResize) !=0 ){
        return ;
    }
    if(maximized){
        setCursor(Qt::ArrowCursor);
        return;
    }

    //Set mouse state according to abs distance from window border
    if(abs(event->globalPos().x()-(windowWidget->frameGeometry().left()+frameGeometry().left())) < 5){
        mouseState |= MouseState_ResizeLeft ;
    }
    if(abs(event->globalPos().x()-(windowWidget->frameGeometry().right()+frameGeometry().left())) < 5){
        mouseState |= MouseState_ResizeRight ;
    }
    if(abs(event->globalPos().y()-(windowWidget->frameGeometry().top()+frameGeometry().top())) < 5){
        mouseState |= MouseState_ResizeTop ;

    }
    if(abs(event->globalPos().y()-(windowWidget->frameGeometry().bottom()+frameGeometry().top())) < 5){
        mouseState |= MouseState_ResizeBottom ;
    }
    //1.left  2.right  3.top 4.bottom
    if(event->globalPos().x()-(windowWidget->frameGeometry().left()+frameGeometry().left())>5 &&
            windowWidget->frameGeometry().right()+frameGeometry().left()-windowBtnWidget->width()-event->globalPos().x()>5&&
            event->globalPos().y()>frameGeometry().top()+windowWidget->frameGeometry().top()+5&&
            event->globalPos().y()<frameGeometry().top()+windowWidget->frameGeometry().top()+windowBtnWidget->geometry().bottom())
    {
        mouseState |=MouseState_Move;
//        qDebug()<<"mousePosition"<<event->globalPos();
//        qDebug()<<"windowWidget geometry:"<<windowWidget->frameGeometry()<<"  left:"<<windowWidget->geometry().left();
//        qDebug()<<"framegeometry:"<<frameGeometry()<<"   left :"<<geometry().left();
    }

    switch (mouseState) {
    case MouseState_ResizeLeft:
    case MouseState_ResizeRight:
        setCursor(Qt::SizeHorCursor);
        break;
    case MouseState_ResizeTop:
    case MouseState_ResizeBottom:
        setCursor(Qt::SizeVerCursor);
        break;
    case MouseState_ResizeLeft | MouseState_ResizeTop:
    case MouseState_ResizeRight | MouseState_ResizeBottom:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case MouseState_ResizeLeft | MouseState_ResizeBottom:
    case MouseState_ResizeRight | MouseState_ResizeTop:
        setCursor(Qt::SizeBDiagCursor);
        break;
    case MouseState_Move:
        setCursor(Qt::OpenHandCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
        break;
    }
}

void FrameLessWidget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        mousePressed=true;

        lastMousePosition=event->globalPos();
    }
}

void FrameLessWidget::mouseReleaseEvent(QMouseEvent *event)
{
    mousePressed=false;
    QScreen * screen=QGuiApplication::screenAt(event->globalPos());
//    qDebug()<<"Current screen geometry:";
//    qDebug()<<"[+]screen position:"<<screen->geometry().x()<<","<<screen->geometry().y();
//    qDebug()<<"[+]screen size:"<<screen->geometry().width()<<","<<screen->geometry().height();
    if(abs(event->globalPos().y()-screen->geometry().top())<5)
    {
        controlWindowScale();
    }
    updateMouseState(event);
}

void FrameLessWidget::mouseMoveEvent(QMouseEvent *event)
{
//    qDebug()<<"Detected mouse move";
    if(event->buttons()==Qt::NoButton)
    {
        mousePressed=false;
    }
    if(abs(event->globalPos().x()-lastMousePosition.x())>MAX_MOUSE_MOVEMENT){
        lastMousePosition=event->globalPos();
    }
    if(abs(event->globalPos().y()-lastMousePosition.y())>MAX_MOUSE_MOVEMENT){
        lastMousePosition=event->globalPos();
    }
    if(!mousePressed){
        updateMouseState(event);
    }
    else{
        switch (mouseState) {
        case MouseState_ResizeLeft:
           resize(frameGeometry().width()-event->globalPos().x()+frameGeometry().left()+windowWidget->frameGeometry().left(),frameGeometry().height());
           move(event->globalPos().x()-windowWidget->frameGeometry().left(),frameGeometry().top());
            break;
        case MouseState_ResizeRight:
//            qDebug()<<"鼠标位置:"<<event->globalPos()<<"  主窗口FrameGeometry:"<<frameGeometry().left()<<"  windowwidget的geometry:"<<windowWidget->frameGeometry().left();
//            qDebug()<<frameGeometry().right()<<"  "<<windowWidget->frameGeometry().right();
            resize(event->globalPos().x()-frameGeometry().left()+windowWidget->frameGeometry().left(),frameGeometry().height());
            break;
        case MouseState_ResizeTop:
            resize(frameGeometry().width(),frameGeometry().height()-event->globalPos().y()+frameGeometry().top()+windowWidget->frameGeometry().top());
            move(frameGeometry().left(),event->globalPos().y()-windowWidget->frameGeometry().top());
            break;
        case MouseState_ResizeBottom:
            resize(frameGeometry().width(),event->globalPos().y()-frameGeometry().top()+windowWidget->frameGeometry().top());
            break;
        case MouseState_ResizeLeft | MouseState_ResizeTop:
            resize(frameGeometry().width() - event->globalPos().x() + frameGeometry().left() + windowWidget->frameGeometry().left(), frameGeometry().height() - event->globalPos().y() + frameGeometry().top() + windowWidget->frameGeometry().top());
            move(event->globalPos().x() - windowWidget->frameGeometry().left(), event->globalPos().y() - windowWidget->frameGeometry().top());
            break;
        case MouseState_ResizeLeft |MouseState_ResizeBottom:
            resize(frameGeometry().width() - event->globalPos().x() + frameGeometry().left() + windowWidget->frameGeometry().left(), event->globalPos().y() - frameGeometry().top() + windowWidget->frameGeometry().top());
            move(event->globalPos().x() - windowWidget->frameGeometry().left(), frameGeometry().top());
            break;
        case MouseState_ResizeRight | MouseState_ResizeTop :
            resize(event->globalPos().x() - frameGeometry().left() + windowWidget->frameGeometry().left(), frameGeometry().height() - event->globalPos().y() + frameGeometry().top() + windowWidget->frameGeometry().top());
            move(frameGeometry().left(), event->globalPos().y() - windowWidget->frameGeometry().top());
            break;
        case MouseState_ResizeRight | MouseState_ResizeBottom :
            resize(event->globalPos().x() - frameGeometry().left() + windowWidget->frameGeometry().left(), event->globalPos().y() - frameGeometry().top() + windowWidget->frameGeometry().top());
            break;
        case MouseState_Move:
            move(frameGeometry().left()+event->globalPos().x()-lastMousePosition.x(),frameGeometry().top()+event->globalPos().y()-lastMousePosition.y());
            break;
        default:
            if(maximized){
                qreal wRatio =(qreal)event->pos().x()/(qreal)windowWidget->width();
                controlWindowScale();
                move(event->globalPos().x()-windowWidget->width()*wRatio,event->globalPos().y()-52);
            }
//            else{
//                move(frameGeometry().left()+event->globalPos().x()-lastMousePosition.x(),frameGeometry().top()+event->globalPos().y()-lastMousePosition.y());
//            }
            break;
        }
        lastMousePosition=event->globalPos();
    }
}

void FrameLessWidget::setWindowAttributes(unsigned int attributes)
{
     m_attributes=(UiWindowAttributes)attributes;
        if ((m_attributes & UiWindow_DisableMinSize) == 0) {
            minimizeBtn->show();
        }
        else {
            minimizeBtn->hide();
        }
        if ((m_attributes & UiWindow_DisableMaxSize) == 0) {
            maximizeBtn->show();
        }
        else {
            maximizeBtn->hide();
        }
        if ((m_attributes & UiWindow_DisableClose) == 0) {
            closeBtn->show();
        }
        else {
            closeBtn->hide();
        }
}

