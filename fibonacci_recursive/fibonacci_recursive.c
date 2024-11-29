#include <stdio.h>

// Recursive function to calculate nth Fibonacci number
int fibonacci(int n) {
    if (n == 0) { // Base case 1
        return 0;
    } else if (n == 1) { // Base case 2
        return 1;
    } else { // Recursive case
        return fibonacci(n - 1) + fibonacci(n - 2);
    }
}

int main() {
    int n;
    printf("Enter the position (n) to find the nth Fibonacci number: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Fibonacci sequence is not defined for negative numbers.\n");
    } else {
        printf("The %dth Fibonacci number is %d.\n", n, fibonacci(n));
    }

    return 0;
}