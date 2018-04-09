#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T14:49:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Resize
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    editdialog.cpp \
    ../../../MyCV/mycv.cpp \
    ../../../MyCV/myimage.cpp \
    ../../../MyCV/mymat.cpp \
    ../../../MyCV/mymat2.cpp \
    ../../../MyCV/mymath.cpp \
    ../../../MyCV/mycomplexnumber.cpp \
    ../../../MyCV/mykernel2.cpp \
    ../../../MyCV/mykernel3.cpp \
    ../../../MyCV/mymat3.cpp

HEADERS += \
        mainwindow.h \
    editdialog.h \
    ../../../MyCV/mycv.h \
    ../../../MyCV/myimage.h \
    ../../../MyCV/mymat.h \
    ../../../MyCV/mymat2.h \
    ../../../MyCV/mymath.h \
    ../../../MyCV/mycomplexnumber.h \
    ../../../MyCV/mykernel2.h \
    ../../../MyCV/mykernel3.h \
    ../../../MyCV/mymat3.h
