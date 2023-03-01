#ifndef MYSHADOWWIDGET_H
#define MYSHADOWWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QGraphicsDropShadowEffect>


class MyShadowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MyShadowWidget(QWidget *parent = nullptr);

private:
    //Widget List
    QVBoxLayout* stretchLayout=nullptr;
    QWidget * windowWidget=nullptr;
    QWidget* windowBorder=nullptr;
    QGraphicsDropShadowEffect * windowShadow=nullptr;

    int cornerRadius=15;
    int shift=1;
    const QColor backgroundColor=QColor(251,251,251);
    const QColor borderColor=QColor(104,104,104);

    bool isInitial=false;
    bool isBorderLower=false;


private:
    void initialWidget();
public:
    QWidget * getMainWindow()const;
    void setShift(int shift);
    void setBorderWidth(float width);
    void setLayoutContentMargins(int left,int top,int right,int bottom);
    void setBorderWidgetLower(bool flag);
signals:

public slots:


protected:
    void showEvent(QShowEvent *event)override ;
    void resizeEvent(QResizeEvent *event)override;
};

#endif // MYSHADOWWIDGET_H
