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
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
