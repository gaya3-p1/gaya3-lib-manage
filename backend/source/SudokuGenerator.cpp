#include "SudokuGenerator.h"
#include "SudokuSolver.h"
#include <cstdlib>
#include <ctime>

std::vector<std::vector<int>> SudokuGenerator::generate(int size, int clues) {
    std::vector<std::vector<int>> grid(size, std::vector<int>(size, 0));
    SudokuSolver solver;
    solver.solve(grid, size);

    srand(time(0));
    int CTR = size*size - clues;
    while (CTR > 0) {
        int i = rand() % size;
        int j = rand() % size;

        if(grid[i][j] != 0) {
            grid[i][j] = 0;
            CTR--;
        }
    }
    
    return grid;
}