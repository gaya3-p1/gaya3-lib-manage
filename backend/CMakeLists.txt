cmake_minimum_required(VERSION 3.10)

project(SudokuSolver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include)

set(SOURCES
    source/main.cpp
    source/SudokuSolver.cpp
    source/SudokuGenerator.cpp
    source/SudokuValidator.cpp
    source/SudokuUI.cpp
)

add_executable(sudoku 
        source/main.cpp
        source/SudokuSolver.cpp
        source/SudokuGenerator.cpp
        source/SudokuValidator.cpp
        source/SudokuUI.cpp
)

