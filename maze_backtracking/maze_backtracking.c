#include <stdio.h>
#include <stdbool.h>

#define N 4 // Size of the maze

// Function to print the solution matrix
void printMaze(int maze[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }
}

// Function to check if moving to a cell is valid
bool isSafe(int maze[N][N], int x, int y) {
    return (x >= 0 && x < N && y >= 0 && y < N && maze[x][y] == 1);
}

// Backtracking function to solve the maze
bool solveMazeUtil(int maze[N][N], int x, int y, int solution[N][N]) {
    // Base case: If we reach the bottom-right corner
    if (x == N - 1 && y == N - 1) {
        solution[x][y] = 1;
        return 1;
    }

    // Check if the current cell is valid
    if (isSafe(maze, x, y)) {
        solution[x][y] = 1; // Mark the cell as part of the solution

        // Move right
        if (solveMazeUtil(maze, x, y + 1, solution)) {
            return true;
        }

        // Move down
        if (solveMazeUtil(maze, x + 1, y, solution)) {
            return true;
        }

        // Backtrack: Unmark the cell as part of the solution
        solution[x][y] = 0;
    }

    return false;
}

int main() {
    int maze[N][N] = {
        {1, 0, 0, 0},
        {1, 1, 1, 1},
        {0, 1, 0, 0},
        {1, 1, 1, 1}
    };
    int solution[N][N] = {0};

    printf("Maze:\n");
    printMaze(maze);

    printf("Solution to the maze:\n");

    if (!solveMazeUtil(maze, 0, 0, solution)) {
        printf("No solution exists\n");
    } else {
        printMaze(solution);
    }

    return 0;
}