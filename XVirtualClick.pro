#-------------------------------------------------
#
# Project created by QtCreator 2013-08-27T14:57:00
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XVirtualClick
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    xvirtualclick.cpp \
    myapplication.cpp \
    aboutdialog.cpp

HEADERS  += mainwindow.h \
    xvirtualclick.h \
    myapplication.h \
    aboutdialog.h

RESOURCES += \
    rsc.qrc

RC_FILE  += \
    info.rc

OTHER_FILES += \
    info.rc
