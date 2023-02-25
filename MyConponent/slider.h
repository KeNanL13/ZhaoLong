#ifndef SLIDER_H
#define SLIDER_H

#include <QWidget>
#include <QBoxLayout>
#include <QSlider>
#include <QLabel>
#include <functional>
#include <pushbutton.h>

class Slider : public QWidget
{
    Q_OBJECT
public:
    explicit Slider(float min,float max,int step,QWidget *parent = nullptr);
private:
    //Settings
    float min;
    float max;
    int step; //Step count of slider value

    //State
    bool enable=true;

    //UI Settings
    const QColor defaultSchemeColor=QColor(58,143,183);
    QColor subColor;
    QColor addColor;
    QColor handleColor;
    QColor hoverColor;
    QColor pressColor;
    QColor restoredColor[5];

    //UI Layout
    QHBoxLayout * mainLayout;
    QSlider * slider;
    PushButton * decreaseBtn;
    QLabel * decreaseIcon;
    PushButton * increaseBtn;
    QLabel * increaseIcon;

    //Transformation function
    std::function<float(float)> transformFunc;
    std::function<float(float)> inversionFunc;
//    float (*transformFunc)(float)=nullptr;
//    float (*inverseFunc)(float)=nullptr;

private:
    void generatorColor(QColor schemeColor);
    void setSliderStyle();
public:
    //Getting APIs
    QHBoxLayout* getMainLayout()const {return mainLayout;}
    float getValue()const {return transformFunc(slider->value());}
    float getleValue()const {return slider->value();}

    //Setting APIs
    void setColorScheme(QColor color);
    void setMin(float value);
    void setMax(float value);
    void setStep(int  value);
    void setValue(float value);//Set the actual value
    void setTransformation(std::function<float(float)> transform,std::function<float(float)> inverse);
//    void setTranformation( float(*p)(float), float(*p2)(float)){
//        transformFunc=p;
//        inverseFunc=p2;
//    }
    void setEnable(bool enabled =true);
signals:
    void onChanged(float newVal);
    void onSetValue(float newVal);
    void onDragStart();
    void onDragEnd();


public slots:
};

#endif // SLIDER_H
