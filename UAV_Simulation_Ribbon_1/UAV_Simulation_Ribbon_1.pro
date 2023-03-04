#-------------------------------------------------
#
# Project created by QtCreator 2022-09-26T10:42:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts printsupport

TARGET = UAV_Simulation_Ribbon
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    titlewidget.cpp \
    occview.cpp \
    hpm_widget.cpp \
    environmentwidget.cpp \
    modelwidget.cpp \
    modeltreewidget.cpp \
    occread.cpp \
    simulationwidget.cpp \
    hpmsettingwidget.cpp \
    hpm_source.cpp \
    AdaptorVec_AIS.cxx \
    qcustomplot.cpp

HEADERS += \
        mainwindow.h \
    titlewidget.h \
    occview.h \
    hpm_widget.h \
    environmentwidget.h \
    modelwidget.h \
    modeltreewidget.h \
    occread.h \
    simulationwidget.h \
    hpmsettingwidget.h \
    hpm_source.h \
    AdaptorVec_AIS.h \
    qcustomplot.h

FORMS += \
    titlewidget.ui \
    hpm_widget.ui \
    environmentwidget.ui \
    modelwidget.ui \
    simulationwidget.ui \
    hpmsettingwidget.ui

# Default rules for deployment.
include($$PWD/occ/occ.pri)
include($$PWD/Gmsh/gmsh.pri)
include($$[QT_INSTALL_PREFIX]/../Src/qttools/src/shared/qtpropertybrowser/qtpropertybrowser.pri)
include($$PWD/SARibbon-master/SARibbonBar.pri)
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#RESOURCES += \
#    res.qrc

RESOURCES += \
    res.qrc
