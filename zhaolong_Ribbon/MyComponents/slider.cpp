#include "slider.h"

#include<QRegularExpression>

Slider::Slider(float min, float max, int step, QWidget *parent):
    QWidget (parent),min(min),max(max),step(step)
{
    //Set map functions
    transformFunc=[this](float x){
        //Map x of [0,step] to [min,max]
        float y=x/this->step*(this->max-this->min)+this->min;
        return y;
    };
    inversionFunc=[this](float x)
    {
        //Map x of[min,max] to [0,step]
        float y=(x-this->min)/(this->max-this->min)*this->step;
        return y;
    };

    //Generate colors
    generatorColor(defaultSchemeColor);
    //Create main layout
    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(4,4,4,4);
    mainLayout->setSpacing(0);
    setLayout(mainLayout);
    //Create slider
    slider=new QSlider(Qt::Horizontal,this);
    slider->setMinimum(0);
    slider->setMaximum(step);
    slider->setSingleStep(1);
    //Set slider style sheet
    setSliderStyle();
    //Create decrease button
    decreaseBtn=new PushButton(nullptr,this);
    decreaseBtn->setColorScheme(defaultSchemeColor);
    decreaseBtn->setFixedSize(24,24);
    decreaseBtn->setRadius(8);
    decreaseBtn->setMargin(0,0,0,3);
    decreaseBtn->setIndicatorColor(QColor(255,255,255,0));
    //Create decrease label
    decreaseIcon=new QLabel(decreaseBtn);
    decreaseIcon->setFont(QFont("Font Awesome 6 Free Solid",6));
    decreaseIcon->setText("\uf068");
    decreaseIcon->setAlignment(Qt::AlignCenter);
    decreaseBtn->setChildWidget(decreaseIcon);
    decreaseBtn->show();
    //Create increase button
    increaseBtn=new PushButton(nullptr,this);
    increaseBtn->setColorScheme(defaultSchemeColor);
    increaseBtn->setFixedSize(24,24);
    increaseBtn->setRadius(8);
    increaseBtn->setMargin(0,0,0,3);
    increaseBtn->setIndicatorColor(QColor(255,255,255,0));
    //Create increase label
    increaseIcon=new QLabel(increaseBtn);
    increaseIcon->setFont(QFont("Font Awesome 6 Free Solid",6));
    increaseIcon->setText("\uf067");
    increaseIcon->setAlignment(Qt::AlignCenter);
    increaseBtn->setChildWidget(increaseIcon);
    increaseIcon->show();
    //Add to main layout
    mainLayout->addWidget(decreaseBtn);
    mainLayout->addSpacing(4);
    mainLayout->addWidget(slider);
    mainLayout->addSpacing(4);
    mainLayout->addWidget(increaseBtn);
    decreaseBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    slider->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
    increaseBtn->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    decreaseBtn->show();
    slider->show();
    increaseBtn->show();
    //connect signals and slots
    connect(decreaseBtn,&PushButton::onClick,this,[=](){
        //Set current value
        slider->setValue(slider->value()+1);
        emit onChanged(transformFunc(slider->value()));
        emit onSetValue(transformFunc(slider->value()));
        emit onDragEnd();
    });
    connect(increaseBtn,&PushButton::onClick,this,[=](){
        //Set current value
        slider->setValue(slider->value()+1);
        emit onChanged(transformFunc(slider->value()));
        emit onSetValue(transformFunc(slider->value()));
        emit onDragEnd();
    });
    connect(slider,&QSlider::valueChanged,this,[this](int value){
        //Judge whether the silder is changed by dragging or function
        if(slider->isSliderDown()){
            //Value changed by user
            emit onChanged(transformFunc(value));
        }
        emit onSetValue(transformFunc(value));
    });
    connect(slider,&QSlider::sliderPressed,this,&Slider::onDragStart);
    connect(slider,&QSlider::sliderReleased,this,&Slider::onDragEnd);


}

void Slider::generatorColor(QColor schemeColor)
{
    subColor=schemeColor;
    addColor=QColor(216,216,216);
    handleColor=QColor(194,194,194);
    hoverColor=schemeColor.lighter(20);
    float hoverBlendRaito=0.2;
    hoverColor=QColor(
                hoverColor.red()*hoverBlendRaito+handleColor.red()*(1-hoverBlendRaito),
                hoverColor.green()*hoverBlendRaito+handleColor.green()*(1-hoverBlendRaito),
                hoverColor.blue()*hoverBlendRaito+handleColor.blue()*(1-hoverBlendRaito)
                );
    pressColor=schemeColor.lighter(20);
    float pressBlendRatio=0.5;
    pressColor=QColor(
                pressColor.red()*pressBlendRatio+handleColor.red()*(1-pressBlendRatio),
                pressColor.green()*pressBlendRatio+handleColor.green()*(1-pressBlendRatio),
                pressColor.blue()*pressBlendRatio+handleColor.blue()*(1-pressBlendRatio)
                );
}

void Slider::setSliderStyle()
{
    QString grooveStyle="QSlider::groove:horizontal{"
            "height:6px;"
            "border-radius:3px;"
            "}";
    QString sliderStyle="QSlider::handle:horizontal{"
            "width:12px;"
            "margin-bottom:-3px;"
            "margin-top:-3px;"
            "background:"+handleColor.name(QColor::HexArgb)+";"
            "}";
    QString sliderHoverStyle = "QSlider::handle:horizontal:hover {"
           "width:12px;"
           "margin-bottom:-3px;"
           "margin-top:-3px;"
           "background:" + hoverColor.name(QColor::HexArgb) + ";"
           "border-radius:6px;"
           "}";
       QString sliderPressStyle = "QSlider::handle:horizontal:pressed {"
           "width:12px;"
           "margin-bottom:-3px;"
           "margin-top:-3px;"
           "background:" + pressColor.name(QColor::HexArgb) + ";"
           "border-radius:6px;"
           "}";
       QString subStyle = "QSlider::sub-page:horizontal {"
           "background:" + subColor.name(QColor::HexArgb) + ";"
           "border-radius:3px;"
           "}";
       QString addStyle = "QSlider::add-page:horizontal {"
           "background:" + addColor.name(QColor::HexArgb) + ";"
           "border-radius:3px;"
           "}";
       slider->setStyleSheet(grooveStyle+sliderStyle+sliderHoverStyle+sliderPressStyle+subStyle+addStyle);
}

void Slider::setColorScheme(QColor color)
{
    generatorColor(color);
    //Change style Sheet
    setSliderStyle();

    //Change button color
    decreaseBtn->setColorScheme(color);
    decreaseBtn->setIndicatorColor(QColor(255,255,255,0));
    increaseBtn->setColorScheme(color);
    increaseBtn->setIndicatorColor(QColor(255,255,255,0));
}

void Slider::setMin(float value)
{
    min=value;
}

void Slider::setMax(float value)
{
    max=value;
}

void Slider::setStep(int  value)
{
    step=value;
    slider->setMaximum(step);
}

void Slider::setValue(float value)
{
    slider->setValue((int)inversionFunc(value));
}

void Slider::setTransformation(std::function<float (float)> transform, std::function<float (float)> inverse)
{
    transformFunc=transform;
    inversionFunc=inverse;
}

void Slider::setEnable(bool enabled)
{
    if(enable==enabled)
    {
        return;
    }
    enable=enabled;
    slider->setEnabled(enabled);
    decreaseBtn->setEnabled(enabled);
    increaseBtn->setEnabled(enabled);
    if(!enabled)
    {
        //Store colors
        restoredColor[0]=subColor;
        restoredColor[1]=addColor;
        restoredColor[2]=handleColor;
        restoredColor[3]=hoverColor;
        restoredColor[4]=pressColor;
        //Change colors
        setColorScheme(QColor(200,200,200));

    }
    else {
        //Restore colors
        subColor=restoredColor[0];
        addColor=restoredColor[1];
        handleColor=restoredColor[2];
        hoverColor=restoredColor[3];
        pressColor=restoredColor[4];
        //Change style sheet
        setSliderStyle();
        //Change button color
        decreaseBtn->setColorScheme(subColor);
        decreaseBtn->setIndicatorColor(QColor(255,255,255,0));
        increaseBtn->setColorScheme(subColor);
        increaseBtn->setIndicatorColor(QColor(255,255,255,0));

    }
}
