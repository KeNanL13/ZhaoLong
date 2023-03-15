#ifndef LINEEDITWIDGET_H
#define LINEEDITWIDGET_H

#include <QWidget>
#include <QLineEdit>
#include <QBoxLayout>
#include <QGraphicsEffect>
#include <QEvent>

class LineEditWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LineEditWidget(QWidget *parent = nullptr);

private:
    //UI control variables
    int cornerRadius=8;

    //UI elements
    QHBoxLayout * mainLayout=nullptr;//For layout the user added components and the real editor component

    QWidget * backgroundWidget=nullptr;
    const QColor defaultColorScheme=QColor(58,143,183);
    QColor backgroundColor;
    QColor hoverColor;
    QColor pressedColor;

    QWidget * editorWidget=nullptr;//Container widget for the real edit component
    QHBoxLayout * editorWidgetLayout=nullptr;

    QLineEdit *editor=nullptr;
    const QFont defaultFont=QFont("DengXian",12,QFont::Normal);

    QWidget* indicator=nullptr;
    const int indicatorWidth=4;
    const int indicatorSpacing=4;
    QColor indicatorColor;
    QGraphicsOpacityEffect * indicatorEffect;

    //Editor state
    bool hovered=false;
    bool pressed=false;
    bool enabled=true;
    bool editing=false;
    bool initialized=false;

private:
    //UI Util functions
    void initializeUI();
    void genenrateColor(QColor colorScheme);

    //Interaction Util functions
    void startEdit();
    void endEdit();

private:
    //Interactions
    virtual void showEvent(QShowEvent * event)override;
    virtual void enterEvent(QEvent * event)override;
    virtual void leaveEvent(QEvent * event)override;
    virtual void mousePressEvent(QMouseEvent* event)override;
    virtual void mouseReleaseEvent(QMouseEvent* event)override;
    virtual void focusInEvent(QFocusEvent *event)override;
    virtual void focusOutEvent(QFocusEvent*event)override;
    virtual void resizeEvent(QResizeEvent * event)override;
    virtual bool eventFilter(QObject* obj,QEvent*event)override;

public:
    //Public setter APIs for text
    void setText(const QString& text);
    void setPlaceHolderText(const QString&text);
    void setValidator(const QValidator*validator);

    //Publics setting APIs for UI
    void setEnable(bool enable=true);
    void setMargins(QMargins margins);
    void setMargins(int left,int top,int right,int bottom);
    void setBackgroundColor(QColor color);
    void setHoverColor(QColor color);
    void setPressedColor(QColor color);
    void setIndicatorColor(QColor color);
    void setColorScheme(QColor primaryColor);
    void setAlignment(Qt::AlignmentFlag align);

    //public getter APIs
    QString getText() const ;
    QHBoxLayout *getMainLayout()const ;

signals:
    //public signal functions
    void onStartEditing(const QString & text);
    void onTextChanged(const QString & text);
    void onEndEditing(const QString & text);

public slots:
};

#endif // LINEEDITWIDGET_H
