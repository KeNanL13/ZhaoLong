#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <roundedcornerwidget.h>
#include <occview.h>
#include <QGraphicsOpacityEffect>
#include <myshadowwidget.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    OccView *view;
    RoundedCornerWidget * widget2;
    QGraphicsOpacityEffect * leftOpacity;
    MyShadowWidget * shadowWidgetLeft;
    MyShadowWidget * shadowWidgetRight;
private:
    void moveIn();
    void moveOut();

    // QWidget interface
protected:
    void mouseMoveEvent(QMouseEvent *event);

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
};

#endif // MAINWINDOW_H
