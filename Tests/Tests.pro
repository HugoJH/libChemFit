#-------------------------------------------------
#
# Project created by QtCreator 2018-02-12T09:03:54
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = UnitTests
CONFIG   += console c++11
CONFIG   -= app_bundle

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

LIBS +=  "$$shadowed($$PWD)/../source/libchemFit.so.1.0.0" -L"$$shadowed($$PWD)/../source/"

SOURCES += \
        main.cpp \
        suite.cpp \
    DoubleExponentialTest.cpp \
    SingleExponentialTest.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"
INCLUDEPATH += $$PWD/../source
DEPENDPATH += $$PWD/../source

HEADERS += \
    suite.h \
    DoubleExponentialTest.h \
    SingleExponentialTest.h
