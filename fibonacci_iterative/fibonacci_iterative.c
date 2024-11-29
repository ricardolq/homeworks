#include <stdio.h>

// Iterative function to calculate nth Fibonacci number
int fibonacci_iterative(int n) {
    if (n == 0) return 0; // Base case
    if (n == 1) return 1; // Base case

    int prev1 = 1;
    int prev2 = 0;
    int current;

    for (int i = 2; i <= n; i++) {
        current = prev1 + prev2; // Calculate current Fibonacci number
        prev2 = prev1;           // Update prev2 to prev1
        prev1 = current;         // Update prev1 to current
    }

    return current;
}

int main() {
    int n;
    printf("Enter the position (n) to find the nth Fibonacci number: ");
    scanf("%d", &n);

    if (n < 0) {
        printf("Fibonacci sequence is not defined for negative numbers.\n");
    } else {
        printf("The %dth Fibonacci number is %d.\n", n, fibonacci_iterative(n));
    }

    return 0;
}