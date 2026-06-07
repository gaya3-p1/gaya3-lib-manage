#include "SudokuUI.h"
#include <iostream>

void SudokuUI::displayGrid(const std::vector<std::vector<int>>& grid, int size) {
    std::cout<<"\n SUdoku Grid (" <<size <<"x"<<size<<"):\n";
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++) {
            if(grid[i][j] == 0) {
                std::cout << ". ";
            } else {
                std::cout <<grid[i][j]<<" ";
            }
            }
            std::cout<<std::endl;
        }
    }

    void SudokuUI::showMenu() {
        std::cout<< "\n Options:"<<std::endl;
        std::cout<<"1.Generate Sudoku"<<std::endl;
        std::cout<<"2.Solve Sudoku"<<std::endl;
        std::cout<<"3.Exit"<<std::endl;
        std::cout<<"Enter your choice:";
        
    }

    int SudokuUI::getChoice() {
        int choice;
        std::cin >> choice;
        return choice;
    }