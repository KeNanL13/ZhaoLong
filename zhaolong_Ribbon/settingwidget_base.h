#ifndef SETTINGWIDGET_BASE_H
#define SETTINGWIDGET_BASE_H

#include <QObject>
#include <QWidget>
#include <MyComponents/myshadowwidget.h>
#include <TopoDS_Shape.hxx>
#include <MyComponents/lineeditwidget.h>
#include <QComboBox>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Shape.hxx>
#include <TopoDS_Face.hxx>
#include <Quantity_Color.hxx>


typedef QVector<QPair<TopoDS_Shape,Quantity_NameOfColor>> ShapeWithColorList;

class SettingWidget_Base : public MyShadowWidget
{
    Q_OBJECT
public:
    enum CableType{
        None,
        SingleCable,
        ParallelCable,
        TwistCable,
        HighSpeedCable
    };

public:
    explicit SettingWidget_Base(QWidget *parent = nullptr);
public:
    virtual QVector<double> getInputNumber()=0;
    virtual QVector<QString>getInputText()=0;
    virtual void sendInputInformation()=0;


    virtual ShapeWithColorList getShape()=0;
    virtual bool isInputCompleted()=0;
    virtual int  isShapeInputCompleted()=0;




protected:
    CableType m_type=None;
    QMap<QWidget*,QComboBox*>mapOfMetricsComboBox;
    QMap<QWidget*,QVector<double>>mapOfMetricsValue;
    int textLineCount;
    int numberLineCount;

    //基础线缆建模方法
    TopoDS_Face makeHoleFace(gp_Pnt pos,double bigRadius,double radius);
    TopoDS_Face makeCircle(gp_Pnt pos, double Radius);

    TopoDS_Wire makeOuter(gp_Pnt right,gp_Pnt ground,double rightRadius,double groundRadius);
    TopoDS_Face makeOuterMain(gp_Pnt right,gp_Pnt ground,double rightRadius,double leftRadius,double epsi);
public:
    CableType getType(){return m_type;}
    void setType(CableType type){m_type=type;}
    int getNumerInputCount(){return numberLineCount;}
    int getTextInputCount(){return textLineCount;}

signals:
    void transInputInfo(QVector<QString> title,QVector<QString>value,QVector<QString>Metrics);
    void createShape();
    void clearShape();


public slots:
};

#endif // SETTINGWIDGET_BASE_H
