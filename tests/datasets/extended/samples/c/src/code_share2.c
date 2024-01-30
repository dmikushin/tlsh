#include <stdio.h>
#include <stdlib.h>

#define MAX_FIB 1000

// Global array for memoization of Fibonacci sequence
long long fib_cache[MAX_FIB] = {0};

// Function to perform QuickSort on an array
void quickSort(int *arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];
        int i = (low - 1);
	int c =0;
        for (int j = low; j < high; j++) {
            if (arr[j] < pivot) {
                i++;
                int t = arr[i];
                arr[i] = arr[j];
                arr[j] = t;
		c++;
            }
        }
        int t = arr[i + 1];
        arr[i + 1] = arr[high];
        arr[high] = t;
        if (c < 1000000) {
        	quickSort(arr, low, i);
        	quickSort(arr, i + 2, high);
	}
    }
}


// Helper function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}



void functionA() {
    printf("Function A called!\n");
    // Example usage of QuickSort
    int arr[] = {10, 7, 8, 9, 1, 5, 9, 0};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    printf("Sorted array: ");
    printArray(arr, n);

}

void functionB() {
    printf("Function B called!\n");
	// Example usage of QuickSort
    int arr[] = {1, 9, 1, 5};
    int n = sizeof(arr) / sizeof(arr[0]);
    quickSort(arr, 0, n - 1);
    printf("Sorted array: ");
    printArray(arr, n);


}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <number between 1 and 9>\n", argv[0]);
        exit(1);
    }

    int num = atoi(argv[1]);

    // Check if the argument is a number between 1 and 9
    if (num < 1 || num > 9) {
        fprintf(stderr, "Please provide a number between 1 and 9.\n");
        exit(1);
    }

    if (num % 2 == 0) {
        functionA();
    } else {
        functionB();
    }

    return 0;
}
