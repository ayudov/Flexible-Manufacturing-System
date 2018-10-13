#-------------------------------------------------
#
# Project created by QtCreator 2018-10-09T12:29:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = FlexManSys
TEMPLATE = app

CONFIG+=c++11
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp\
        mainwindow.cpp \
    Operation.cpp \
    Billet.cpp \
    addbillet.cpp \
    matrix.cpp

HEADERS  += mainwindow.h \
    Billet.h \
    Operation.h \
    addbillet.h \
    matrix.h

FORMS    += mainwindow.ui \
    addbillet.ui \
    matrix.ui

RESOURCES += \
    resources.qrc
