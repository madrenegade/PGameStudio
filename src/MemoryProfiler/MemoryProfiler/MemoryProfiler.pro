#-------------------------------------------------
#
# Project created by QtCreator 2011-09-06T14:12:16
#
#-------------------------------------------------

QT       += core gui

TARGET = MemoryProfiler
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    serverthread.cpp \
    samplenode.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    serverthread.h \
    samplenode.h

FORMS    += mainwindow.ui \
    aboutdialog.ui

unix:!macx:!symbian: LIBS += -L$$PWD/../../../bin/Debug/Linux/x86_64/ -lmemprof

INCLUDEPATH += $$PWD/../memprof
DEPENDPATH += $$PWD/../memprof

unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../../../bin/Debug/Linux/x86_64/libmemprof.a

unix:!macx:!symbian: LIBS += -lgcov

unix:!macx:!symbian: LIBS += -lglog

unix:!macx:!symbian: LIBS += -lboost_system

INCLUDEPATH += $$PWD/
DEPENDPATH += $$PWD/

unix:!macx:!symbian: LIBS += -lboost_serialization

INCLUDEPATH += $$PWD/../../StackTrace
DEPENDPATH += $$PWD/../../StackTrace

unix:!macx:!symbian: LIBS += -L$$PWD/../../../bin/Debug/Linux/x86_64/ -lStackTrace
unix:!macx:!symbian: PRE_TARGETDEPS += $$PWD/../../../bin/Debug/Linux/x86_64/libStackTrace.a

unix:!macx:!symbian: LIBS += -lunwind-x86_64
unix:!macx:!symbian: LIBS += -lunwind
