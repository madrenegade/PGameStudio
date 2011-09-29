#-------------------------------------------------
#
# Project created by QtCreator 2011-09-15T18:43:16
#
#-------------------------------------------------

QT       += core gui opengl

TARGET = PGSEditor
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x -DDEBUG -DGCC

SOURCES += main.cpp\
        mainwindow.cpp \
    newscenewizard.cpp \
    controller.cpp \
    sceneexporter.cpp \
    renderingdockwidget.cpp \
    systemsdockwidget.cpp \
    singleviewwidget.cpp \
    renderingviewwidget.cpp \
    scene.cpp \
    assetimportwizard.cpp \
    multiviewwidget.cpp \
    assetimporter.cpp \
    scenedata.cpp \
    scenedockwidget.cpp \
    editorapplication.cpp

HEADERS  += mainwindow.h \
    newscenewizard.h \
    controller.h \
    sceneexporter.h \
    renderingdockwidget.h \
    systemsdockwidget.h \
    singleviewwidget.h \
    renderingviewwidget.h \
    scene.h \
    assetimportwizard.h \
    multiviewwidget.h \
    assetimporter.h \
    scenedata.h \
    scenedockwidget.h \
    mesh.h \
    scenenode.h \
    material.h \
    editorapplication.h

FORMS    += mainwindow.ui \
    newscenewizard.ui \
    renderingdockwidget.ui \
    systemsdockwidget.ui \
    singleviewwidget.ui \
    renderingviewwidget.ui \
    assetimportwizard.ui \
    multiviewwidget.ui \
    scenedockwidget.ui

unix:!macx:!symbian: LIBS += -L$$PWD/../../../../../../../usr/lib64/ -lassimp_d

INCLUDEPATH += $$PWD/../../../../../../../usr/lib64
DEPENDPATH += $$PWD/../../../../../../../usr/lib64

unix:!macx:!symbian: LIBS += -L$$PWD/../../bin/Debug/Linux/x86_64/ -lMath

INCLUDEPATH += $$PWD/../Math
DEPENDPATH += $$PWD/../Math

unix:!macx:!symbian: LIBS += -L$$PWD/../../bin/Debug/Linux/x86_64/ -lUtilities

INCLUDEPATH += $$PWD/../Utilities
DEPENDPATH += $$PWD/../Utilities

unix:!macx:!symbian: LIBS += -L$$PWD/../../bin/Debug/Linux/x86_64/ -lCore

INCLUDEPATH += $$PWD/../Core
DEPENDPATH += $$PWD/../Core

unix:!macx:!symbian: LIBS += -lglog

unix:!macx:!symbian: LIBS += -L$$PWD/../../bin/Debug/Linux/x86_64/ -lStackTrace

INCLUDEPATH += $$PWD/../StackTrace
DEPENDPATH += $$PWD/../StackTrace

unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../../bin/Debug/Linux/x86_64/libStackTrace.a

unix:!macx:!symbian: LIBS += -lboost_system-mt

unix:!macx:!symbian: LIBS += -ltbb_debug
