#include "SudokuSolver.h"
#include "SearchNode.h"
#include <vector>
#include <iostream>
#include <utility>
#include <chrono>
#include <thread>
#include "utils.h"

#define UNDEFINED_PARENT_PTR shared_ptr<SearchNode>{}
#define SLEEP_MS_DELAY 10

using namespace std;

SudokuSolver::SudokuSolver(Sudoku _sudoku) : sudoku{_sudoku} {}

void SudokuSolver::solveAndPrint() {
    SearchNode current{UNDEFINED_PARENT_PTR, getNextBlankCell()};

    activateVirtualTerminal();

    clearTerminal();

    while(!sudoku.checkWholeCompleteValidity(false)) {
        //first, we try every possibility for that cell
        bool hasFoundCorrectValue=false;
        for(int possible_value=current.getLastValueTried()+1; possible_value<=9; possible_value++) {
            sudoku.setCellValue(current.getX(), current.getY(), possible_value);

            current.setLastValueTried(possible_value);

            this_thread::sleep_for(chrono::milliseconds(SLEEP_MS_DELAY));

            resetCursorPosition();//so it prints over the last sudoku printed, and not under it
            sudoku.resetColors();
            sudoku.setGreenColorForCell(current.getX(), current.getY());
            cout << sudoku;

            if(sudoku.checkWholeCompleteValidity(true)) {
                hasFoundCorrectValue=true;
                current=SearchNode(make_shared<SearchNode>(current), getNextBlankCell());
                break;
            }
            else {
                sudoku.setCellValue(current.getX(), current.getY(), BLANK_VALUE);
            }
        }

        if(!hasFoundCorrectValue) {
            //then, we need to get higher in the nodes
            while(current.getLastValueTried() >= 9) {
                if(current.getParent()==nullptr) {
                    throw invalid_argument("The sudoku provided in the file is not solvable !");
                }

                current=*current.getParent();
            }
        }
    }

    cout << "SOLUTION FOUND !" << endl;
}

pair<int, int> SudokuSolver::getNextBlankCell() const {
    for(int line=0; line<9;line++) {
        for(int column=0; column<9; column++) {
            if(sudoku.getCellValue(line, column)==BLANK_VALUE) {
                return {line, column};
            }
        }
    }

    return {-1, -1};//if no blank cells are found anymore
}