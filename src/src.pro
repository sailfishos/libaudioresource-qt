TEMPLATE = lib
TARGET = audioresource-qt
VERSION = 2.0.0

# No need to link against QtGui for this library
QT -= gui

# Symbol visibility
DEFINES += AUDIORESOURCEQT_LIBRARY
QMAKE_CXXFLAGS += -fvisibility=hidden -fvisibility-inlines-hidden

# Library requirements
CONFIG += link_pkgconfig
PKGCONFIG += audioresource

# Sources
DEPENDPATH += . ../include
INCLUDEPATH += . ../include
SOURCES += audioresource-qt.cpp
HEADERS += ../include/audioresource-qt.h

# Installation
target.path = $$[QT_INSTALL_LIBS]
header.path = $$PREFIX/include/audioresource-qt/
header.files = ../include/audioresource-qt.h ../include/AudioResourceQt
INSTALLS += target header

# pkg-config configuration file
CONFIG += create_pc create_prl no_install_prl
QMAKE_PKGCONFIG_NAME = audioresource-qt
QMAKE_PKGCONFIG_DESCRIPTION = Nemo Mobile Audio Resource API (Qt bindings)
QMAKE_PKGCONFIG_LIBDIR = $$target.path
QMAKE_PKGCONFIG_INCDIR = $$header.path
QMAKE_PKGCONFIG_DESTDIR = pkgconfig
