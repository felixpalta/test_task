CXX=g++
CXXFLAGS=-c -Wall -Wextra -Weffc++ -std=c++11 -pedantic \
                    -Wunreachable-code -Wshadow \
                    -Wold-style-cast -Wnon-virtual-dtor  \
                    -Woverloaded-virtual \
                    -Wenum-compare  \
                    -Wctor-dtor-privacy	\
                    -Wsign-conversion  \
                    -Wconversion

LDFLAGS=
SOURCES=$(wildcard *.cpp)
BINDIR=bin
OBJDIR=obj
OBJECTS=$(OBJDIR)/args.o $(OBJDIR)/fifopair.o $(OBJDIR)/ledprotocolhelper.o $(OBJDIR)/main.o $(OBJDIR)/rgbled.o $(OBJDIR)/rqprocessor.o $(OBJDIR)/server.o
TARGET=$(BINDIR)/server

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS)  -c $< -o $@

#.cpp.o:
#	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJDIR)/$(OBJECTS) $(BINDIR)/$(TARGET)

