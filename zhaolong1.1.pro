QT       += core gui
QT       += charts
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    cableselectdialog.cpp \
    occview.cpp \
    modeltree.cpp \
    solvercable.cpp \
    occread.cpp \
    chartwidget.cpp \
    qcustomplot.cpp

HEADERS += \
    mainwindow.h \
    cableselectdialog.h \
    occview.h \
    modeltree.h \
    solvercable.h \
    occread.h \
    chartwidget.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui \
    cableselectdialog.ui \
    occview.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    src.qrc

include($$PWD/osg/osg.pri)
include($$PWD/osgqt/osgqt.pri)
include($$PWD/occ/occ.pri)


INCLUDEPATH += $$quote(D:/ProgramFiles/MATLAB/R2021b/extern/include)
INCLUDEPATH += $$quote(D:/ProgramFiles/MATLAB/R2021b/extern/include/Win64)
UI_DIR=./UI
# 用到的MATLAB 的.lib库文件 及其搜索路径
INCLUDEPATH += $$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft)
DEPENDPATH += $$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft)

win32: LIBS += -L$$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft) -llibmex
win32: LIBS += -L$$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft) -llibmx
win32: LIBS += -L$$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft) -llibmat
win32: LIBS += -L$$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft) -llibeng
win32: LIBS += -L$$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft) -lmclmcr
win32: LIBS += -L$$quote(D:/ProgramFiles/MATLAB/R2021b/extern/lib/win64/microsoft) -lmclmcrrt



win32: LIBS += -L$$PWD/matlab/ -lfar_field_two_cables_function
win32: LIBS += -L$$PWD/matlab/ -lcascade_cable_and_connector_function
win32: LIBS += -L$$PWD/matlab/ -lTWP_far_filed_function
win32: LIBS += -L$$PWD/matlab/ -lTBTWPfunction
win32: LIBS += -L$$PWD/matlab/ -lzhaolong_cableFunction

INCLUDEPATH += $$PWD/matlab
DEPENDPATH += $$PWD/matlab

DISTFILES +=
