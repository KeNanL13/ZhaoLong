#-------------------------------------------------
#
# Project created by QtCreator 2023-02-13T20:31:39
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MyConponent
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
    framelesswidget.cpp \
    sidebar.cpp \
    pushbutton.cpp \
    pagewidget.cpp \
    slider.cpp \
    lineeditwidget.cpp \
    roundedcornerwidget.cpp \
    combinationwidget.cpp \
    aboutpage.cpp \
    materialcomponent.cpp \
    combobox.cpp \
    occview.cpp

HEADERS += \
        mainwindow.h \
    framelesswidget.h \
    sidebar.h \
    pushbutton.h \
    pagewidget.h \
    slider.h \
    lineeditwidget.h \
    roundedcornerwidget.h \
    combinationwidget.h \
    aboutpage.h \
    materialcomponent.h \
    combobox.h \
    occview.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

include($$PWD/occ/occ.pri)
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

