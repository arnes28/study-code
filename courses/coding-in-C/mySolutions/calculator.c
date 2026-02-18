#include <stdio.h>

int main(){
    float first_n, second_n, erg;
    char zeichen;
    
    printf("Erste Nummer: ");
    scanf("%f",&first_n);
    
    printf("Zweite Nummer: ");
    scanf("%f", &second_n);
    
    printf("Rechenart : ");
    scanf(" %c", &zeichen);

    if(zeichen=='*'){
        erg=first_n*second_n;
        printf("%.2f * %.2f = %.2f ", first_n, second_n, erg);    }
    else if(zeichen=='+'){
        erg=first_n+second_n;
        printf("%.2f + %.2f = %.2f ", first_n, second_n, erg);    }
    else if(zeichen=='-'){
        erg=first_n-second_n;
        printf("%.2f - %.2f = %.2f ", first_n, second_n, erg);    }
    else if(zeichen=='/'){
        if(second_n==0){
            printf("Fehler: Durch 0 geteilt");
            return 1;
        }
        erg=first_n/second_n;
        printf("%.2f / %.2f = %.2f ", first_n, second_n, erg);
    }
    else {
        printf("Keine valide Rechart");
    }
    return 0;
}