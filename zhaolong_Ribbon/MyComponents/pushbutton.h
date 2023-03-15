#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QWidget>
#include <QEvent>
#include <QBoxLayout>
#include <QGraphicsEffect>
#include <QPropertyAnimation>
#include <QEnterEvent>

class PushButton : public QWidget
{
    Q_OBJECT
public:
    enum BtnIndicatorPos{
        BtnPos_Left,
        BtnPos_Right,
        BtnPos_Top,
        BtnPos_Bottom
    };
public:
    explicit PushButton(QWidget * child,QWidget *parent = nullptr);

private:
    //Button Layout
    QWidget * childWidget=nullptr;
    QRect childWidgetOriginalGeometry;
    const float childWidgetShrinkRatio=0.9f;
    QHBoxLayout * stretchLayout;
    QMargins contentMargin=QMargins(12,12,12,12);

    //Button ui
    int radius=8;

    QWidget* backgroundWidget;
    const QColor defaultColorScheme=QColor(58,143,183);
    QColor backgroundColor;
    QColor hoverColor;
    QColor pressedColor;
    QColor selectedColor;
    QColor restoredColor[5];

    QWidget * indicator;
    BtnIndicatorPos indicatorPostion=BtnPos_Left;
    const int indicatorWidth=6;
    const int indicatorSpacing=4;
    const float activatedLengthRatio=0.4f;
    const float hoveredLengthRadio=0.5f;
    const float pressedLengthRadio=0.2f;
    QColor indicatorColor;
    QGraphicsOpacityEffect * indicatorEffect;

    //Button state
    bool enabled=true;
    bool hovered=false;
    bool pressed=false;
    bool selected=false;

private:
    //UI util functions
    void initializeUI();
    void generatorColor(QColor colorScheme);

private:
    //Interactions
    virtual void enterEvent(QEvent *event)override;
    virtual void leaveEvent(QEvent* event)override;
    virtual void mousePressEvent(QMouseEvent*event)override;
    virtual void mouseReleaseEvent(QMouseEvent* event)override;
    virtual void resizeEvent(QResizeEvent * event)override;

public:
    //operation APIs
    void select();
    void deselect();
    void setEnabled(bool enabled=true);

    //Attribute setter APIs
    void setRadius(int radius);

    void setBackgroundColor(QColor color);
    void setHoverColor(QColor color);
    void setPressedColor(QColor color);
    void setSelectedColor(QColor color);
    void setIndicatorColor(QColor color);
    void setColorScheme(QColor primaryColor);

    QHBoxLayout * getMainLayout() const;
    void setAlignment(Qt::Alignment alignment);
    void setMargin(QMargins margin);
    void setMargin(int left,int top,int right,int bottom);

    void setIndicatorPosition(BtnIndicatorPos position);

    QWidget* getChildWidget()const;
    void setChildWidget(QWidget* widget);

    bool isSelected()const;

signals:
    void onClick();
    void onHover();
    void onPressed();



};

#endif // PUSHBUTTON_H
