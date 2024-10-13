#ifndef SUDOKU_H
#define SUDOKU_H

#include <array>
#include <string>
#include <iostream>
#include <vector>
#include <utility>

#define BLANK_VALUE 0

class Sudoku {
    public:
    Sudoku() = default;
    Sudoku(std::string filename);

    unsigned int getCellValue(int line, int column) const;

    bool isCellBlank(int line, int column) const;
    bool checkLineValid(int line, bool skipBlankValues) const;
    bool checkColumnValid(int column, bool skipBlankValues) const;
    bool checkCellGroup(int line, int column, bool skipBlankValues) const;
    bool checkWholeCompleteValidity(bool skipBlankValues) const;

    void setCellValue(int line, int column, unsigned int value);

    std::array<std::string, 9> getPrintableMatrix() const;
    void setGreenColorForCell(int line, int column);
    void resetColors();


    friend std::ostream& operator<<(std::ostream& out, Sudoku const &sudoku);

    static void checkIndexValidity(int lineIndex, int columnIndex);

    private:
        std::array<std::array<unsigned int, 9>, 9> matrix;//first dimension = lines, second dimension = columns
        std::vector<std::pair<int, int>> coloredCells;
};


#endif //Sudoku.h