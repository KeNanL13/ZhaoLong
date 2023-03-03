#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H

#include <QWidget>
#include <QMainWindow>

namespace Ui {
class titleWidget;
}

class titleWidget : public QWidget
{
    Q_OBJECT

public:
    explicit titleWidget(QWidget *parent = nullptr);
    titleWidget(QMainWindow *widget,QWidget *parent = nullptr);
    ~titleWidget();
signals:
    void openMainWindow();
private:
    Ui::titleWidget *ui;
    void startUp();
    QMainWindow *widget;
};

#endif // TITLEWIDGET_H
