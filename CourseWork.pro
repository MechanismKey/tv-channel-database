#-------------------------------------------------
#
# Project created by QtCreator 2017-06-01T17:49:55
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += C++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CourseWork
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    employee.cpp \
    passport.cpp \
    manager.cpp \
    authorization.cpp \
    database.cpp

HEADERS  += mainwindow.h \
    employee.h \
    passport.h \
    manager.h \
    authorization.h \
    database.h

FORMS    += mainwindow.ui \
    manager.ui \
    authorization.ui
