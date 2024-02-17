#include "display.h"
#include "mainConfigure.h"
#include "untils.h"
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char *argv[]) {
    // print version info
    if (argc == 2 && strncmp(argv[1], "-v", sizeof("-v")) == 0) {
        printf("version:%d.%d", Project2048_VERSION_MAJOR,
               Project2048_VERSION_MINOR);
        return 0;
    }

    srand(time(NULL));
    start_curses();

    refresh();
    number_generator();
    update_display();

    while (true) {
        char key = getch();
        switch (key) {
        case 'w':
            slide(UP);
            break;
        case 's':
            slide(DOWN);
            break;
        case 'a':
            slide(LEFT);
            break;
        case 'd':
            slide(RIGHT);
            break;
        case 'q':
            gameRaiseError(NORMAL_ERROR);
            break;
        default:
            continue;
            break;
        }
        if (detectError())
            break;
        if (!GAME_SLID) {
            continue;
        }
        number_generator();
        update_display();
        if (detectError())
            break;
    }
}
