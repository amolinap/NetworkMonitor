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

INCLUDEPATH += src/

SOURCES += main.cpp\
    src/mainwindow.cpp \
    src/Monitor.cpp \
    src/HostIP.cpp

HEADERS  += src/mainwindow.h \
    src/Monitor.h \
    src/HostIP.h

FORMS    += src/mainwindow.ui \
    src/Monitor.ui \
    src/HostIP.ui
