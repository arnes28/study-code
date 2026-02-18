#include <stdio.h>



int main(){
    printf("   ");
    for(int j=0; j<8; j++){
        printf(" %c ", 'A'+j);
    }
    printf("\n");
    printf("  +");
    for(int j=0; j<8; j++){
        printf("--+");
    }
    printf("\n");
    for(int i=8; i>=1; i--){
        printf("%d |", i);  
        
        for(int j=0; j<8; j++){
            if((i+j) % 2 == 0){
                printf("  |");  
            } else {
                printf("##|");  
            }
        }
        
        printf(" %d\n", i);  
        printf("  +");
        for(int j=0; j<8; j++){
            printf("--+");
        }
        printf("\n");
    }
    
    printf("   ");
    for(int j=0; j<8; j++){
        printf(" %c ", 'A'+j);
    }
    printf("\n");
    
    return 0;
}