#include "Board.h"
#include "Err.h"

const int numCol = 8;

Board::Board(int numRow) : size{numRow} {
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < numCol; ++j) {
            grid[i].emplace_back(Cell(i, j));
        }
    }
}

Cell& Board::getCell(int row, int col){
    if (row < size && col < numCol) {
        return grid[row][col];
    }
    throw std::out_of_range(Err::invalidCoordinates);
}

int Board::getSize() const {
    return size;
}

