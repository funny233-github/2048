#ifndef UNTILS
#define UNTILS

#include <stdbool.h>
#include <stdlib.h>

#define GAMECOLS 4
#define GAMERAWS 4

extern int numbers[GAMECOLS*GAMERAWS];
extern int stack[4];
extern int top;
extern int mergedlayer;
extern int state;
void push_and_merge_element(int value);
void reset_stack();
void print_stack();
void slide_up();
void slide_down();
void slide_left();
void slide_right();
void number_generator();

#endif
