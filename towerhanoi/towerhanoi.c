#include <stdio.h>
#include <stdlib.h>
#include <unistd.h> // For sleep() on UNIX systems

#define N 5 // Number of disks
#define MAX_DISKS 10 // Maximum number of disks (for display purposes)

// Rod arrays to represent the state of each rod
int rodA[MAX_DISKS], rodB[MAX_DISKS], rodC[MAX_DISKS];
int topA = -1, topB = -1, topC = -1; // Track top of each rod

// Function to initialize the rods
void initializeRods(int n) {
    for (int i = n; i >= 1; i--) {
        rodA[++topA] = i; // Push all disks onto rod A
    }
}

// Function to display the current state of the rods
void displayRods() {
    int height = N;

    printf("\nRod A       Rod B       Rod C\n");
    for (int i = height - 1; i >= 0; i--) {
        // Print the current level for each rod
        printf("  %2d         %2d         %2d\n",
               (i <= topA ? rodA[i] : 0),
               (i <= topB ? rodB[i] : 0),
               (i <= topC ? rodC[i] : 0));
    }
    printf("----------------------------\n");
    sleep(1); // Pause to visualize the change
}

// Function to move a disk between rods
void moveDisk(int from[], int *fromTop, int to[], int *toTop) {
    int disk = from[(*fromTop)--]; // Pop from the source rod
    to[++(*toTop)] = disk;        // Push onto the destination rod
    displayRods();                // Display the updated state
}

// Recursive function to solve the Towers of Hanoi
void solveTowersOfHanoi(int n, int from[], int *fromTop, int to[], int *toTop, int aux[], int *auxTop) {
    if (n == 1) {
        moveDisk(from, fromTop, to, toTop); // Base case: Move one disk
        return;
    }

    // Move top n-1 disks from 'from' to 'aux' using 'to' as auxiliary
    solveTowersOfHanoi(n - 1, from, fromTop, aux, auxTop, to, toTop);

    // Move the nth disk directly from 'from' to 'to'
    moveDisk(from, fromTop, to, toTop);

    // Move the n-1 disks from 'aux' to 'to' using 'from' as auxiliary
    solveTowersOfHanoi(n - 1, aux, auxTop, to, toTop, from, fromTop);
}

int main() {
    initializeRods(N); // Initialize the rods with disks

    printf("Initial state:\n");
    displayRods();

    solveTowersOfHanoi(N, rodA, &topA, rodC, &topC, rodB, &topB);

    printf("\nTowers of Hanoi solved!\n");
    return 0;
}