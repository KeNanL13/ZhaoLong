DEFINES += OSG_DLL

LIBS += -L$$PWD/lib -llibosgViewer.dll
LIBS += -L$$PWD/lib -llibosgDB.dll
LIBS += -L$$PWD/lib -llibosgManipulator.dll
LIBS += -L$$PWD/lib -llibOpenThreads.dll
LIBS += -L$$PWD/lib -llibosgAnimation.dll
LIBS += -L$$PWD/lib -llibosg.dll
LIBS += -L$$PWD/lib -llibosgFX.dll
LIBS += -L$$PWD/lib -llibosgGA.dll
LIBS += -L$$PWD/lib -llibosgUtil.dll
LIBS += -L$$PWD/lib -llibosgWidget.dll
LIBS += -L$$PWD/lib -llibosgVolume.dll
LIBS += -L$$PWD/lib -llibosgUI.dll
LIBS += -L$$PWD/lib -llibosgPresentation.dll
LIBS += -L$$PWD/lib -llibosgShadow.dll
LIBS += -L$$PWD/lib -llibosgParticle.dll
LIBS += -L$$PWD/lib -llibosgTerrain.dll

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include
