#include "display.h"

PUBLIC(void) start_curses() {
    initscr();
    cbreak();
    noecho();
    curs_set(0);
    start_color();

    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    init_pair(5, COLOR_RED, COLOR_BLACK);
    init_pair(6, COLOR_RED, COLOR_BLACK);
    init_pair(7, COLOR_YELLOW, COLOR_BLACK);
    init_pair(8, COLOR_YELLOW, COLOR_BLACK);
    init_pair(9, COLOR_YELLOW, COLOR_BLACK);
    init_pair(10, COLOR_YELLOW, COLOR_BLACK);
    init_pair(11, COLOR_YELLOW, COLOR_BLACK);
    init_pair(12, COLOR_YELLOW, COLOR_BLACK);
    init_pair(13, COLOR_YELLOW, COLOR_BLACK);
    init_pair(14, COLOR_YELLOW, COLOR_BLACK);
    init_pair(15, COLOR_YELLOW, COLOR_BLACK);
}

PUBLIC(void) update_display() {

    clear();
    mvprintw(0, 0, "score:%d", GAME_SCORE);
    refresh();

    WINDOW *windows[16];
    for (int i = 0; i < GAMERAWS; i++)
        for (int j = 0; j < GAMECOLS; j++) {
            int color = 0;
            int numcache = GAME_GRID[INDEX(i, j)];

            windows[INDEX(i, j)] = newwin(10, 20, i * 10 + 1, j * 20 + 1);

            while (numcache != 0) {
                numcache /= 2;
                color += 1;
            }

            wattron(windows[INDEX(i, j)], COLOR_PAIR(color));
            box(windows[INDEX(i, j)], 0, 0);

            if (GAME_GRID[INDEX(i, j)] != 0)
                mvwprintw(windows[INDEX(i, j)], 4, 9, "%d",
                          GAME_GRID[INDEX(i, j)]);

            wattroff(windows[INDEX(i, j)], COLOR_PAIR(color));
            wrefresh(windows[INDEX(i, j)]);
            wclear(windows[INDEX(i, j)]);
        }
}
