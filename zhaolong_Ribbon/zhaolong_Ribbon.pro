#-------------------------------------------------
#
# Project created by QtCreator 2022-11-01T13:06:37
#
#-------------------------------------------------

QT       += core gui axcontainer sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = zhaolong_Ribbon
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
    contentwidget.cpp \
    recordwidget.cpp \
    occview.cpp \
    cable.cpp \
    highspeedcable.cpp \
    chartwidget.cpp \
    qcustomplot.cpp \
    ExcelBase.cpp \
    parameterwidget.cpp

HEADERS += \
        mainwindow.h \
    contentwidget.h \
    recordwidget.h \
    occview.h \
    cable.h \
    highspeedcable.h \
    chartwidget.h \
    qcustomplot.h \
    ExcelBase.h \
    parameterwidget.h

FORMS += \
    recordwidget.ui \
    contentwidget.ui \
    parameterwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
include($$PWD/SARibbon-master/SARibbonBar.pri)
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


RESOURCES += \
    resource.qrc

win32: LIBS += -L$$PWD/matlab/ -lzhaolongFunction

INCLUDEPATH += $$PWD/matlab
DEPENDPATH += $$PWD/matlab

INCLUDEPATH += $$PWD/components/

RESOURCES += \
    components/resources.qrc



win32:CONFIG(release, debug|release): LIBS += -L$$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/release/ -lcomponents
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/debug/ -lcomponents

INCLUDEPATH += $$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/debug
DEPENDPATH += $$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/debug

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/release/libcomponents.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/debug/libcomponents.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/release/components.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/components/build-components-Desktop_Qt_5_12_2_MinGW_64_bit-Debug/debug/components.lib
