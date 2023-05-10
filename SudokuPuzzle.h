#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <fstream>




class SudokuPuzzle
{
public:
    SudokuPuzzle();
    ~SudokuPuzzle();

    void load(const char filenameIn[]);
    void solve();
    void output(const char filenameOut[]) const;

private:
    std::chrono::duration<double, std::micro> _loadTime;
    std::chrono::duration<double, std::micro> _solveTime;
};
    
    

    
class Cell {
public:
    int value;
    bool isFixed = false;
    

private:
   
};

const int N = 9;
const int UNASSIGNED = 0;

class Sudoku {
public:
    int grid[N][N];
    bool isSolved = false;
    int cellsSolved = 0;
    int candidatesConsidered = 0;
    int passes = 0;

    void printGrid() {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool findUnassigned(int& row, int& col) {
        for (row = 0; row < N; row++) {
            for (col = 0; col < N; col++) {
                if (grid[row][col] == UNASSIGNED) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isSafe(int row, int col, int value) {
        // check row
        for (int j = 0; j < N; j++) {
            if (grid[row][j] == value) {
                return false;
            }
        }
        // check column
        for (int i = 0; i < N; i++) {
            if (grid[i][col] == value) {
                return false;
            }
        }
        // check block
        int blockRow = row - row % 3;
        int blockCol = col - col % 3;
        for (int i = blockRow; i < blockRow + 3; i++) {
            for (int j = blockCol; j < blockCol + 3; j++) {
                if (grid[i][j] == value) {
                    return false;
                }
            }
        }
        return true;
    }

    bool solve() {
        int row, col;
        if (!findUnassigned(row, col)) {
            isSolved = true;
            return true;
        }
        for (int num = 1; num <= N; num++) {
            candidatesConsidered++;
            if (isSafe(row, col, num)) {
                grid[row][col] = num;
                cellsSolved++;
                if (solve()) {
                    return true;
                }
                grid[row][col] = UNASSIGNED;
            }
        }
        passes++;
        return false;
    }
    int mainfunction() {
        Sudoku mypuzzle;

        // read puzzle from file
        std::ifstream infile("sudoku_puzzle.txt");
        if (!infile) {
            std::cerr << "Error: File could not be opened" << std::endl;
            return 1;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                infile >> mypuzzle.grid[i][j];
            }
        }
        infile.close();
        

        std::cout << "Sudoku puzzle:" << std::endl;
        mypuzzle.printGrid();

        if (mypuzzle.solve()) {
            std::cout << "\nSudoku solution:" << std::endl;
            mypuzzle.printGrid();
            std::cout << "Cells solved: " << mypuzzle.cellsSolved << std::endl;
            std::cout << "Candidate values considered: " << mypuzzle.candidatesConsidered << std::endl;
            std::cout << "Passes through grid: " << mypuzzle.passes << std::endl;
        }
        else {
            std::cout << "No solution exists for the given puzzle" << std::endl;
        }
        std::ofstream outfile("sudoku_solution.txt");
        if (outfile.is_open()) {
            for (int i = 0; i < 9; ++i) {
                for (int j = 0; j < 9; ++j) {
                    outfile << mypuzzle.grid[i][j] << " "; 
                }
                outfile << std::endl; 
            } 
            outfile.close();
            std::cout << "Solved Sudoku written to solution_puzzle.txt" << std::endl;
        }
        else {
            std::cout << "Error: Could not open file for writing." << std::endl;
        }
    }
};

