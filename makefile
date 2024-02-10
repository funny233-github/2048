OBJECTS = 2048 test display-test
DEPENDENCY = untils.c display.c

CC = gcc
LDFLAGS = -lncurses

all:main test-all

main: main.c
	$(CC) main.c $(DEPENDENCY) -o 2048 $(LDFLAGS)

test-all: test display-test

test: tests/test.c $(DEPENDENCY)
	$(CC) tests/test.c $(DEPENDENCY) -o test $(LDFLAGS)

display-test: tests/display-test.c $(DEPENDENCY)
	$(CC) tests/display-test.c $(DEPENDENCY) -o display-test $(LDFLAGS)

clean:
	rm -rf $(OBJECTS)
