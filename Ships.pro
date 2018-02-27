#-------------------------------------------------
#
# Project created by QtCreator 2017-11-10T13:24:40
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Ships
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
    dialogadddship.cpp \
    chooseredactmode.cpp \
    dialogchoosemode.cpp \
    dialogredactgraph.cpp \
    mainwindowredactvertex.cpp \
    mainwindowredactdatabase.cpp \
    dialogaddvertex.cpp \
    mainwindowredactedge.cpp \
    dialogaddedge.cpp \
    dialogmainuser.cpp \
    dialoguserresult.cpp \
    database.cpp \
    vertex.cpp \
    edge.cpp

HEADERS += \
    dialogaddship.h \
    chooseredactmode.h \
    dialogchoosemode.h \
    dialogredactgraph.h \
    mainwindowredactvertex.h \
    mainwindowredactdatabase.h \
    dialogaddvertex.h \
    dialogaddedge.h \
    mainwindowredactedge.h \
    dialogmainuser.h \
    dialoguserresult.h \
    database.h \
    vertex.h \
    edge.h

FORMS += \
    dialogaddship.ui \
    chooseredactmode.ui \
    dialogchoosemode.ui \
    dialogredactgraph.ui \
    mainwindowredactvertex.ui \
    mainwindowredactdatabase.ui \
    dialogaddvertex.ui \
    mainwindowredactedge.ui \
    dialogaddedge.ui \
    dialogmainuser.ui \
    dialoguserresult.ui

RESOURCES += \
    resources.qrc
