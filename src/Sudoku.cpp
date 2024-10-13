#include "Sudoku.h"
#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <unordered_set>
#include "utils.h"
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

Sudoku::Sudoku(string filename): matrix{{}}, coloredCells{} {
    ifstream inputFile(filename);
    string lineText;

    if(!inputFile) {
        throw invalid_argument("File name " + filename + " does not exist !");
    }

    for(int line=0; getline(inputFile, lineText) && line < 9 && inputFile.good(); line++) {
        for(int column=0; column < 9 && column < lineText.length(); column++) {
            char value=lineText[column]-'0';

            if(1 <= value && value <= 9) {//if the value is valid
                setCellValue(line, column, value);
            }
            else {
                setCellValue(line, column, BLANK_VALUE);
            }
        } 
    }
}

void Sudoku::checkIndexValidity(int lineIndex, int columnIndex) {
    if(lineIndex < 0 || lineIndex > 8 || 0 > columnIndex || columnIndex > 8) {
        throw invalid_argument("Indexes " + to_string(lineIndex) + " " + to_string(columnIndex) +  " don't match the sudoku limits !");
    }
}


unsigned int Sudoku::getCellValue(int line, int column) const {
    Sudoku::checkIndexValidity(line, column);

    return matrix[line][column];
}

bool Sudoku::isCellBlank(int line, int column) const {
    Sudoku::checkIndexValidity(line, column);

    return matrix[line][column]==BLANK_VALUE;
}

bool Sudoku::checkLineValid(int line, bool skipBlankValues) const {
    Sudoku::checkIndexValidity(line, 0);

    unordered_set<unsigned int> presentValues;
    for(int column=0; column<9; column++) {
        unsigned int currentValue=matrix[line][column];
        if(currentValue != BLANK_VALUE && presentValues.find(currentValue) == presentValues.end()) {//if not blank and not present
            presentValues.insert(currentValue);
        }
        else if(currentValue != BLANK_VALUE) {
            return false;
        }
        else if(!skipBlankValues) {
            return false;
        }
    }

    return true;
}

bool Sudoku::checkColumnValid(int column, bool skipBlankValues) const {
    Sudoku::checkIndexValidity(0, column);

    unordered_set<unsigned int> presentValues;
    for(int line=0; line<9; line++) {
        unsigned int currentValue=matrix[line][column];
        if(currentValue != BLANK_VALUE && presentValues.find(currentValue) == presentValues.end()) {
            presentValues.insert(currentValue);
        }
        else if(currentValue != BLANK_VALUE) {
            return false;
        }
        else if(!skipBlankValues) {
            return false;
        }
    }

    return true;
}

/**
    Checks the 3x3 group of cells around the given cell coordinates
 */
bool Sudoku::checkCellGroup(int line, int column, bool skipBlankValues) const {
    Sudoku::checkIndexValidity(line, column);

    int lineGroup=line - (line%3);
    int columnGroup=column - (column%3);

    unordered_set<unsigned int> presentValues;
    for(int lineOffset=0; lineOffset<3; lineOffset++) {
        for(int columnOffset=0; columnOffset<3; columnOffset++) {
            unsigned int currentValue=matrix[lineGroup + lineOffset][columnGroup + columnOffset];
            if(currentValue != BLANK_VALUE && presentValues.find(currentValue) == presentValues.end()) {
                presentValues.insert(currentValue);
            }
            else if(currentValue != BLANK_VALUE) {
                return false;
            }
            else if (!skipBlankValues) {
                return false;
            }
        }
    }

    return true;
}

bool Sudoku::checkWholeCompleteValidity(bool skipBlankValues) const {
    for(int line=0; line < 9; line++) {
        if(!checkLineValid(line, skipBlankValues)) return false;
    }

    for(int column=0; column < 9; column++) {
        if(!checkColumnValid(column, skipBlankValues)) return false;
    }
    
    for(int line=0; line < 9; line+=3) {
        for(int column=0; column<9; column+=3) {
            if(!checkCellGroup(line, column, skipBlankValues)) return false;
        }
    }
    return true;
}

void Sudoku::setCellValue(int line, int column, unsigned int value) {
    Sudoku::checkIndexValidity(line, column);

    matrix[line][column]=value;
}





/* printing methods */

array<string, 9> Sudoku::getPrintableMatrix() const {
    array<string, 9> textArray{{""}};

    for(int line=0; line < 9; line++) {
        for(int column=0; column<9; column++) {
            unsigned int value=matrix[line][column];
            
            bool shouldColorValue=false;
            
            if(std::find(coloredCells.begin(), coloredCells.end(), pair<int, int>{line, column}) != coloredCells.end()) {
                shouldColorValue=true;
                textArray[line]+="\x1B[32m";
            }

            
            textArray[line]+=(value == BLANK_VALUE) ? "-" : to_string(value);
            if(shouldColorValue) textArray[line]+="\033[0m";
            textArray[line]+=" ";
        }
        if(checkLineValid(line, false)) {
            textArray[line]=string{"\x1B[34m"}+textArray[line]+"\033[0m";//add yellow colors prefix and suffixes to the line
        }
    }

    return textArray;
}

void Sudoku::setGreenColorForCell(int line, int column) {
    Sudoku::checkIndexValidity(line, column);

    coloredCells.push_back({line, column});
}

void Sudoku::resetColors() {
    coloredCells.clear();
}

ostream& operator<<(ostream& out, Sudoku const &sudoku) {//TODO: improve by not creating a useless string matrix
    for(string const& line : sudoku.getPrintableMatrix()) {
        out << line << endl;
    }

    return out;
}