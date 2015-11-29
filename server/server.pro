TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    rgbled.cpp \
    fifopair.cpp \
    server.cpp \
    rqhandlerset.cpp \
    rqhandler.cpp \
    ledprotocolhelper.cpp

HEADERS += \
    rgbled.h \
    irgbled.h \
    iblockingiochannel.h \
    fifopair.h \
    iserver.h \
    server.h \
    irqhandler.h \
    irqhandlerset.h \
    rqhandlerset.h \
    rqhandler.h \
    ledprotocolhelper.h

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

