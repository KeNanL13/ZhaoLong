#ifndef SLIDERPAGEEXAMPLE_H
#define SLIDERPAGEEXAMPLE_H

#include <QMainWindow>
#include <slidepage.h>

namespace Ui {
class SliderPageExample;
}

class SliderPageExample : public QMainWindow
{
    Q_OBJECT

public:
    explicit SliderPageExample(QWidget *parent = nullptr);
    ~SliderPageExample();

private:
    Ui::SliderPageExample *ui;
     SlidePage * page1=nullptr;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);
};

#endif // SLIDERPAGEEXAMPLE_H
