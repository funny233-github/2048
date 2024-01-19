#ifndef UNTILS
#define UNTILS

#include <stdbool.h>
#include <stdlib.h>

#define GAMECOLS 4
#define GAMERAWS 4

typedef enum direction{
    UP,
    DOWN,
    LEFT,
    RIGHT,
}direction;
extern int grid[GAMECOLS*GAMERAWS];
extern int stack[4];
extern int top;
extern int mergedlayer;
extern int score;
extern bool slid;
void push_and_merge_element(int value);
void reset_stack();
void print_stack();
int* get_element(direction direc,int i,int j);
void slide(direction direc);
void number_generator();

#endif
