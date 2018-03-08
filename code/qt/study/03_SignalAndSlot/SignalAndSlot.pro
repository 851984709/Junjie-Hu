#-------------------------------------------------
#
# Project created by QtCreator 2018-01-13T11:18:20
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SignalAndSlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwidget.cpp \
    subwidget.cpp

HEADERS  += mainwidget.h \
    subwidget.h

CONFIG += C++11 #Lamda表达式需要
