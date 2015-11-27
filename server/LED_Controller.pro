TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ledmanager.cpp \
    ledserver.cpp \
    rgbled.cpp

include(deployment.pri)
qtcAddDeployment()

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

HEADERS += \
    iledmanager.h \
    ledmanager.h \
    ledserver.h \
    irgbled.h \
    rgbled.h

