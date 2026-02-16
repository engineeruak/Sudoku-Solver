//Sudoku Solver.
#include <iostream>
#include <vector>

// Define the Sudoku grid size
const int N = 9;

// Function to print the Sudoku grid
void printGrid(const std::vector<std::vector<int>>& grid) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            std::cout << grid[i][j] << " ";
            if ((j + 1) % 3 == 0 && j < 8) std::cout << "| ";
        }
        std::cout << "\n";
        if ((i + 1) % 3 == 0 && i < 8) std::cout << "---------------------" << std::endl;
    }
}

// Function to check if a number can be placed in grid[row][col]
bool isSafe(const std::vector<std::vector<int>>& grid, int row, int col, int num) {
    // Check row and column
    for (int x = 0; x < N; ++x) {
        if (grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }

    // Check 3x3 subgrid
    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (grid[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

// Function to solve Sudoku using backtracking
bool solveSudoku(std::vector<std::vector<int>>& grid) {
    int row = -1, col = -1;
    bool isEmpty = false;

    // Find an empty cell
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }

    // No empty cells left, puzzle solved
    if (!isEmpty) return true;

    // Try numbers 1 to 9 in the empty cell
    for (int num = 1; num <= 9; ++num) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (solveSudoku(grid)) {
                return true;
            }
            grid[row][col] = 0; // Backtrack
        }
    }
    return false;
}

int main() {
    // Example Sudoku puzzle (0 represents empty cells)
    std::vector<std::vector<int>> grid = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    std::cout << "Initial Sudoku puzzle:" << std::endl;
    printGrid(grid);

    if (solveSudoku(grid)) {
        std::cout << "\nSolved Sudoku:" << std::endl;
        printGrid(grid);
    } else {
        std::cout << "No solution exists." << std::endl;
    }
    system ("pause");

    return 0;
}
