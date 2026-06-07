#ifndef SUDOKUVALIDATOR_H
#define SUDOKUVALIDATOR_H

#include<vector>

class SudokuValidator {
    public:
        bool isValid(const std::vector<std::vector<int>> &grid, int row, int col, int num, int size);
};

#endif