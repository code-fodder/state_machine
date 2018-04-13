TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    state_machine.cpp \
    state_start.cpp \
    state_middle.cpp

HEADERS += \
    state_machine.h \
    state_start.h \
    state_middle.h

