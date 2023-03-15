#ifndef ROUNDEDCORNERWIDGET_H
#define ROUNDEDCORNERWIDGET_H

#include <QWidget>
#include <QBoxLayout>
#include <QEvent>

class RoundedCornerWidget : public QWidget
{
    Q_OBJECT
public:
    explicit RoundedCornerWidget(QWidget *parent = nullptr);

protected:
    //UI settings
    int cornerRadius=15;
    QColor borderColor=QColor(255,255,0);

    //UI elements
    QWidget * mainWidget=nullptr;
    QVBoxLayout * mainLayout=nullptr;
    QWidget *borderWidget=nullptr;

    //Initialization mark
    bool initialized=false;
    void initializeWidgetUI();

    //UI events
    virtual void showEvent(QShowEvent * event)override;
    virtual void resizeEvent(QResizeEvent *event)override;

public:
    //Public APIs
    void setCornerRadius(int radius);
    void setBorderColor(QColor color);
    void setBorderStyleSheet(QString styleSheet);
    QWidget * getMainWidget() const ;
signals:
    void windowShowed();

public slots:
};

#endif // ROUNDEDCORNERWIDGET_H
