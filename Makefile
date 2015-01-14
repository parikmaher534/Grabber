PHONY: clean all

prefix=/usr/local
exec_prefix=${prefix}
libdir=${exec_prefix}/lib

CC = g++
CFLAGS = -lc++ -Wall -Wextra -pedantic-errors 
LDFLAGS = -L${libdir} -lgumbo
SOURCES = main.cpp
HEADERS = main.h
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = main


clean:
	rm -f *.o main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@
