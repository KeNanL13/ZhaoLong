#ifndef COMBINATIONWIDGET_H
#define COMBINATIONWIDGET_H

#include <QMainWindow>
#include <QEvent>
#include <framelesswidget.h>
#include <sidebar.h>
#include <aboutpage.h>


class CombinationWidget : public FrameLessWidget
{
    Q_OBJECT
public:
    explicit CombinationWidget(QWidget *parent = nullptr);

private:
    //Main ui layout
    QHBoxLayout *mainLayout =nullptr;

    //Side bar and corresponding pages
    sidebar * sideBar =nullptr;
    AboutPage * widget1=nullptr;

    //Place holder widget for resizing pages
    QWidget * placeHolderWidget=nullptr;

private:
    void resizePages(QResizeEvent * event);

private:
    virtual void showEvent(QShowEvent*event)override;
    virtual bool eventFilter(QObject * obj,QEvent* event)override;
signals:
    void finshInitial(QWidget*);
public slots:
};

#endif // COMBINATIONWIDGET_H
