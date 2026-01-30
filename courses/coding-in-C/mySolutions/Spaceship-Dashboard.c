#include <stdio.h>

int main() {
    char name [64] = "NCC-1701-D";
    int crew_count = 1014;
    int mission_days = 2563;
    long distance_traveled = 900000000;
    float light_speed = 12.7;
    double range = 1234567.891;

    printf("Class of the ship: ");
    scanf("%s", name);
    printf("Number of crew members: ");
    scanf("%d", &crew_count);
    printf("Number of mission days: ");
    scanf("%d", &mission_days);
    
    printf("\n\n%-30s %s \n", "Name", "Value");
    for(int i = 1; i < 45; i++) {
        printf("-");
    }
    printf("\n");
    printf("%-30s %s\n", "Class", name);
    printf("%-30s %d\n", "Crew Count", crew_count);
    printf("%-30s %d\n", "Mission Days", mission_days);
    printf("%-30s %ld\n", "Distance Travelled (km)", distance_traveled);
    printf("%-30s %.1f\n", "% of Light Speed Distance", light_speed);
    printf("%-30s %.3f\n\n\n", "Current Range", range);
    while(1);
    return 0;
}