#-------------------------------------------------
#
# Project created by QtCreator 2019-09-13T13:33:27
#
#-------------------------------------------------

QT       += core gui widgets
QT       += widgets

TARGET = poocman
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

CONFIG += c++11

SOURCES += \
    animationsprite.cpp \
    blinky.cpp \
    button.cpp \
    clyde.cpp \
    gameoverscene.cpp \
    gamescene.cpp \
    ghost.cpp \
    instrscene.cpp \
        main.cpp \
        mainwindow.cpp \
    maze.cpp \
    mazegenerator.cpp \
    menuscene.cpp \
    pacdot.cpp \
    poocman.cpp \
    timerproxy.cpp

HEADERS += \
    animationsprite.h \
    blinky.h \
    button.h \
    clyde.h \
    commonInfo.h \
    gameoverscene.h \
    gamescene.h \
    ghost.h \
    instrscene.h \
        mainwindow.h \
    maze.h \
    mazegenerator.h \
    menuscene.h \
    pacdot.h \
    poocman.h \
    timerproxy.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    resource/blinky_sprite.png \
    resource/ghost.json \
    resource/pacdot.json \
    resource/pacman_sprite.png

RESOURCES += \
    resources.qrc
