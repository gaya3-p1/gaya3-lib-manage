#ifndef SUDOKUUI_H
#define SUDOKUUI_H

#include <vector>
class SudokuUI {
    public:
        void displayGrid(const std::vector<std::vector<int>>&grid, int size);
        void showMenu();
        int getChoice();
};

#endif
