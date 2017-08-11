TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    qdbmp.c

HEADERS += \
    qdbmp.h

LIBS += -lesi
