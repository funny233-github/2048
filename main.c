#include <ncurses.h>
#include <time.h>
#include "untils.h"
#include "display.h"

int main(){
    srand(time(NULL));
    start_curses();

    refresh();
    number_generator();
    update_windows_and_score();

    while (true){
        char key = getch();
        if (key == 'q')
            break;
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
            default:
                continue;
                break;
        }
        if (slid){
            slid = false;
            number_generator();
        }
        update_windows_and_score();
    }
    endwin();
}
