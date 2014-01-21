#-------------------------------------------------
#
# Project created by QtCreator 2013-10-20T21:10:58
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestQT
#CONFIG += console
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    graphwidget.cpp \
    edge.cpp \
    node.cpp \
    helper.cpp \
    expandcoloringalgorithm.cpp \
    nocolorexception.cpp

HEADERS  += mainwindow.h \
    graphwidget.h \
    edge.h \
    node.h \
    helper.h \
    expandcoloringalgorithm.h \
    nocolorexception.h

FORMS    += mainwindow.ui

RESOURCES += \
    ColorGraph.qrc

win32: LIBS += -L"C:/Program Files/CGAL-4.3/build/lib/" -lCGAL-vc100-mt-4.3
win32: LIBS += -L"C:/Program Files/CGAL-4.3/auxiliary/gmp/lib/"  -llibgmp-10
win32: LIBS += -LE:/boost_1_54_0/lib32-msvc-10.0/ -lboost_system-vc100-mt-gd-1_54
win32: LIBS += -LE:/boost_1_54_0/lib32-msvc-10.0/ -lboost_thread-vc100-mt-gd-1_54

INCLUDEPATH += C:/Program\ Files/CGAL-4.3/build/include
INCLUDEPATH += C:/Program\ Files/CGAL-4.3/auxiliary/gmp/include
INCLUDEPATH += E:/boost_1_54_0
