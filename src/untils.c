#include "untils.h"
#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

static data gamedata = {{0}, 0, 0, 0};

PUBLIC(int *) getGameGrid() { return gamedata.grid; }

PUBLIC(int) getGameScore() { return gamedata.score; }

PUBLIC(bool) getGameSlid() { return gamedata.slid; }

PUBLIC(bool) gameRaiseError(error_type error) {
    if (error > SLIDE_ERROR)
        goto fail;

    gamedata.error = error;
    return true;
fail:
    gamedata.error = NORMAL_ERROR;
    return false;
}

PUBLIC(bool) detectError() {
    switch (gamedata.error) {
    case NO_ERROR:
        return false;
    case NORMAL_ERROR:
        endwin();
        printf("normal error");
        return true;
    case INDEX_ERROR:
        endwin();
        printf("index error");
        return true;
    case GENERATOR_ERROR:
        endwin();
        printf("generator error");
        return true;
    case SLIDE_ERROR:
        endwin();
        printf("slid error");
        return true;
    }
    return false;
}

PUBLIC(bool) number_generator() {
    int *buffer[N_GRID];
    int top = 0;

    for (int i = 0; i < N_GRID; i++)
        if (gamedata.grid[i] == 0)
            buffer[top++] = &gamedata.grid[i];

    if (top == 0)
        goto fail;

    *buffer[rand() % (top)] = 2 + rand() % 2 * 2;
    return true;
fail:
    gameRaiseError(GENERATOR_ERROR);
    return false;
}

PUBLIC(bool) slide(direction direc) {
    if (direc != UP && direc != DOWN && direc != LEFT && direc != RIGHT)
        goto fail;

    gamedata.slid = false;
    for (int i = 0; i < ((direc == UP || direc == DOWN) ? GAMECOLS : GAMERAWS);
         i++) {
        int buffer[MAX_COL_RAW], before[MAX_COL_RAW];
        int top = 0, skip = -1;
        memset(buffer, 0, sizeof(buffer));
        for (int j = 0;
             j < ((direc == UP || direc == DOWN) ? GAMERAWS : GAMECOLS); j++)
            before[j] = gamedata.grid[INDEX_BY(direc, i, j)];

        for (int j = 0;
             j < ((direc == UP || direc == DOWN) ? GAMERAWS : GAMECOLS); j++) {
            int value = gamedata.grid[INDEX_BY(direc, i, j)];
            if (value == 0)
                continue;
            if (top == 0 || buffer[top - 1] != value || top - 1 <= skip) {
                buffer[top++] = value;
                continue;
            }
            skip = top - 1;
            buffer[skip] += value;
            gamedata.score += value;
        }

        for (int j = 0;
             j < ((direc == UP || direc == DOWN) ? GAMERAWS : GAMECOLS); j++) {
            gamedata.grid[INDEX_BY(direc, i, j)] = buffer[j];
            if (buffer[j] != before[j])
                gamedata.slid = true;
        }
    }
    return true;
fail:
    gameRaiseError(GENERATOR_ERROR);
    return false;
}
