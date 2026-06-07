#ifndef SUDOKUGENERATOR_H
#define SUDOKUGENERATOR_H

#include <vector>

class SudokuGenerator {
    std::vector<std::vector<int>> generate(int size, int clues);
};

#endif