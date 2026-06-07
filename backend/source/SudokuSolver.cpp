#include "SudokuSolver.h"

bool SudokuSolver::isSafe(const std::vector<std::vector<int>> & grid,int row, int col, int num, int size) {
    int boxSize = (size == 9) ? 3 : 2;
    for(int x = 0; x < size; x++) {
        if(grid[row][x] == num || grid[x][col] == num) {
            return false;
        }
    }
    int startRow = row - row % boxSize;
    int startCol = col - col % 3;
    for(int i = 0; i < boxSize; i++) {
        for(int j = 0; j < 3; j++) {
            if(grid[i+startRow][j+startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

bool SudokuSolver::solve(std::vector<std::vector<int>> &grid, int size) {
    for(int row = 0; row < size; row++) {
        for(int col = 0; col < size; col++){
            if(grid[row][col] == 0) {
                for(int num = 1; num <= size; num++){
                    if(isSafe(grid, row, col, num, size)) {
                        grid[row][col] = num;
                        if(solve(grid, size)) {
                            return true;
                        }
                        grid[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}