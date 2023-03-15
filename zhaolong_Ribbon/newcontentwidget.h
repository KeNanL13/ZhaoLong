#ifndef NEWCONTENTWIDGET_H
#define NEWCONTENTWIDGET_H

#include <QObject>
#include <QWidget>
#include <settingwidget_highspeed.h>
#include <occview.h>
#include <settingwidget_base.h>
#include <QGraphicsOpacityEffect>
#include <qtmaterialsnackbar.h>

class NewContentWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NewContentWidget(QWidget *parent = nullptr);


public:
    QVector<double> getInputParameter_Num();
    QVector<QString>getInputParameter_Text();
    void receiveInputMessage(QVector<QString> title,QVector<QString>value,QVector<QString>Metrics);
    void sendInputMessage();
    bool isInputComplete();
    void setProject(int i);
    void showToolWidget(SettingWidget_Base::CableType type);
    void closeToolWidget();
    void occResize();
    SettingWidget_Base* getToolWidget(){return toolWidget;}

private:
    void displayShape();
    void clearShape();


private:
    SettingWidget_Base * toolWidget=nullptr;
    OccView * occWidget=nullptr;
    QHBoxLayout * mainLayout=nullptr;
    QGraphicsOpacityEffect * opacity=nullptr;


signals:
    void transInfo(QVector<QString> title,QVector<QString>value,QVector<QString>Metrics);
public slots:

    // QWidget interface
protected:
    void showEvent(QShowEvent *event);
};

#endif // NEWCONTENTWIDGET_H
