TARGET	= myths
SOURCES = src/
HEADERDIR = include/
LIBS	= $(shell sdl2-config --libs) -lSDL2_image
CXX	= g++
CXXFLAGS  = -g -Wall -Iinclude $(shell sdl2-config --cflags)
SHELL	= /bin/sh

.PHONY: default all clean

default: $(TARGET)
all: default


CXXFILES = $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
OBJECTS = $(patsubst %.cpp, %.o, $(wildcard $(SOURCES)*.cpp))

HEADERS = $(foreach dir,$(HEADERDIR),$(notdir $(wildcard $(dir)/*.hpp)))

%.o: %.cpp $(HEADERS)
	echo $<
	$(CXX) $(CXXFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f $(SOURCES)*.o
	-rm -f $(TARGET)
