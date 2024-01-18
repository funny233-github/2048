#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define GAMERAWS 4
#define GAMECOLS 4
int numbers[GAMECOLS*GAMERAWS] = {0};

int stack[4] = {0};
int top = -1;
int mergedlayer = -1;
int state = 0;

bool is_full(){
    for (int i = 0; i < 16; i++){
        if (numbers[i] == 0)
            return false;
    }
    return true;
}

void number_generator(){
    if (is_full())
        return;

    while (true){
        int pos = rand()%16;
        if (numbers[pos] == 0){
            numbers[pos] = 2 + rand()%2*2;
            break;
        }
    }
}

void push_and_merge_element(int value){
    if (value == 0)
        return;

    if (top == -1 || stack[top] != value || mergedlayer >= top){
        stack[++top] = value;
        return;
    }

    stack[top] += value;
    state += stack[top];
    mergedlayer = top;
}

void reset_stack(){
    top = -1;
    mergedlayer = -1;
    for (int i = 0;i < 4; stack[i++] = 0);
}

void print_stack(){
    printf("\n");
    for (int i = 0;i < 4; printf("%d--",stack[i++]));
    printf("\nmergedlayer:%d\ntop:%d\n\n",mergedlayer,top);
}

void slide_up(){
    for (int j = 0;j < 4;j++){
        for (int i = 0;i < 4; push_and_merge_element(numbers[i++*GAMERAWS+j]));
        for (int i = 0;i <= 4; i++)
            numbers[i*GAMERAWS+j] = stack[i];
        reset_stack();
    }
}

void slide_down(){
    for (int j = 0;j < 4;j++){
        for (int i = 3;i >= 0; push_and_merge_element(numbers[i--*GAMERAWS+j]));
        for (int i = 0;i < 4; i++){
            numbers[i*GAMERAWS+j] = stack[3-i];
        }
        reset_stack();
    }
}

void slide_left(){
    for (int i = 0;i < 4;i++){
        for (int j = 0;j < 4; push_and_merge_element(numbers[i*GAMERAWS+j++]));
        for (int j = 0;j < 4; j++){
            numbers[i*GAMERAWS+j] = stack[j];
        }
        reset_stack();
    }
}

void slide_right(){
    for (int i = 0;i < 4;i++){
        for (int j = 3;j >= 0; push_and_merge_element(numbers[i*GAMERAWS+j--]));
        for (int j = 0; j < 4; j++){
            numbers[i*GAMERAWS+j] = stack[3-j];
        }
        reset_stack();
    }
}

