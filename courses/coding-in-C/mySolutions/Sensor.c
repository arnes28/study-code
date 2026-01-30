#include <stdio.h>

int main(){
    int messwert=0;
    unsigned char status = 0xA7;

    if(status>>7 & 1){
        printf("Fehler\n");
    }
    if (status>>6 & 1){
        printf("Übertemperatur\n");
    }
    if (status >> 5 & 1) {
        printf("Unterspannung\n");
    }
    if (status>>3 & 1) {
        messwert += 8;
    }
    if (status>>2 & 1) {
        messwert += 4;
    }
    if (status>>1 & 1) {
        messwert += 2;
    }
    if (status & 1) {
        messwert += 1;
    }
    printf("\nMesswert: %d\n", messwert);
    return 0;
}