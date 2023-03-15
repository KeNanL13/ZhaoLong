#include "lineeditwidget.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QDebug>

LineEditWidget::LineEditWidget(QWidget *parent) : QWidget(parent)
{
    //Generator colors
    genenrateColor(defaultColorScheme);

    //Initialize ui
    initializeUI();

    //Connect line edit events
    connect(editor,&QLineEdit::returnPressed,this,&LineEditWidget::endEdit);
    connect(editor,&QLineEdit::editingFinished,this,&LineEditWidget::endEdit);
    connect(editor,&QLineEdit::textChanged,this,&LineEditWidget::onTextChanged);

}

void LineEditWidget::initializeUI()
{
    //Construct and set main layout
    mainLayout=new QHBoxLayout(this);
    mainLayout->setContentsMargins(12,0,12,0);
    mainLayout->setSpacing(8);
    setLayout(mainLayout);

    //Construct editor container widget
    editorWidget=new QWidget(this);
    mainLayout->addWidget(editorWidget);
    editorWidget->show();

    //Construct editor layout to stretch editor widget
    editorWidgetLayout=new QHBoxLayout(editorWidget);
    editorWidgetLayout->setContentsMargins(0,10,0,10);
    editorWidgetLayout->setSpacing(0);
    editorWidget->setLayout(editorWidgetLayout);

    //Install event filter to editor widget to resize indicator
    editorWidget->installEventFilter(this);

    //Construct real text edit
    editor=new QLineEdit(editorWidget);
    editor->setText("");
    editor->setFont(defaultFont);
    editor->setAlignment(Qt::AlignRight);
    editor->setReadOnly(true);
    editor->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    editor->setStyleSheet("QLineEdit{color:#2c2c2c;background-color:#00ffffff;border-style:none;}");
    //editor->setFixedHeight(editor->fontMetrics().lineSpace());
    editor->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::Minimum);
    editorWidgetLayout->addWidget(editor);
    editor->show();

    //Construct indicator widget
    indicator=new QWidget(editorWidget);
    indicator->setObjectName("indicator");
    indicator->setStyleSheet("QWidget#indicator{background-color:"+indicatorColor.name(QColor::HexArgb)+";"
                             "border-radius:"+QString::number((float)indicatorWidth/2)+"px;}");

    indicator->resize(indicatorWidth,indicatorWidth);
    indicator->move(editorWidget->width()-indicatorWidth,editorWidget->height()-indicatorWidth-indicatorSpacing);
    indicatorEffect=new QGraphicsOpacityEffect(indicator);
    indicatorEffect->setOpacity(0);
    indicator->setGraphicsEffect(indicatorEffect);
    indicator->show();

    //Construct background widget
    backgroundWidget=new QWidget(this);
    backgroundWidget->resize(size());
    backgroundWidget->setObjectName("backgroundWidget");
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");
    backgroundWidget->lower();
    backgroundWidget->show();
    //Set size policy
    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);
}

void LineEditWidget::genenrateColor(QColor colorScheme)
{
    backgroundColor=colorScheme.lighter(120);
    backgroundColor.setAlpha(5);
    hoverColor=colorScheme.lighter(120);
    hoverColor.setAlpha(40);
    pressedColor=colorScheme.lighter(120);
    pressedColor.setAlpha(50);
    indicatorColor=colorScheme;
}

void LineEditWidget::startEdit()
{
    if(editing)
    {
        return;
    }
    qDebug()<<"start edit";
    //Set editng flag
    editing=true;

    //Enable QLineEdit widget
    editor->setReadOnly(false);
    editor->setAttribute(Qt::WA_TransparentForMouseEvents,false);
    editor->setFocus();
    editor->setCursorPosition(editor->text().length());

    //Minorly move cursor to update cursor icon
    QCursor::setPos(QCursor::pos()+QPoint(1,0));
    QCursor::setPos(QCursor::pos()+QPoint(-1,0));

    //Add grow and fade in animation for indicator
    QParallelAnimationGroup* startEditAnimation=new QParallelAnimationGroup(this);
    QPropertyAnimation * growAnimation=new QPropertyAnimation(indicator,"geometry");
    QPropertyAnimation * fadeInAnimation=new QPropertyAnimation(indicatorEffect,"opacity");
    growAnimation->setDuration(200);
    growAnimation->setEasingCurve(QEasingCurve::OutQuad);
    fadeInAnimation->setDuration(200);
    fadeInAnimation->setEasingCurve(QEasingCurve::OutQuad);
    growAnimation->setStartValue(indicator->geometry());
    growAnimation->setEndValue(QRect(
                                   0,
                                   editorWidget->height()-indicatorWidth-indicatorSpacing,
                                   editorWidget->width(),indicatorWidth)
                               );
    fadeInAnimation->setStartValue(indicatorEffect->opacity());
    fadeInAnimation->setEndValue(0.999);
    startEditAnimation->addAnimation(growAnimation);
    startEditAnimation->addAnimation(fadeInAnimation);
    startEditAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    //Emit signal
    emit onStartEditing(editor->text());

}

void LineEditWidget::endEdit()
{
    if(!editing)
    {
        return;
    }

    //Set editing flag
    editing=false;

    //Disable qlineedit widget
    editor->setReadOnly(true);
    editor->setAttribute(Qt::WA_TransparentForMouseEvents,true);
    editor->setSelection(0,0);

    //Add shrink and fade out animation for indicator
    QParallelAnimationGroup * endEditAnimation=new QParallelAnimationGroup(this);
    QPropertyAnimation * shrinkAnimation=new QPropertyAnimation(indicator,"geometry");
    QPropertyAnimation * fadeOutAnimation=new QPropertyAnimation(indicatorEffect,"opacity");
    shrinkAnimation->setDuration(200);
    shrinkAnimation->setEasingCurve(QEasingCurve::OutQuad);
    fadeOutAnimation->setDuration(200);
    fadeOutAnimation->setEasingCurve(QEasingCurve::OutQuad);
    shrinkAnimation->setStartValue(indicator->geometry());
    shrinkAnimation->setEndValue(QRect(
                                     editorWidget->width()-indicatorWidth,
                                     editorWidget->height()-indicatorWidth-indicatorSpacing,
                                     indicatorWidth,
                                     indicatorWidth
                                     ));
    fadeOutAnimation->setStartValue(indicatorEffect->opacity());
    fadeOutAnimation->setEndValue(0.0);
    endEditAnimation->addAnimation(shrinkAnimation);
    endEditAnimation->addAnimation(fadeOutAnimation);
    endEditAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    //emit signal
    emit onEndEditing(editor->text());
}

void LineEditWidget::showEvent(QShowEvent *event)
{
    //Call on parent
    QWidget::showEvent(event);

    //check initialize state
    if(initialized){
        return;
    }
    //Initialize size dependent widgets
    backgroundWidget->resize(size());
    if(editing)
    {
        indicator->move(0,editorWidget->height()-indicatorWidth-indicatorSpacing);
        indicator->resize(editorWidget->width(),indicatorWidth);

    }
    else{
        indicator->move(editorWidget->width()-indicatorWidth,editorWidget->height()-indicatorWidth-indicatorSpacing);
        indicator->resize(indicatorWidth,indicatorWidth);
    }
    initialized=true;
}

void LineEditWidget::enterEvent(QEvent *event)
{
    //Check on enabled
    if(enabled)
    {
        setCursor(Qt::PointingHandCursor);
    }

    //Change background color
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");

    //Set hover flag
    hovered =true;
}

void LineEditWidget::leaveEvent(QEvent *event)
{
    setCursor(Qt::ArrowCursor);

    //Change background color
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");

    //Set hover flag
    hovered =false;
    pressed=false;
}

void LineEditWidget::mousePressEvent(QMouseEvent *event)
{
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");
    pressed=true;
}

void LineEditWidget::mouseReleaseEvent(QMouseEvent *event)
{
    //Change background color
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");
    //Trigger on click
    if(pressed){
        if(enabled){
            if(editing){
                endEdit();
            }
            else{
                startEdit();
            }
        }
        else{
            if(editing){
                endEdit();
            }
        }
    }
    //Set pressed flag
    pressed=false;
}

void LineEditWidget::focusInEvent(QFocusEvent *event)
{
    //Call on parent
    QWidget::focusInEvent(event);

    //Check on enabled
    if(!enabled){
        return;
    }

    //Change background color
    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");
    //Start edit
    if(!editing)
    {
        startEdit();
    }
}

void LineEditWidget::focusOutEvent(QFocusEvent *event)
{
    QWidget::focusOutEvent(event);

    backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");
    //End edit
    if(editing)
    {
        endEdit();
    }
}

void LineEditWidget::resizeEvent(QResizeEvent *event)
{
    //Check initialize state
    if(!initialized)
    {
        return;
    }

    //Resize background widget
    backgroundWidget->resize(size());
}

bool LineEditWidget::eventFilter(QObject *obj, QEvent *event)
{
    //Resize indicator when editor widget size changed
    if(obj==editorWidget){
        if(event->type()==QEvent::Resize){
            if(editing){
                indicator->move(0,editorWidget->height()-indicatorWidth-indicatorSpacing);
                indicator->resize(editorWidget->width(),indicatorWidth);
            }
            else {
                indicator->move(editorWidget->width()-indicatorWidth,editorWidget->height()-indicatorWidth-indicatorSpacing);
                indicator->resize(indicatorWidth,indicatorWidth);
            }
        }
    }
    return QWidget::eventFilter(obj,event);
}

void LineEditWidget::setText(const QString &text)
{
    editor->setText(text);
}

void LineEditWidget::setPlaceHolderText(const QString &text)
{
    editor->setPlaceholderText(text);
}

void LineEditWidget::setValidator(const QValidator *validator)
{
    editor->setValidator(validator);
}

void LineEditWidget::setEnable(bool enable)
{
    enabled=enable;
    if(editing &&! enabled){
        endEdit();
    }
}

void LineEditWidget::setMargins(QMargins margins)
{
    mainLayout->setContentsMargins(margins);
}

void LineEditWidget::setMargins(int left, int top, int right, int bottom)
{
    mainLayout->setContentsMargins(left,top,right,bottom);
}

void LineEditWidget::setBackgroundColor(QColor color)
{
    backgroundColor=color;

    if(!hovered && !pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";"
                                        "border-radius:"+QString::number(cornerRadius)+"px;}");
    }
}

void LineEditWidget::setHoverColor(QColor color)
{
    hoverColor=color;

    if(hovered &&!pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";"
                                        "border-radius:"+QString::number(cornerRadius)+"px;}");
    }
}

void LineEditWidget::setPressedColor(QColor color)
{
    pressedColor=color;
    if(pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";"
                                        "border-radius:"+QString::number(cornerRadius)+"px;}");
    }
}

void LineEditWidget::setIndicatorColor(QColor color)
{
    indicatorColor=color;
    indicator->setStyleSheet("QWidget#indicator{background-color:"+indicatorColor.name(QColor::HexArgb)+";"
                                    "border-radius:"+QString::number(cornerRadius)+"px;}");
}

void LineEditWidget::setColorScheme(QColor primaryColor)
{
    genenrateColor(primaryColor);

    if(!hovered && !pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+backgroundColor.name(QColor::HexArgb)+";"
                                        "border-radius:"+QString::number(cornerRadius)+"px;}");
    }
    else if(hovered &&!pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+hoverColor.name(QColor::HexArgb)+";"
                                        "border-radius:"+QString::number(cornerRadius)+"px;}");
    }
    else if(pressed)
    {
        backgroundWidget->setStyleSheet("QWidget#backgroundWidget{background-color:"+pressedColor.name(QColor::HexArgb)+";"
                                        "border-radius:"+QString::number(cornerRadius)+"px;}");
    }
    indicator->setStyleSheet("QWidget#indicator{background-color:"+indicatorColor.name(QColor::HexArgb)+";"
                                                                                                        "border-radius:"+QString::number(cornerRadius)+"px;}");
}

void LineEditWidget::setAlignment(Qt::AlignmentFlag align)
{
    editor->setAlignment(align);
}

QString LineEditWidget::getText() const
{
    return editor->text();
}

QHBoxLayout *LineEditWidget::getMainLayout() const
{
    return mainLayout;
}

