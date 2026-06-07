#include "SudokuValidator.h"
#include "SudokuSolver.h"

bool SudokuValidator::isValid(const std::vector<std::vector<int>> &grid, int row, int col, int num, int size) {
    SudokuSolver solver;
    return solver.isSafe(grid, row, col, num, size);
}