#include <stdio.h>
#include <stdlib.h>

void functionA() {
    printf("Function A called!\n");
}

void functionB() {
    printf("Function B called!\n");
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
