#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define GAMECOLS 4
#define GAMERAWS 4

int numbers[GAMECOLS*GAMERAWS] = {0};

int stack[4] = {};
int top = -1;
int mergedlayer = -1;

int state = 0;

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

void reset_stack(){
    top = -1;
    mergedlayer = -1;
    for (int i = 0;i < 4; stack[i++] = 0);
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
