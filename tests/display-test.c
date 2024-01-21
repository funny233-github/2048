#include "../untils.h"
#include "../display.h"

void test_color_display(){
    int test1[16] = {
        0,2,4,8,
        16,32,64,128,
        256,512,1024,2048,
        4096,8192,16384,32767,
    };
    for (int i = 0;i < 16;i++)
        grid[i] = test1[i];
    
    update_windows_and_score();
     
}

int main(){
    start_curses();
    if(has_colors() == FALSE){
        printf("has colors : false");
        return -1;
    }
    refresh();
    test_color_display();
    getch();
    endwin();
}
