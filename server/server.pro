TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += thread

SOURCES += main.cpp \
    rgbled.cpp \
    fifopair.cpp \
    server.cpp \
    ledprotocolhelper.cpp \
    rqprocessor.cpp \
    args.cpp

HEADERS += \
    rgbled.h \
    irgbled.h \
    iblockingiochannel.h \
    fifopair.h \
    iserver.h \
    server.h \
    ledprotocolhelper.h \
    rqprocessor.h \
    irqprocessor.h \
    args.h \
    clientproducer.h

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

