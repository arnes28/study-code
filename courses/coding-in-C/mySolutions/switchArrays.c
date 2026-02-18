#include <stdio.h>

int array1[5][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16},
    {17, 18, 19, 20}};
int array2[5][4] = {
    {21, 22, 23, 24},
    {25, 26, 27, 28},
    {29, 30, 31, 32},
    {33, 34, 35, 36},
    {37, 38, 39, 40}};
int speicher;

int main(void){
    for(int j=0;j<5;j++){
        for(int i=0;i<4;i++){
            speicher = array2[j][i];
            array2[j][i] = array1[j][i];
            array1[j][i] = speicher;
        }
    }
    printf("Array 1:\n");
    for(int j=0;j<5;j++){
        for(int i=0;i<4;i++){
                printf("%4d", array1[j][i]);
        }
        printf("\n");
    }
    printf("\nArray 2:\n");
    for(int j=0;j<5;j++){
        for(int i=0;i<4;i++){
                printf("%4d", array2[j][i]);
        }
        printf("\n");
    }
    return 0;
}