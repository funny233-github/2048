SOURCES = main.c
OBJECTS = main
DEPENDENCY = untils.c display.c
TEST = test.c
TEST_OBJECT = test

CC = gcc
LDFLAGS = -lncurses

all:main test

main: $(SOURCES)
	$(CC) $(LDFLAGS) $(SOURCES) $(DEPENDENCY) -o $(OBJECTS)

test: $(TEST) $(DEPENDENCY)
	$(CC) $(LDFLAGS) $(TEST) $(DEPENDENCY) -o $(TEST_OBJECT)

clean:
	rm -rf $(OBJECTS)
	rm -rf $(TEST_OBJECT)
