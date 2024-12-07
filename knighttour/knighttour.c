/*
Knight's Tour Problem
Problem Statement:
    •	Given a chessboard, the Knight's Tour problem is to find a sequence of moves for a knight to visit all squares exactly once.
    •	The knight moves in an “L” shape: two squares in one direction and one square perpendicular to it (or vice versa).
    •	The board size is  N \times N , and the knight starts at a given position.
    •	The goal is to find a sequence of moves for a knight on a chessboard such that the knight visits every square exactly once.
    •	The knight moves in an “L” shape: two squares in one direction and one square perpendicular to it (or vice versa).
    •	The board size is  N \times N , and the knight starts at a given position
*/

#include <stdio.h>
#include <stdbool.h>

#define N 8 // Size of the chessboard

// Possible moves for a knight
int knightMoves[8][2] = {
    {2, 1}, {1, 2}, {-1, 2}, {-2, 1},
    {-2, -1}, {-1, -2}, {1, -2}, {2, -1}
};

// Function to print the chessboard
void printBoard(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d ", board[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if the knight can move to (x, y)
bool isSafe(int x, int y, int board[N][N]) {
    return (x >= 0 && x < N && y >= 0 && y < N && board[x][y] == -1);
}

// Backtracking function to solve the Knight's Tour problem
bool solveKnightTour(int x, int y, int moveCount, int board[N][N]) {
    // Base case: If all squares are visited
    if (moveCount == N * N) {
        return true;
    }

    // Try all possible moves
    for (int i = 0; i < 8; i++) {
        int nextX = x + knightMoves[i][0];
        int nextY = y + knightMoves[i][1];

        if (isSafe(nextX, nextY, board)) {
            board[nextX][nextY] = moveCount; // Mark as visited

            // Recursively try the next move
            if (solveKnightTour(nextX, nextY, moveCount + 1, board)) {
                return true;
            }

            board[nextX][nextY] = -1; // Backtrack
        }
    }

    return false;
}

int main() {
    int board[N][N];

    // Initialize the board with -1 (unvisited)
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            board[i][j] = -1;
        }
    }

    // Starting position for the knight
    int startX = 0, startY = 0;
    board[startX][startY] = 0; // First move

    printf("Knight's Tour on a %dx%d board:\n", N, N);

    if (solveKnightTour(startX, startY, 1, board)) {
        printBoard(board);
    } else {
        printf("No solution exists.\n");
    }

    return 0;
}