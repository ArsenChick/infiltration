LIBS += -L$$PWD/external/SFML-2.5.1/lib

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Enemy.cpp \
        main.cpp

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-main -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-main-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += $$PWD/external/SFML-2.5.1/include
DEPENDPATH += $$PWD/external/SFML-2.5.1/include

HEADERS += \
    Enemy.h
