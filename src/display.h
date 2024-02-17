#ifndef DISPLAY
#define DISPLAY

#include "untils.h"
#include <ncurses.h>

PUBLIC(void) start_curses();
PUBLIC(void) update_display();

#define BACKGROUND_COLOR COLOR_BLACK
#define BACKGROUND_PAIR 32

#endif
