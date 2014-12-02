CC = g++
SOURCES = main.cpp
HEADERS = main.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main


all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $< -o $@
