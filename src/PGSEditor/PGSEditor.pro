#-------------------------------------------------
#
# Project created by QtCreator 2011-09-15T18:43:16
#
#-------------------------------------------------

QT       += core gui

TARGET = PGSEditor
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++0x

SOURCES += main.cpp\
        mainwindow.cpp \
    newscenewizard.cpp \
    controller.cpp \
    sceneexporter.cpp \
    renderingdockwidget.cpp \
    systemsdockwidget.cpp

HEADERS  += mainwindow.h \
    newscenewizard.h \
    controller.h \
    sceneexporter.h \
    renderingdockwidget.h \
    systemsdockwidget.h

FORMS    += mainwindow.ui \
    newscenewizard.ui \
    renderingdockwidget.ui \
    systemsdockwidget.ui
