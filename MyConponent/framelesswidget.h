#ifndef FRAMELESSWIDGET_H
#define FRAMELESSWIDGET_H

#include <QWidget>
#include <QEvent>
#include <QBoxLayout>
#include <QGraphicsColorizeEffect>
#include <QGraphicsEffect>
#include <QPushButton>

class FrameLessWidget : public QWidget
{
    Q_OBJECT
public:
    //window attributes
    enum UiWindowAttributes{
        UiWindow_NoAttributes =0,
        UiWindow_DisableClose =1<<0,//1<<0 中<<表示位移，所以表示1
        UiWindow_DisableMaxSize=1<<1,//2
        UiWindow_DisableMinSize=1<<2,//4
        UiWindow_DisableResize=1<<3//8
    };
public:
//    explicit FrameLessWidget(QWidget *parent = nullptr);
//    explicit FrameLessWidget(int cornerRadius, QWidget *parent=nullptr);
//    explicit FrameLessWidget(unsigned int attributes, QWidget* parent=nullptr);
    explicit FrameLessWidget(int cornerRadius,unsigned int attributes,QWidget *parent=nullptr);
    ~FrameLessWidget();

protected:
    //UI control variables
    const int m_cornerRadius=0;
    const QColor backgroundColor=QColor(251,251,251);
    const QColor borderColor=QColor(104,104,104);

    //Window initialize
    bool initialized=false;//防止初始化两次在从最小化恢复时
    void initialWindowUI();
    virtual void showEvent(QShowEvent* event)override;
    //Widget List
    QVBoxLayout* stretchLayout=nullptr;
    QWidget * windowWidget=nullptr;
    QWidget* windowBorder=nullptr;
    QGraphicsDropShadowEffect * windowShadow=nullptr;

    QWidget* windowBtnWidget=nullptr;
    QHBoxLayout *windowBtnLayout=nullptr;
    QPushButton * minimizeBtn=nullptr;
    QPushButton * maximizeBtn=nullptr;
    QPushButton * closeBtn=nullptr;

    //Window Size Control
    UiWindowAttributes m_attributes=UiWindow_NoAttributes;
    bool maximized=false;
    QRect lastWindowGeometry;

    virtual void resizeEvent(QResizeEvent *event)override;
    void controlWindowScale();

    //User interaction control
    enum MouseState{
        MouseState_None=0,
        MouseState_ResizeLeft=1<<0,
        MouseState_ResizeTop=1<<1,
        MouseState_ResizeRight=1<<2,
        MouseState_ResizeBottom=1<<3,
        MouseState_Move=1<<4
    };
    bool mousePressed=false;
    unsigned int  mouseState=MouseState_None;
    QPointF lastMousePosition;
    void updateMouseState(QMouseEvent *event);
    virtual void mousePressEvent(QMouseEvent* event)override;
    virtual void mouseReleaseEvent(QMouseEvent*event)override;
    virtual void mouseMoveEvent(QMouseEvent* event)override;
//    int i=0;

public:
    QWidget * getWindowWidget()const {return windowWidget;}
    UiWindowAttributes getWindowAttributes() const {return m_attributes;}
    void setWindowAttributes(unsigned int attributes);


signals:

public slots:
};

#endif // FRAMELESSWIDGET_H
