#include "display.h"
#include "untils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand(time(NULL));
    start_curses();
    if (has_colors() == FALSE) {
        printf("has colors : false");
        return -1;
    }

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
