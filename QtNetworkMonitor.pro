#-------------------------------------------------
#
# Project created by QtCreator 2016-12-10T22:25:25
#
#-------------------------------------------------

QT       += core gui network xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkMonitor
TEMPLATE = app
BASEDIR = $$PWD
TARGETDIR = $$OUT_PWD
BUILDDIR = $$TARGETDIR/build
OBJECTS_DIR = $$BUILDDIR/obj
MOC_DIR = $$BUILDDIR/moc
UI_DIR = $$BUILDDIR/generated

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
