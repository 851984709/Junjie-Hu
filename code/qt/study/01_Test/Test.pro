#-------------------------------------------------
#
# Project created by QtCreator 2018-01-12T22:30:42
#
#-------------------------------------------------

#模块
QT       += core gui

#高于4版本，添加 QT += widgets ， 为了兼容Qt4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#应用程序的名字
TARGET = Test

#指定makefile的类型，app
TEMPLATE = app

#源文件 .cpp
SOURCES += main.cpp\
        mywidget.cpp

#头文件 .h
HEADERS  += mywidget.h
