#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>
#include <QLabel>
#include <QBoxLayout>
#include <QColor>
#include <QMap>
#include <QList>

#include "pushbutton.h"
#include "pagewidget.h"


class sidebar : public QWidget
{
    Q_OBJECT
public:
    explicit sidebar(QWidget *parent = nullptr);

private:
    //Initialized flag
    bool initialized=false;

    //UI control variables
    QColor backgroundColor=QColor(230,230,230);
    int collapsedWidth=90;
    int expandedWidth=200;

    //UI widgets
    PushButton * expandButton;
    QLabel *expandButtonIcon;
    QVBoxLayout* mainLayout=nullptr;//Layout expand icon and page selection buttons
    QWidget * pageIconButtonWidget=nullptr;
    QVBoxLayout * pageIconButtonLayout=nullptr;
    QWidget *pageTextButtonWidget=nullptr;
    QVBoxLayout*pageTextButtonLayout=nullptr;

    //Interaction controls
    bool expanded =false;
    PageWidget * currentPage=nullptr;

    //State storage
    //QMap<PageWidget*,QPair<PushButton*,PushButton*>>pageButtonMap;
    QList<PageWidget*>pageList;
    QList<QPair<PushButton*,PushButton*>>pageButtonList;

private:
    void expand();
    void collapse();
    void selectPage(PageWidget* page);

public:
    void setBackGroundColor(QColor color);
    void setCollapsedWidth(int width);
    void setExpandedWidth(int width);
    void addPage(PageWidget *page);
    void insertPage(PageWidget * page,int index);
    void removePage(PageWidget * page);
signals:
    void onPageChange(PageWidget* previousPage,PageWidget *currentPage);

public slots:
};

#endif // SIDEBAR_H
