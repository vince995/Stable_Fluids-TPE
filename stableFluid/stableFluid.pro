TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    vecfield.cpp \
    fluid.cpp \
    vector.cpp \
    scalarfield.cpp

HEADERS += \
    vecfield.h \
    fluid.h \
    vector.h \
    scalarfield.h


CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics  -lsfml-network -lsfml-window -lsfml-system

CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics  -lsfml-network -lsfml-window -lsfml-system

