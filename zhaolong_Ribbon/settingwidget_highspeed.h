#ifndef SETTINGWIDGET_HIGHSPEED_H
#define SETTINGWIDGET_HIGHSPEED_H

#include <QWidget>
#include <settingwidget_base.h>
#include <qtmaterialtextfield.h>




class SettingWidget_HighSpeed : public SettingWidget_Base
{
    Q_OBJECT
public:
    explicit SettingWidget_HighSpeed(QWidget *parent = nullptr);
//Attribute
private:

    unsigned int mainRange[11]{0,1,2,5,6,7,3,4,8,9,10};
//    QVector<QtMaterialTextField*> cableInputLines;
    QVector<LineEditWidget*>cableInputLines;
    QVector<LineEditWidget*>textInputLines;
    QVector<QComboBox *>comboboxList;


    const QFont font=QFont("DengXian",12,QFont::Normal);

//Method
private:
    LineEditWidget * getLineEditWidget(QString label,QString comboboxItem);
    LineEditWidget * getLineEditWidget(QString label);
    LineEditWidget * getLineEditWidget(QString label,QList<QString> comboboxItems);
    QWidget * getSelectionLine(QString label,QList<QString>comboboxItems,QList<QString>comboboxMetrics);
    QWidget * getSelectionLine(QString label,QList<QString>comboboxItems);
    QWidget * getCheckWidget(QString label);

//    void shapeLineChanged(const QString & text);

\
//    void createHighSpeedCable(double r1,double d,double r2,double h,double l);

public :
    QVector<LineEditWidget*>getInputLines()const{return cableInputLines;}
    QVector<QComboBox*>getComboboxList()const {return comboboxList;}


    virtual bool isInputCompleted();
    virtual QVector<double> getInputNumber();
    virtual QVector<QString>getInputText();

    virtual ShapeWithColorList getShape();
    virtual int  isShapeInputCompleted();
    virtual void sendInputInformation();


signals:

public slots:
};

#endif // SETTINGWIDGET_HIGHSPEED_H
