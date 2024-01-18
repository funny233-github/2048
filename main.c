#include <ncurses.h>
#include <time.h>
#include "untils.h"

void start_curses(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}


void update_windows_and_state(){

    clear();
    mvprintw(0,0,"state:%d",state);
    refresh();

    WINDOW * windows[16];
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            windows[i*GAMERAWS+j] = newwin(10,20,i*10+1,j*20+1);
            box(windows[i*GAMERAWS+j],0,0);

            if (numbers[i*GAMERAWS+j] != 0)
                mvwprintw(windows[i*GAMERAWS+j],4,9,"%d",numbers[i*4+j]);

            wrefresh(windows[i*GAMERAWS+j]);
            wclear(windows[i*GAMERAWS+j]);
        }
    }
}

int main(){
    srand(time(NULL));
    start_curses();

    refresh();
    number_generator();
    update_windows_and_state();

    while (true){
        char key = getch();
        if (key == 'q')
            break;
        switch (key) {
            case 'w':
                slide_up();
                break;
            case 's':
                slide_down();
                break;
            case 'a':
                slide_left();
                break;
            case 'd':
                slide_right();
                break;
            default:
                continue;
                break;
        }
        number_generator();
        update_windows_and_state();
    }
    endwin();
}
