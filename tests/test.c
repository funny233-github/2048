#include <stdio.h>
#include <stdbool.h>
#include "../untils.h"
#include "../display.h"

void test_push_and_merge_element(){

    push_and_merge_element(2);
    if (!(stack[0] == 2 && stack[1] == 0 && stack[2] == 0 && stack[3] == 0 && mergedlayer == -1 && top == 0)){
        fprintf(stderr,"Error: test_push_and_merge_element 0 not success\n");
        print_stack();
    }

    reset_stack();
    if (!(stack[0] == 0 && stack[1] == 0 && stack[2] == 0 && stack[3] == 0 && mergedlayer == -1 && top == -1)){
        fprintf(stderr,"Error: test_push_and_merge_element 1 not success\n");
        print_stack();
    }

    push_and_merge_element(2);
    push_and_merge_element(2);
    if (!(stack[0] == 4 && stack[1] == 0 && stack[2] == 0 && stack[3] == 0 && mergedlayer == 0 && top == 0)){
        fprintf(stderr,"Error: test_push_and_merge_element 2 not success\n");
        print_stack();
    }


    reset_stack();
    for (int i = 0; i < 8; push_and_merge_element(2),i++);
    if (!(stack[0] == 4 && stack[1] == 4 && stack[2] == 4 && stack[3] == 4 && mergedlayer == 3 && top == 3)){
        fprintf(stderr,"Error: test_push_and_merge_element 3 not success\n");
        print_stack();
    }

    reset_stack();
    for (int i = 1; i < 5; push_and_merge_element(2*i++));
    if (!(stack[0] == 2 && stack[1] == 4 && stack[2] == 6 && stack[3] == 8 && mergedlayer == -1 && top == 3)){
        fprintf(stderr,"Error: test_push_and_merge_element 4 not success\n");
        print_stack();
    }

    reset_stack();

}

void print_grid(){
    for (int i = 0;i < 4;i++){
        for (int j = 0;j < 4;printf("%d ",grid[i*GAMECOLS+j++]));
        printf("\n");
    }
}

void test_slide(){
    int test1[16] = {
        2,0,0,0,
        2,0,0,0,
        0,0,0,0,
        0,0,0,0,
    };
    for (int i = 0;i < 16;i++)
        grid[i] = test1[i];
    int answer1[16] = {
        4,0,0,0,
        0,0,0,0,
        0,0,0,0,
        0,0,0,0,
    };
    slide(UP);
    for (int i = 0;i < 16;i++){
        if (grid[i] != answer1[i]){
            fprintf(stderr,"Error: test_slide 1 not success\n");
            print_grid(); 
            break;
        }
    }

    int test2[16] = {
        0,0,0,0,
        2,0,4,0,
        2,2,0,0,
        2,0,0,0,
    };
    for (int i = 0;i < 16;i++)
        grid[i] = test2[i];
    int answer2[16] = {
        4,2,4,0,
        2,0,0,0,
        0,0,0,0,
        0,0,0,0,
    };
    slide(UP);
    for (int i = 0;i < 16;i++){
        if (grid[i] != answer2[i]){
            fprintf(stderr,"Error: test_slide 2 not success\n");
            print_grid(); 
            break;
        }
    }
    
}


int main(){
    test_push_and_merge_element();
    test_slide();
}
