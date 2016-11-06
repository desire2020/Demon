#-------------------------------------------------
#
# Project created by QtCreator 2016-10-19T23:22:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demon
TEMPLATE = app


SOURCES += main.cpp\
        displaywindow.cpp \
    jsonparser.cpp

HEADERS  += displaywindow.hpp \
    jsonparser.hpp

FORMS    += displaywindow.ui

DISTFILES += \
    layout.qss

RESOURCES += \
    images.qrc
