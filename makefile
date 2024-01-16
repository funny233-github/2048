SOURCES = main.c
OBJECTS = main

CC = gcc
LDFLAGS = -lncurses

all: main

main: $(SOURCES)
	$(CC) $(LDFLAGS) $(SOURCES) -o $(OBJECTS)

clean:
	rm -rf $(OBJECTS)