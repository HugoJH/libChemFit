#-------------------------------------------------
#
# Project created by QtCreator 2018-02-12T09:40:21
#
#-------------------------------------------------

QT       -= gui

TARGET = chemFit
TEMPLATE = lib
CONFIG += c++11
DEFINES += SOURCE_LIBRARY

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix:LIBS += $$system(python$${PYTHON_VERSION}-config --libs)
unix:QMAKE_CXXFLAGS += $$system(python$${PYTHON_VERSION}-config --includes) -D_hypot=hypot
win32:LIBS += C:/Python27/libs/python27.lib -lqwt

SOURCES += \
    ChemFit.cpp \
    SingleExponential.cpp \
    mathOps.cpp \
    PythonInterface.cpp \
    DoubleExponential.cpp

HEADERS += \
    ChemFit.h \
    SingleExponential.h \
    ChemFit_global.h \
    mathOps.h \
    PythonInterface.h \
    DoubleExponential.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
