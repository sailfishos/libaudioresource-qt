TARGET = audioresource-qt-example

QT -= gui
QT += multimedia

SOURCES += main.cpp

SOURCES += player.cpp
HEADERS += player.h

INCLUDEPATH += . ../include
DEPENDPATH += . ../include

LIBS += -L../src -laudioresource-qt

target.path = /usr/bin
INSTALLS += target
