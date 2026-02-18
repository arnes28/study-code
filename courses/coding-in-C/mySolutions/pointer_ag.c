#include <stdio.h>

int main(){
    int myNumbers[5]={10,20,30,40,50};
    int *p1= &myNumbers[1];
    int *p2= &myNumbers[4];
    printf("Pointer 1: %d, Pointer 2: %d \n Differenz: %d \n", p1, p2, p2-p1);
    return 0;
}