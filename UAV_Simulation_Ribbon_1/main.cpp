#include "mainwindow.h"
#include <titlewidget.h>
#include <QApplication>
#include <hpm_widget.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QFont f;
    f.setFamily("微软雅黑");
    f.setPixelSize(13);
    a.setFont(f);
    MainWindow *w=new MainWindow();
    titleWidget * title=new titleWidget(w,nullptr);
    title->show();
//        MainWindow W;
//        W.show();

//    HPM_Widget w;
//    w.show();

    return a.exec();
}
