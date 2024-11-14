#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Example function to measure (you can replace this with your own function)
void function_to_measure() {
    // Simulate some work
    for(int i = 0; i < 1000000; i++) {
        // Some arbitrary operations
        double x = i * 2.5;
        x = x / 2.0;
    }
}

// Function to measure execution time
double measure_execution_time(void (*func)(), int num_runs) {
    if (num_runs <= 0) {
        printf("Error: Number of runs must be positive\n");
        return -1;
    }

    double total_time = 0.0;
    clock_t start, end;

    for (int i = 0; i < num_runs; i++) {
        start = clock();
        func();  // Execute the function
        end = clock();
        
        // Calculate time in milliseconds
        double time_taken = ((double)(end - start) * 1000) / CLOCKS_PER_SEC;
        total_time += time_taken;
    }

    return total_time / num_runs;  // Return average time
}

int main(int argc, char *argv[]) {
    int num_runs;
    
    // Check if number of runs is provided as command line argument
    if (argc != 2) {
        printf("Usage: %s <number_of_runs>\n", argv[0]);
        return 1;
    }

    num_runs = atoi(argv[1]);
    if (num_runs <= 0) {
        printf("Error: Please provide a positive number of runs\n");
        return 1;
    }

    double avg_time = measure_execution_time(function_to_measure, num_runs);
    
    if (avg_time >= 0) {
        printf("Average execution time over %d runs: %.3f milliseconds\n", 
               num_runs, avg_time);
    }

    return 0;
}