#ifndef SPLASH_H
#define SPLASH_H

#include <QWidget>
#include <myshadowwidget.h>
#include <QGraphicsOpacityEffect>
#include <QLabel>

class Splash : public MyShadowWidget
{
    Q_OBJECT
public:
    explicit Splash(QWidget *parent = nullptr);
    void CloseSplash(QWidget*);
private:
    QGraphicsOpacityEffect * opacity=nullptr;

    const QFont defaultFont=QFont("DengXian",12,QFont::Normal);
    QLabel * textLabel=nullptr;
    QWidget *nextWidget=nullptr;


//    QWidget * mainWidget=nullptr;

signals:

public slots:
    void AddMessage(QString msg);
    void setNextWidget(QWidget* widget);


    // QWidget interface
protected:
    void showEvent(QShowEvent *event);

};

#endif // SPLASH_H
