#include "mainwindow.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QFont f;
    f.setFamily("微软雅黑");
    f.setPixelSize(13);
    a.setFont(f);
    MainWindow w;
    w.show();


    return a.exec();
}
