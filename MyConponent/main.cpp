#include "mainwindow.h"
#include <QApplication>
#include <framelesswidget.h>
#include <combinationwidget.h>
#include <QFontDatabase>
#include <QDebug>
#include <materialcomponent.h>
#include <sliderpageexample.h>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    FrameLessWidget w(20,FrameLessWidget::UiWindow_NoAttributes);

    if(QFontDatabase::addApplicationFont("E:/QtProject/QtComponts/ZhaoLong/MyConponent/Font/font_awesome_6_regular_free.otf")<0 )
    {
        qDebug()<<"fail to find font_awesome_6 ";
    }
    if( QFontDatabase::addApplicationFont("E:/QtProject/QtComponts/ZhaoLong/MyConponent/Font/font_awesome_6_solid_free.otf")<0)
    {
        qDebug()<<"fail to find awesome solid";
    }
    if(QFontDatabase::addApplicationFont("E:/QtProject/QtComponts/ZhaoLong/MyConponent/Font/Dengl.ttf")<0)
    {
        qDebug()<<"fail to find font_dengl";
    }
    if(QFontDatabase::addApplicationFont("E:/QtProject/QtComponts/ZhaoLong/MyConponent/Font/Dengb.ttf")<0)
    {
        qDebug()<<"fail to find font_Dengb";
    }
    if(QFontDatabase::addApplicationFont("E:/QtProject/QtComponts/ZhaoLong/MyConponent/Font/Deng.ttf")<0)
    {
        qDebug()<<"fail to find font_deng";
    }
    if(QFontDatabase::addApplicationFont("E:/QtProject/QtComponts/ZhaoLong/MyConponent/Font/corbel.ttf")<0)
    {
        qDebug()<<"fail to find font_corbel";
    }
    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QFont f;
    f.setFamily("微软雅黑");
    f.setPixelSize(13);
    a.setFont(f);

    SliderPageExample w;
    w.show();

    return a.exec();
}
