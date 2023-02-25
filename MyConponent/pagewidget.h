#ifndef PAGEWIDGET_H
#define PAGEWIDGET_H

#include <QWidget>
#include <QGraphicsEffect>

#include "pushbutton.h"

class PageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PageWidget(QWidget *parent = nullptr);
protected:
    //Page layout and content widget(which holds the actual page elements)
    QVBoxLayout * stretchLayout=nullptr;
    QWidget * contentWidget=nullptr;

    //Button widgets for side bar
    PushButton * iconButton=nullptr;
    PushButton * textButton=nullptr;

    //Opacity effects
    QGraphicsOpacityEffect * pageOpacityEffect=nullptr;

    //Page position memory
    QPoint originPagePosition = QPoint(0,0);

public:
    virtual PushButton* getPageIconButton(QWidget* context) = 0;  // provide a push button with only an icon
    virtual PushButton* getPageTextButton(QWidget* context) = 0;  // provide a push button with an icon and a description text

public:
    void onStage();//provide an on stage animation when the page is selected
    void offStage();
signals:

public slots:
};

#endif // PAGEWIDGET_H
