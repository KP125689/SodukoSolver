#include <iostream>
#include <fstream> 
#include "SudokuPuzzle.h"

using namespace std; 
 
SudokuPuzzle::SudokuPuzzle() : 
	_loadTime(std::chrono::duration<double>(0)),
	_solveTime(std::chrono::duration<double>(0)) 
{
}

SudokuPuzzle::~SudokuPuzzle() {
	std::cout << "Time to load: " << _loadTime.count() << " microseconds" << std::endl;
	std::cout << "Time to solve: " << _solveTime.count() << " microseconds" << std::endl;
	
}
void SudokuPuzzle::load(const char filenameIn[]) {
	const auto start = std::chrono::high_resolution_clock::now();

	const auto end = std::chrono::high_resolution_clock::now();
	_loadTime = end - start;
}

void SudokuPuzzle::solve() {
	const auto start = std::chrono::high_resolution_clock::now();
	// Add your code here to solve the puzzle
	Sudoku run;
	run.mainfunction(); 
	
	const auto end = std::chrono::high_resolution_clock::now();
	_solveTime = end - start;
}

// This is an example of how you may output the solved puzzle
void SudokuPuzzle::output(const char filenameOut[]) const {

	// Add your code here to write your solution to the file filenameOut
	

}
