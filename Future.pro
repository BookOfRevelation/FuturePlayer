#-------------------------------------------------
#
# Project created by QtCreator 2017-04-07T16:37:39
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Future
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    titlebar.cpp \
    oldbutton.cpp \
    aboutwindow.cpp \
    textbutton.cpp \
    warningdialog.cpp \
    fortunedialog.cpp \
    basedialog.cpp \
    centralplayer.cpp \
    playlist.cpp \
    infodialog.cpp \
    durationprogress.cpp \
    pureconfiguration.cpp

HEADERS  += mainwindow.h \
    titlebar.h \
    oldbutton.h \
    aboutwindow.h \
    textbutton.h \
    warningdialog.h \
    fortunedialog.h \
    basedialog.h \
    centralplayer.h \
    playlist.h \
    infodialog.h \
    durationprogress.h \
    pureconfiguration.h

RC_FILE = app.rc

RESOURCES += \
    res.qrc

DISTFILES += \
    app.rc
