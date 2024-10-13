#include <iostream>

#include "Sudoku.h"
#include "SudokuSolver.h"

using namespace std;

#define DEFAULT_FILENAME "./test.txt"

int main(int argc, char *argv[]) {
    string inputFile{DEFAULT_FILENAME};
    if(argc >= 2) {
        inputFile=argv[1];
    }

    Sudoku sudoku{inputFile};

    SudokuSolver solver{sudoku};

    solver.solveAndPrint();

    return 0;
}