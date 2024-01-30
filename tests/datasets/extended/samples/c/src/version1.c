#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

// ... (Other functions)


#define MAX_FIB 1000

// Global array for memoization of Fibonacci sequence
long long fib_cache[MAX_FIB] = {0};

// Function to perform QuickSort on an array
void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
            }
        }
        int t = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = t;

        quickSort(arr, low, i);
        quickSort(arr, i + 2, high);
    }
}

// Function to calculate Fibonacci number using memoization
long long fibonacci(int n) {
    if (n <= 1)
        return n;
    if (fib_cache[n] != 0)
        return fib_cache[n];
    fib_cache[n] = fibonacci(n - 1) + fibonacci(n - 2);
    return fib_cache[n];
}

// Function to perform matrix multiplication
void matrixMultiply(int r1, int c1, int r2, int c2, int a[r1][c1], int b[r2][c2], int result[r1][c2]) {
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
            result[i][j] = 0;
            for (int k = 0; k < c1; k++)
                result[i][j] += a[i][k] * b[k][j];
        }
    }
}

// Function to calculate the area of a circle
double calculateCircleArea(double radius) {
    return M_PI * radius * radius;
}

// Function to convert Celsius to Fahrenheit
double celsiusToFahrenheit(double celsius) {
    return (celsius * 9 / 5) + 32;
}

// Function to calculate the factorial of a number
unsigned long long calculateFactorial(int n) {
    if (n == 0) return 1;
    unsigned long long factorial = 1;
    for (int i = 1; i <= n; ++i) {
        factorial *= i;
    }
    return factorial;
}


// Helper function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// Function for a menu using switch statement with 10 cases and random inputs
void menuSystem(int choice) {
    // Seed the random number generator
    srand((unsigned int)time(NULL));

    double radius, celsius;
    int number;

    switch(choice) {
        case 1:
            radius = (double)rand() / (double)(RAND_MAX) * 100; // Random radius between 0 and 100
            printf("Random radius of the circle: %.2f\n", radius);
            printf("Area of the circle: %.2f\n", calculateCircleArea(radius));
            break;
        case 2:
            celsius = (double)rand() / (double)(RAND_MAX) * 100; // Random celsius between 0 and 100
            printf("Random temperature in Celsius: %.2f\n", celsius);
            printf("Temperature in Fahrenheit: %.2f\n", celsiusToFahrenheit(celsius));
            break;
        case 3:
            number = rand() % 21; // Random number between 0 and 20 for factorial
            printf("Random number to calculate the factorial: %d\n", number);
            printf("Factorial of %d: %llu\n", number, calculateFactorial(number));
            break;
        // ... (Other cases)

	 case 4:
            printf("Menu 4: Placeholder for another function.\n");
            break;
        case 5:
            printf("Menu 5: Placeholder for another function.\n");
            break;
        case 6:
            printf("Menu 6: Placeholder for another function.\n");
            break;
        case 7:
            printf("Menu 7: Placeholder for another function.\n");
            break;
        case 8:
            printf("Menu 8: Placeholder for another function.\n");
            break;
        case 9:
            printf("Menu 9: Placeholder for another function.\n");
            break;
        case 10:
            printf("Menu 10: Placeholder for another function.\n");
            break;
        default:
            printf("Invalid choice. Please select a number between 1 and 10.\n");
            break;
    }
}

// ... (Main function and other code)

int main() {
    // Example usage of QuickSort
    int arr[] = {10, 7, 8, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    printf("Sorted array: ");
    printArray(arr, n);

    // Example usage of Fibonacci
    int fib_number = 50; // This will compute the 50th Fibonacci number
    printf("Fibonacci number %d is: %lld\n", fib_number, fibonacci(fib_number));

    // Example usage of Matrix Multiplication
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int b[3][2] = {{7, 8}, {9, 10}, {11, 12}};
    int result[2][2] = {0};

    matrixMultiply(2, 3, 3, 2, a, b, result);
    printf("Matrix multiplication result:\n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }


    // Example usage of the menu system with random choice
    int choice = rand() % 10 + 1; // Random choice between 1 and 10
    printf("Random menu choice (1-10): %d\n", choice);
    menuSystem(choice);

    return 0;
}
