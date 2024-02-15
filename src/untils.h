#ifndef UNTILS
#define UNTILS

#include <stdbool.h>

#define PUBLIC(type) type

#define GAMECOLS 4
#define GAMERAWS 4
#define N_GRID GAMECOLS *GAMERAWS

typedef enum direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
} direction;

typedef enum error_type {
    NO_ERROR,
    NORMAL_ERROR,
    INDEX_ERROR,
    GENERATOR_ERROR,
    SLIDE_ERROR,
} error_type;

PUBLIC(bool) gameRaiseError(error_type error);
PUBLIC(bool) detectError();

typedef struct data {
    int grid[N_GRID];
    int score;
    bool slid;
    error_type error;
} data;

/* INDEX(i,j)
 * #--> j
 * |
 * v
 * i
 */

#define INDEX(i, j)                                                            \
    ((i >= 0 && j >= 0 && i <= GAMERAWS && j <= GAMECOLS)                      \
         ? ((i)*GAMECOLS + (j))                                                \
         : (gameRaiseError(INDEX_ERROR)))

// i use to scan, j use to buffer
#define INDEX_BY(direc, i, j)                                                  \
    ((direc == UP || direc == DOWN)                                            \
         ? ((direc == UP) ? (INDEX(j, i)) : (INDEX(3 - j, i)))                 \
         : ((direc == LEFT) ? (INDEX(i, j)) : (INDEX(i, 3 - j))))

#define MAX(a, b) ((a >= b) ? a : b)
#define MAX_COL_RAW MAX(GAMECOLS, GAMERAWS)

PUBLIC(int *) getGameGrid();
PUBLIC(int) getGameScore();
PUBLIC(bool) getGameSlid();
#define GAME_GRID getGameGrid()
#define GAME_SCORE getGameScore()
#define GAME_SLID getGameSlid()

PUBLIC(bool) slide(direction direc);
PUBLIC(bool) number_generator();

#endif
