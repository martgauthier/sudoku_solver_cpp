#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include "Sudoku.h"
#include <utility>

class SudokuSolver {
    public:
    SudokuSolver(Sudoku sudoku);
    void solveAndPrint();
    std::pair<int, int> getNextBlankCell() const;

    private:
    Sudoku sudoku;
};

#endif //SudokuSolver.h