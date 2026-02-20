# include <stdio.h>
#include <stdlib.h>
#include <string.h>    

char array[100][50];
int len;

struct Car{
    float fuel_level;
    float max_fuel_level;
    char model[20];
};

struct SensorData {
    float time;
    double probability;
};

struct Sensor {
    int id;
    double threshold;
    struct SensorData array[500];
    int object_detection[500];
};

int write_file(char *name, char *inhalt);
int read_file(char *name);
void fuel(struct Car *c,float add);


int main(){
   /* write_file("hello.txt", "Hello \nWorld\n ... \n");
    read_file("mySolutions/hello.txt");
    for(int i=0;i<len;i++){
        printf(array[i]);
    } 
    struct Car c1={12,50,"Mercedes C-Klasse"};
    fuel(&c1,12.43);
    printf("Tank: %.2f \n", c1.fuel_level);*/

    FILE *ptr1;
    FILE *ptr2;
    ptr1 = fopen("sensor1.txt", "r");
    if(ptr1==NULL) return 1;
    ptr2 = fopen("sensor2.txt", "r");
    if(ptr2==NULL) return 1;
    while(){
        fscanf(ptr1,"%s")
    }
    
}

int read_file(char *name){
    int i=0;
    FILE *fptr;
    fptr = fopen(name,"r");
    if(fptr==NULL)return 1;
    while(fgets(array[i],sizeof(array[i]),fptr)){
        i++;
    }
    len = i;
    fclose(fptr);
    return 0;
}

int write_file(char *name, char *inhalt){
    int i=0;
    FILE *fptr;
    fptr = fopen(name,"w");
    if(fptr==NULL)return 1;
    fputs(inhalt,fptr);
    fclose(fptr);
    return 0;
}

void fuel(struct Car *c,float add){
    if((c->fuel_level+add)<c->max_fuel_level) c->fuel_level+=add;
}