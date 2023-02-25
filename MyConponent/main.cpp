#include "mainwindow.h"
#include <QApplication>
#include <framelesswidget.h>
#include <combinationwidget.h>
#include <QFontDatabase>
#include <QDebug>
#include <materialcomponent.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    FrameLessWidget w(20,FrameLessWidget::UiWindow_NoAttributes);

    if(QFontDatabase::addApplicationFont("D:/QtProjects/QtComponts/MyConponent/Font/font_awesome_6_regular_free.otf")<0 )
    {
        qDebug()<<"fail to find font_awesome_6 ";
    }
    if( QFontDatabase::addApplicationFont("D:/QtProjects/QtComponts/MyConponent/Font/font_awesome_6_solid_free.otf")<0)
    {
        qDebug()<<"fail to find awesome solid";
    }
    if(QFontDatabase::addApplicationFont("D:/QtProjects/QtComponts/MyConponent/Font/Dengl.ttf")<0)
    {
        qDebug()<<"fail to find font_dengl";
    }
    if(QFontDatabase::addApplicationFont("D:/QtProjects/QtComponts/MyConponent/Font/Dengb.ttf")<0)
    {
        qDebug()<<"fail to find font_Dengb";
    }
    if(QFontDatabase::addApplicationFont("D:/QtProjects/QtComponts/MyConponent/Font/Deng.ttf")<0)
    {
        qDebug()<<"fail to find font_deng";
    }
    if(QFontDatabase::addApplicationFont("D:/QtProjects/QtComponts/MyConponent/Font/corbel.ttf")<0)
    {
        qDebug()<<"fail to find font_corbel";
    }
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QFont f;
    f.setFamily("微软雅黑");
    f.setPixelSize(13);
    a.setFont(f);

    MainWindow w;
    w.show();

    return a.exec();
}
