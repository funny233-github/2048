OBJECTS = 2048 test display-test
DEPENDENCY = untils.c display.c

CC = gcc
LDFLAGS = -lncurses

all:main test-all

main: main.c
	$(CC) $(LDFLAGS) main.c $(DEPENDENCY) -o 2048

test-all: test display-test

test: tests/test.c $(DEPENDENCY)
	$(CC) $(LDFLAGS) tests/test.c $(DEPENDENCY) -o test

display-test: tests/display-test.c $(DEPENDENCY)
	$(CC) $(LDFLAGS) tests/display-test.c $(DEPENDENCY) -o display-test

clean:
	rm -rf $(OBJECTS)
