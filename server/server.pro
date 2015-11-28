TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ledrqhandler.cpp \
    abstractrqhandler.cpp \
    ledmanager.cpp \
    rgbled.cpp \
    ledserver.cpp

HEADERS += \
    abstractrqhandler.h \
    ledrqhandler.h \
    rgbled.h \
    irgbled.h \
    ledmanager.h \
    iledmanager.h \
    ledserver.h \
    iblockingiochannel.h

*g++*{
QMAKE_CXXFLAGS +=   -Weffc++ -std=c++11 -pedantic -Wall -Wextra \
                    -Wunreachable-code -Wshadow \
                    -Wold-style-cast -Wnon-virtual-dtor  \
                    -Woverloaded-virtual \
                    -Wenum-compare  \
                                        #OFF for QT
                    -Wctor-dtor-privacy	\
                    -Wsign-conversion  \
                    -Wconversion \
}

