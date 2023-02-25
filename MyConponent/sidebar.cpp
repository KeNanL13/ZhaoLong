#include "sidebar.h"
#include <QFontDatabase>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLayoutItem>
#include <QDebug>

sidebar::sidebar(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_StyledBackground,true);
    setMaximumWidth(collapsedWidth);

    //Create styleSheet
    setObjectName("sideBar");
    QString sideBarStyleSheet="QWidget#sideBar{background-color:"+backgroundColor.name(QColor::HexArgb)+";}";
    setStyleSheet(sideBarStyleSheet);

    //Create main layout
    mainLayout=new QVBoxLayout(this);
    mainLayout->setSpacing(8);
    mainLayout->setContentsMargins(16,16,16,16);
    mainLayout->setAlignment(Qt::AlignTop |Qt::AlignLeft);
    mainLayout->addSpacing(8);

    //Create expand button
    expandButton=new PushButton(nullptr,this);
    expandButton->setMargin(18,16,18,16);
    expandButton->setIndicatorColor(QColor(255,255,255,0));
    expandButton->setHoverColor(QColor(0,0,0,10));
    expandButton->setPressedColor(QColor(0,0,0,20));
    int buttonSize=collapsedWidth-mainLayout->contentsMargins().left()-mainLayout->contentsMargins().right();
    int buttonSizeMax=expandedWidth-mainLayout->contentsMargins().left()-mainLayout->contentsMargins().right();
    expandButton->setMinimumSize(buttonSize,buttonSize);
//    expandButton->setMaximumWidth(buttonSizeMax);
    expandButton->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Minimum);
    expandButtonIcon=new QLabel(expandButton);

    expandButtonIcon->setFont(QFont("Font Awesome 6 Free Solid",14));
    expandButtonIcon->setText("\uf0c9");
    expandButton->setChildWidget(expandButtonIcon);
    //Connect the expand button event to expand/collapse event
    connect(expandButton,&PushButton::onClick,this,[=](){
        qDebug()<<"click";
        if(expanded)
        {
            collapse();
            qDebug()<<"collapse";
        }else {
            expand();
            qDebug()<<"expand";
        }
    });

//    Add expand button to main layout
    mainLayout->addWidget(expandButton);
    expandButton->show();

    //Create the page icon button container widget
    pageIconButtonWidget=new QWidget(this);
    pageIconButtonWidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    pageIconButtonLayout=new QVBoxLayout(pageIconButtonWidget);
    pageIconButtonLayout->setSpacing(8);
    pageIconButtonLayout->setContentsMargins(0,0,0,0);
    pageIconButtonLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    pageIconButtonWidget->setLayout(pageIconButtonLayout);

    //Create the page text button container widget;
    pageTextButtonWidget=new QWidget(this);
    pageTextButtonWidget->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    pageTextButtonLayout=new QVBoxLayout(pageTextButtonWidget);
    pageTextButtonLayout->setSpacing(8);
    pageTextButtonLayout->setContentsMargins(0,0,0,0);
    pageTextButtonLayout->setAlignment(Qt::AlignTop | Qt::AlignLeft);
    pageTextButtonWidget->setLayout(pageTextButtonLayout);

    //Add page icon and text button container widgets to main layout
    mainLayout->addWidget(pageIconButtonWidget);
    mainLayout->addWidget(pageTextButtonWidget);

    //Display the icon buttons
    pageIconButtonWidget->show();
    pageTextButtonWidget->hide();

}

void sidebar::expand()
{
    //Add animation to expand the side bar
    QPropertyAnimation *expandAnimation=new QPropertyAnimation(this,"maximumWidth");
    expandAnimation->setDuration(650);
    expandAnimation->setEasingCurve(QEasingCurve::OutExpo);
    expandAnimation->setStartValue(width());
    expandAnimation->setEndValue(expandedWidth);
    expandAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    pageIconButtonWidget->hide();
    pageTextButtonWidget->show();

    expanded=true;
}

void sidebar::collapse()
{
    //Add animation to collapse the side bar
    QPropertyAnimation * collapseAnimation=new QPropertyAnimation(this,"maximumWidth");
    collapseAnimation->setDuration(650);
    collapseAnimation->setEasingCurve(QEasingCurve::OutExpo);
    collapseAnimation->setStartValue(width());
    collapseAnimation->setEndValue(collapsedWidth);
    collapseAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    //Show the page icon buttons
    pageIconButtonWidget->show();
    pageTextButtonWidget->hide();

    expanded=false;
}

void sidebar::selectPage(PageWidget *page)
{
    //Check for input validity
    if(page==nullptr)
    {
        return;
    }

    //Deselect current page if there is one
    if(currentPage!=nullptr)
    {
        qDebug()<<"test point :6";
        //Find the buttons of the current page
        int index=pageList.indexOf(currentPage);
        PushButton * currentPageIconButton=pageButtonList.at(index).first;
        PushButton * currentPageTextButton=pageButtonList.at(index).second;

        //Deselect both the buttons
        currentPageIconButton->deselect();
        currentPageTextButton->deselect();
    }

    //Temporarily store the current page
    PageWidget * previousPage=currentPage;

    //Select the new Page
    int index=pageList.indexOf(page);
    PushButton * newPageIconButton=pageButtonList.at(index).first;
    PushButton * newPageTextButton=pageButtonList.at(index).second;

    newPageIconButton->select();
    newPageTextButton->select();
    currentPage=page;

    //Emit the page selected signal
    emit onPageChange(previousPage,page);
}

void sidebar::setBackGroundColor(QColor color)
{
    QString sideBarStyleSheet="QWidget#sideBar{background-color:"+backgroundColor.name(QColor::HexArgb)+";}";
    setStyleSheet(sideBarStyleSheet);
}

void sidebar::setCollapsedWidth(int width)
{
    if(width<0)
    {
        return;
    }
    collapsedWidth=width;
}

void sidebar::setExpandedWidth(int width)
{
    if(width<0)
    {
        return;
    }
    expandedWidth=width;
}

void sidebar::addPage(PageWidget *page)
{
    //Call on the page's get button method to get icon button & text button
    PushButton * iconButton=page->getPageIconButton(pageIconButtonWidget);
    PushButton * textButton=page->getPageTextButton(pageTextButtonWidget);

    //Store the page in the page list
    pageList.append(page);

    //Store the corresponding buttons
    pageButtonList.append(QPair<PushButton*,PushButton*>(iconButton,textButton));

    //Add the icon button to the icon button layout
    pageIconButtonLayout->addWidget(iconButton);
    iconButton->show();

    //Add the text button to the text button layout
    pageTextButtonLayout->addWidget(textButton);
    textButton->show();

    //Resize the buttons and set size policy to fixed
    int buttonSize=collapsedWidth-mainLayout->contentsMargins().left()-mainLayout->contentsMargins().right();
    int buttonSizeMax=expandedWidth-mainLayout->contentsMargins().left()-mainLayout->contentsMargins().right();

    iconButton->setMinimumSize(buttonSize,buttonSize);
    textButton->setMinimumSize(buttonSize,buttonSize);
    iconButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    textButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    //Connect the button click event with page selection
    connect(iconButton,&PushButton::onClick,this,[=](){
        this->selectPage(page);
    });
    connect(textButton,&PushButton::onClick,this,[=](){
        this->selectPage(page);
    });

    //Select the page if there are no pages
    if(currentPage==nullptr)
    {
        selectPage(page);
    }

}

void sidebar::insertPage(PageWidget *page, int index)
{
    PushButton * iconButton=page->getPageIconButton(pageIconButtonWidget);
    PushButton * textButton=page->getPageTextButton(pageTextButtonWidget);

    //Store the page in the page list
    pageList.insert(index,page);

    //Store the corresponding buttons
    pageButtonList.insert(index,QPair<PushButton*,PushButton*>(iconButton,textButton));

    //Add the icon button to the icon button layout
    pageIconButtonLayout->insertWidget(index,iconButton);
    iconButton->show();

    //Add the text button to the text button layout
    pageTextButtonLayout->insertWidget(index,textButton);
    textButton->show();

    //Resize the buttons and set size policy to fixed
    int buttonSize=collapsedWidth-mainLayout->contentsMargins().left()-mainLayout->contentsMargins().right();
    int buttonSizeMax=expandedWidth-mainLayout->contentsMargins().left()-mainLayout->contentsMargins().right();

    iconButton->setMinimumSize(buttonSize,buttonSize);
    textButton->setMinimumSize(buttonSize,buttonSize);
    iconButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    textButton->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

    //Connect the button click event with page selection
    connect(iconButton,&PushButton::onClick,this,[=](){
        this->selectPage(page);
    });
    connect(textButton,&PushButton::onClick,this,[=](){
        this->selectPage(page);
    });

    //Select the page if there are no pages
    if(currentPage==nullptr)
    {
        selectPage(page);
    }
}

void sidebar::removePage(PageWidget *page)
{
    //Get the index of the page from the page list
    int index=pageList.indexOf(page);

    //Call on the page's get button method to get icon button & text button
    PushButton *iconButton=pageButtonList.at(index).first;
    PushButton *textButton=pageButtonList.at(index).second;


    //Store the page in the page list
    pageList.removeAt(index);

    //Store the corresponding buttons
    pageButtonList.removeAt(index);

    //Add the icon button to the icon button layout
    pageIconButtonLayout->removeWidget(iconButton);
    iconButton->hide();

    //Add the text button to the text button layout
    pageTextButtonLayout->removeWidget(textButton);
    textButton->hide();



    //Select the first page if the current page is the page being removed
    if(currentPage==page)
    {
        if(pageList.size()>0)
        {
            selectPage(pageList.first());
        }
        else{
            currentPage=nullptr;
        }
    }
}
