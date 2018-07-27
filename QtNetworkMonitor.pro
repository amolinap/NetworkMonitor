#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T22:25:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtNetworkMonitor
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Monitor.cpp \
    HostIP.cpp

HEADERS  += mainwindow.h \
    Monitor.h \
    HostIP.h

FORMS    += mainwindow.ui \
    Monitor.ui \
    HostIP.ui
