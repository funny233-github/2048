#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "untils.h"

int grid[GAMECOLS*GAMERAWS] = {0};

int stack[4] = {0};
int top = -1;
int mergedlayer = -1;
int score = 0;

bool slid = false;

bool 
is_full(){

    for (int i = 0; i < 16; i++)
        if (grid[i] == 0) return false;

    return true;
}

void 
number_generator(){
    if (is_full())
        return;

    while (true){
        int pos = rand()%16;
        if (grid[pos] == 0){
            grid[pos] = 2 + rand()%2*2;
            break;
        }
    }
}

void 
push_and_merge_element(int value){
    if (value == 0) return;

    if (top == -1 || stack[top] != value || mergedlayer >= top){
        stack[++top] = value;
        return;
    }

    stack[top] += value;
    score += stack[top];
    mergedlayer = top;
}

void 
reset_stack(){
    top = -1;
    mergedlayer = -1;
    for (int i = 0;i < 4; stack[i++] = 0);
}

void 
print_stack(){
    printf("\n");
    for (int i = 0;i < 4; printf("%d--",stack[i++]));
    printf("\nmergedlayer:%d\ntop:%d\n\n",mergedlayer,top);
}

int* 
get_element(direction direc,int i,int j){
    switch (direc) {
    case UP:
        return &grid[j*GAMERAWS+i]; 
    case DOWN:
        return &grid[(3-j)*GAMERAWS+i];
    case LEFT:
        return &grid[i*GAMERAWS+j];
    case RIGHT:
        return &grid[i*GAMERAWS+(3-j)];
    }
}

void 
slide(direction direc){
    for (int i = 0;i < 4;i++){
        int before[4];
        for (int j = 0;j < 4;j++)
            before[j] = *get_element(direc,i,j);

        for (int j = 0;j < 4;j++)
            push_and_merge_element(*get_element(direc,i,j));

        for (int j = 0;j < 4;j++){
            *get_element(direc,i,j) = stack[j]; 
            if (stack[j] != before[j])
                slid = true;
        }

        reset_stack();
    }
}

