#ifndef SUDOKUSOLVER_H
#define SUDOKUSOLVER_H

#include <vector>

class SudokuSolver{
    public:
        bool solve(std::vector<std::vector<int>>& grid, int size);
        bool isSafe(const std::vector<std::vector<int>>&grid, int row, int col, int num, int size);
};

#endif