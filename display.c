#include <ncurses.h>
#include "untils.h"

void start_curses(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}


void update_windows_and_score(){

    clear();
    mvprintw(0,0,"score:%d",score);
    refresh();

    WINDOW * windows[16];
    for (int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            windows[i*GAMERAWS+j] = newwin(10,20,i*10+1,j*20+1);
            box(windows[i*GAMERAWS+j],0,0);

            if (grid[i*GAMERAWS+j] != 0)
                mvwprintw(windows[i*GAMERAWS+j],4,9,"%d",grid[i*4+j]);

            wrefresh(windows[i*GAMERAWS+j]);
            wclear(windows[i*GAMERAWS+j]);
        }
    }
}
