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
BINDIR=$(BIN_DIR)
OBJDIR=$(OBJ_DIR)
OBJECTS := $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cpp=.o)))
TARGET=$(BINDIR)/server

all: $(SOURCES) $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(LDFLAGS) $(OBJECTS) -o $@

$(OBJECTS): $(OBJDIR)/%.o: %.cpp
	$(CXX) $(CXXFLAGS)  -c $< -o $@

#.cpp.o:
#	$(CXX) $(CXXFLAGS) $< -o $@

clean:
	rm -rf $(OBJECTS) $(TARGET)

