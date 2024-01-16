#include <ncurses.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int numbers[16];

const int GAMECOLS = 4;
const int GAMERAWS = 4;

int state = 0;

void start_curses(){
    initscr();
    cbreak();
    noecho();
    curs_set(0);
}

void update_state(){
    clear();
    mvprintw(0,0,"state:%d",state);
    refresh();
}


void update_windows(){
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

void number_generator(){
    while (true){
        bool isfull = true;
        for(int i = 0; i < 16; i++){
            if (numbers[i] == 0)
                isfull = false;
        }
        if (isfull)
            break;

        int pos = rand()%16;
        if (numbers[pos] == 0){
            numbers[pos] = 2 + rand()%2*2;
            break;
        }
    }
}

void up(){
    for (int j = 0;j < 4;j++){
        int stack[4] = {0,0,0,0};
        int top = 0;
        int donelayer = 0;
        for (int i = 0;i < 4; i++){
            if (numbers[i*GAMERAWS+j] == 0)
                continue;
            if ((stack[top-1] != numbers[i*GAMERAWS+j] || donelayer >= top)){
                stack[top] = numbers[i*GAMERAWS+j];
                top++;
                continue;
            }
            stack[top-1] += numbers[i*GAMERAWS+j];
            state += stack[top-1];
            donelayer = top;
        } 

        for (int i = 0;i < 4; i++)
            numbers[i*GAMERAWS+j] = stack[i];

    }
}

void down(){
    for (int j = 0;j < 4;j++){
        int stack[4] = {0,0,0,0};
        int top = 0;
        int donelayer = 0;
        for (int i = 3;i >= 0; i--){
            if (numbers[i*GAMERAWS+j] == 0)
                continue;
            if ((stack[top-1] != numbers[i*GAMERAWS+j] || donelayer >= top)){
                stack[top] = numbers[i*GAMERAWS+j];
                top++;
                continue;
            }
            stack[top-1] += numbers[i*GAMERAWS+j];
            state+=stack[top-1];
            donelayer = top;
        } 
        for (int i = 3;i >= 0; i--){
            numbers[i*GAMERAWS+j] = stack[3-i];
        }
    }
}

void left(){
    for (int i = 0;i < 4;i++){
        int stack[4] = {0,0,0,0};
        int top = 0;
        int donelayer = 0;
        for (int j = 0;j < 4; j++){
            if (numbers[i*GAMERAWS+j] == 0)
                continue;
            if ((stack[top-1] != numbers[i*GAMERAWS+j] || donelayer >= top)){
                stack[top] = numbers[i*GAMERAWS+j];
                top++;
                continue;
            }
            stack[top-1] += numbers[i*GAMERAWS+j];
            state+=stack[top-1];
            donelayer = top;
        } 
        for (int j = 0;j < 4; j++){
            numbers[i*GAMERAWS+j] = stack[j];
        }
    }
}

void right(){
    for (int i = 0;i < 4;i++){
        int stack[4] = {0,0,0,0};
        int top = 0;
        int donelayer = 0;
        for (int j = 3;j >= 0;j--){
            if (numbers[i*GAMERAWS+j] == 0)
                continue;
            if ((stack[top-1] != numbers[i*GAMERAWS+j] || donelayer >= top)){
                stack[top] = numbers[i*GAMERAWS+j];
                top++;
                continue;
            }
            stack[top-1] += numbers[i*GAMERAWS+j];
            state+=stack[top-1];
            donelayer = top;
        } 
        for (int j = 3; j >=0; j--){
            numbers[i*GAMERAWS+j] = stack[3-j];
        }
    }
}

int main(){
    srand(time(NULL));
    start_curses();

    refresh();
    number_generator();
    update_windows();

    while (true){
        char key = getch();
        if (key == 'q')
            break;
        switch (key) {
            case 'w':
                up();
                break;
            case 's':
                down();
                break;
            case 'a':
                left();
                break;
            case 'd':
                right();
                break;
            default:
                continue;
                break;
        }
        number_generator();
        update_state();
        update_windows();
    }
    endwin();
}
