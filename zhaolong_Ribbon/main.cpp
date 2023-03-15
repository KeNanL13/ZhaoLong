#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>
#include <QSplashScreen>
#include <MyComponents/splash.h>
#include <QThread>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(QFontDatabase::addApplicationFont(QDir::currentPath()+"/Font/Dengl.ttf")<0 )
    {
        qDebug()<<"fail to find font_awesome_6 ";
    }
    if( QFontDatabase::addApplicationFont(QDir::currentPath()+"/Font/font_awesome_6_solid_free.otf")<0)
    {
        qDebug()<<"fail to find awesome solid";
    }
    if(QFontDatabase::addApplicationFont(QDir::currentPath()+"/Font/Dengl.ttf")<0)
    {
        qDebug()<<"fail to find font_dengl";
    }
    if(QFontDatabase::addApplicationFont(QDir::currentPath()+"/Font/Dengb.ttf")<0)
    {
        qDebug()<<"fail to find font_Dengb";
    }
    if(QFontDatabase::addApplicationFont(QDir::currentPath()+"/Font/Deng.ttf")<0)
    {
        qDebug()<<"fail to find font_deng";
    }
    if(QFontDatabase::addApplicationFont(QDir::currentPath()+"/Font/corbel.ttf")<0)
    {
        qDebug()<<"fail to find font_corbel";
    }



    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QFont f;
    f.setFamily("微软雅黑");
    f.setPixelSize(13);
    a.setFont(f);

    Splash * splash=new Splash;
    splash->show();
    splash->AddMessage("正在初始化程序");

    MainWindow w;
    splash->CloseSplash(&w);



    return a.exec();
}
