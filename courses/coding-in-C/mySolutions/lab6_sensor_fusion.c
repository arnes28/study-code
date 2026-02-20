#include <stdio.h>
#include <string.h>

// Data structure for a single sensor measurement
typedef struct {
    float time;
    double probability;
} SensorData;

// Data structure for a complete sensor
typedef struct {
    int id;
    double threshold;
    SensorData data[3000];
    int object_detection[3000];
    int num_samples;
} Sensor;

// Structure for a Car (Section II)
typedef struct {
    float fuel_level;
    float max_fuel_level;
    char model[50];
} Car;

// Detection interval structure
typedef struct {
    float start_time;
    float end_time;
} DetectionInterval;

// Function prototypes
void refuel(Car *car, float amount);
int read_sensor_file(const char *filename, Sensor *sensor);
void compute_detections(Sensor *sensor);
int find_detection_intervals(Sensor *sensor, DetectionInterval intervals[]);
int find_fused_intervals(Sensor *sensor1, Sensor *sensor2, DetectionInterval intervals[]);
void print_intervals(const char *label, DetectionInterval intervals[], int count);

// Section II: Refuel function
void refuel(Car *car, float amount) {
    if (car->fuel_level + amount <= car->max_fuel_level) {
        car->fuel_level += amount;
        printf("Refueled %.2f liters. Current fuel level: %.2f / %.2f liters\n",
               amount, car->fuel_level, car->max_fuel_level);
    } else {
        float added = car->max_fuel_level - car->fuel_level;
        car->fuel_level = car->max_fuel_level;
        printf("Tank is full. Added %.2f liters. Current fuel level: %.2f / %.2f liters\n",
               added, car->fuel_level, car->max_fuel_level);
    }
}

// Read sensor data from file
int read_sensor_file(const char *filename, Sensor *sensor) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error: Could not open file '%s'\n", filename);
        printf("Make sure the file is in the correct location.\n");
        return 0;
    }
    
    sensor->num_samples = 0;
    while (sensor->num_samples < 3000 &&
           fscanf(file, "%f %lf", 
                  &sensor->data[sensor->num_samples].time,
                  &sensor->data[sensor->num_samples].probability) == 2) {
        sensor->num_samples++;
    }
    
    fclose(file);
    printf("Read %d samples from %s\n", sensor->num_samples, filename);
    return sensor->num_samples;
}

// Compute binary detection signal based on threshold
void compute_detections(Sensor *sensor) {
    for (int i = 0; i < sensor->num_samples; i++) {
        sensor->object_detection[i] = 
            (sensor->data[i].probability > sensor->threshold) ? 1 : 0;
    }
}

// Find all detection intervals for a sensor
int find_detection_intervals(Sensor *sensor, DetectionInterval intervals[]) {
    int count = 0;
    int in_detection = 0;
    
    for (int i = 0; i < sensor->num_samples; i++) {
        // Start of detection: 0 -> 1
        if (!in_detection && sensor->object_detection[i] == 1) {
            intervals[count].start_time = sensor->data[i].time;
            in_detection = 1;
        }
        // End of detection: 1 -> 0
        else if (in_detection && sensor->object_detection[i] == 0) {
            intervals[count].end_time = sensor->data[i - 1].time;
            count++;
            in_detection = 0;
        }
    }
    
    // If still in detection at end of data
    if (in_detection) {
        intervals[count].end_time = sensor->data[sensor->num_samples - 1].time;
        count++;
    }
    
    return count;
}

// Find overlapping detection intervals (fusion)
int find_fused_intervals(Sensor *sensor1, Sensor *sensor2, DetectionInterval intervals[]) {
    int count = 0;
    int in_detection = 0;
    int min_samples = (sensor1->num_samples < sensor2->num_samples) ? 
                       sensor1->num_samples : sensor2->num_samples;
    
    for (int i = 0; i < min_samples; i++) {
        int both_detect = sensor1->object_detection[i] && sensor2->object_detection[i];
        
        // Start of fused detection
        if (!in_detection && both_detect) {
            intervals[count].start_time = sensor1->data[i].time;
            in_detection = 1;
        }
        // End of fused detection
        else if (in_detection && !both_detect) {
            intervals[count].end_time = sensor1->data[i - 1].time;
            count++;
            in_detection = 0;
        }
    }
    
    // If still in detection at end of data
    if (in_detection) {
        intervals[count].end_time = sensor1->data[min_samples - 1].time;
        count++;
    }
    
    return count;
}

// Print detection intervals
void print_intervals(const char *label, DetectionInterval intervals[], int count) {
    printf("\n%s:\n", label);
    if (count == 0) {
        printf("  No detections\n");
    } else {
        for (int i = 0; i < count; i++) {
            printf("  Start: %.2f s  End: %.2f s\n", 
                   intervals[i].start_time, intervals[i].end_time);
        }
    }
}

// Section I: File I/O demonstrations
void demonstrate_file_io() {
    printf("=== Section I: File I/O Demonstrations ===\n\n");
    
    // Create a test file
    FILE *test_file = fopen("test_output.txt", "w");
    if (test_file == NULL) {
        printf("Error creating test file\n");
        return;
    }
    
    // fprintf() - formatted output
    fprintf(test_file, "Line 1: Using fprintf\n");
    fprintf(test_file, "Number: %d, Float: %.2f\n", 42, 3.14);
    
    // fputs() - write string
    fputs("Line 2: Using fputs\n", test_file);
    
    // fputc() - write single character
    fputc('A', test_file);
    fputc('\n', test_file);
    
    fclose(test_file);
    
    // Read the file back
    test_file = fopen("test_output.txt", "r");
    if (test_file == NULL) {
        printf("Error opening test file for reading\n");
        return;
    }
    
    printf("Reading file with different methods:\n\n");
    
    // fgetc() - read single character
    printf("1. Using fgetc() for first 10 characters:\n");
    for (int i = 0; i < 10; i++) {
        int c = fgetc(test_file);
        if (c != EOF) {
            putchar(c);
        }
    }
    printf("\n\n");
    
    // Reset file position
    rewind(test_file);
    
    // fgets() - read line
    printf("2. Using fgets() to read lines:\n");
    char buffer[100];
    int line_num = 1;
    while (fgets(buffer, sizeof(buffer), test_file) != NULL) {
        printf("   Line %d: %s", line_num++, buffer);
    }
    printf("\n");
    
    // Reset and use fscanf()
    rewind(test_file);
    printf("3. Using fscanf() to read formatted data:\n");
    char word1[20], word2[20], word3[20];
    fscanf(test_file, "%s %*d%*c %s %s", word1, word2, word3);
    printf("   Read words: %s, %s, %s\n\n", word1, word2, word3);
    
    fclose(test_file);
    
    printf("Note: If you move the file to another folder, you need to:\n");
    printf("  - Update the file path in fopen() to include the folder\n");
    printf("  - Use relative paths (e.g., '../folder/file.txt')\n");
    printf("  - Or use absolute paths (e.g., '/Users/...')\n\n");
}

// Section II: Car refueling demonstration
void demonstrate_car_refuel() {
    printf("=== Section II: Car Refueling ===\n\n");
    
    Car my_car;
    my_car.fuel_level = 15.5;
    my_car.max_fuel_level = 60.0;
    strcpy(my_car.model, "Tesla Model 3");
    
    printf("Car: %s\n", my_car.model);
    printf("Initial fuel level: %.2f / %.2f liters\n\n", 
           my_car.fuel_level, my_car.max_fuel_level);
    
    refuel(&my_car, 20.0);
    refuel(&my_car, 30.0);
    printf("\n");
}

// Main function
int main() {
    printf("========================================\n");
    printf("    Lab 6: Sensor Fusion Solution\n");
    printf("========================================\n\n");
    
    // Section I: File I/O demonstrations
    demonstrate_file_io();
    
    // Section II: Car refueling
    demonstrate_car_refuel();
    
    // Section III: Sensor Fusion
    printf("=== Section III: Sensor Fusion ===\n\n");
    
    // Initialize sensors
    Sensor sensor1, sensor2;
    sensor1.id = 1;
    sensor1.threshold = 0.8;
    sensor2.id = 2;
    sensor2.threshold = 0.7;
    
    // Read sensor data files
    // Note: The files should be in the Lab_6 folder
    // When run from output directory, we need to go up two levels
    const char *sensor1_file = "../../Lab_6/sensor1.txt";
    const char *sensor2_file = "../../Lab_6/sensor2.txt";
    
    if (!read_sensor_file(sensor1_file, &sensor1)) {
        printf("Failed to read sensor1 data. Trying current directory...\n");
        sensor1_file = "sensor1.txt";
        if (!read_sensor_file(sensor1_file, &sensor1)) {
            printf("Cannot find sensor1.txt. Please ensure files are accessible.\n");
            return 1;
        }
    }
    
    if (!read_sensor_file(sensor2_file, &sensor2)) {
        printf("Failed to read sensor2 data. Trying current directory...\n");
        sensor2_file = "sensor2.txt";
        if (!read_sensor_file(sensor2_file, &sensor2)) {
            printf("Cannot find sensor2.txt. Please ensure files are accessible.\n");
            return 1;
        }
    }
    
    // Compute binary detection signals
    compute_detections(&sensor1);
    compute_detections(&sensor2);
    
    // Find detection intervals
    DetectionInterval sensor1_intervals[100];
    DetectionInterval sensor2_intervals[100];
    DetectionInterval fused_intervals[100];
    
    int sensor1_count = find_detection_intervals(&sensor1, sensor1_intervals);
    int sensor2_count = find_detection_intervals(&sensor2, sensor2_intervals);
    int fused_count = find_fused_intervals(&sensor1, &sensor2, fused_intervals);
    
    // Output results
    printf("\n========================================\n");
    printf("    Object Detection Results\n");
    printf("========================================\n");
    
    print_intervals("Sensor 1 detections", sensor1_intervals, sensor1_count);
    print_intervals("Sensor 2 detections", sensor2_intervals, sensor2_count);
    print_intervals("Fused signal (both sensors)", fused_intervals, fused_count);
    
    printf("\n========================================\n");
    printf("Processing complete!\n");
    printf("========================================\n");
    
    return 0;
}
