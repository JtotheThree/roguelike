TARGET = roguelike
LIBS = -lm $(shell sdl2-config --libs) -lSDL2_image
CC = g++
CFLAGS = -g -Wall -std=c++0x $(shell sdl2-config --cflags)

.PHONY: default all clean

default: $(TARGET)
all: default

OBJECTS = $(patsubst %.cc, %.o, $(wildcard src/*.cc))
HEADERS = $(wildcard *.h)

%.o: %.cc $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

.PRECIOUS: $(TARGET) $(OBJECTS)

$(TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -Wall $(LIBS) -o $@

clean:
	-rm -f src/*.o
	-rm -f $(TARGET)
