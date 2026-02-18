#include <stdio.h>

float mal(float a, float b);
float plus(float a, float b);
float minus(float a, float b);
float geteilt(float a, float b);

int main(){
    float first_n, second_n, erg;
    char zeichen;
    
    printf("Erste Nummer:");
    scanf("%f",&first_n);
    
    printf("Zweite Nummer:");
    scanf("%f", &second_n);
    printf("Rechenart:");
    scanf(" %c", &zeichen);

    switch(zeichen){
        case '*':
            erg=mal(first_n, second_n);
            break;
        case '+':
            erg=plus(first_n, second_n);
            break;
        case '-':
            erg=minus(first_n, second_n);
            break;
        case '/':
            if(second_n==0){
                printf("Fehler: Durch 0 geteilt");
                return 1;
            }
            erg=geteilt(first_n, second_n);
            break;
        default:
        printf("Fehler: Rechenart");
        return 1;
    }
        printf("%.2f %c %.2f = %.2f \n", first_n, zeichen, second_n, erg);
    return 0;
}

float mal(float a, float b){
    return a*b;
}
float plus(float a, float b){
    return a+b;
}
float minus(float a, float b){
    return a-b;
}
float geteilt(float a, float b){
    return a/b;
}