#pragma once

#include <vector>
#include <string>
#include "square.h"
using namespace std;

class Board {
private:
    vector<vector<Square>> grid;
    int rows;
    int cols;
    int numBombs;

    void initGrid();

public:
    Board();
    Board(string difficulty);

    // Called after first click — excludes 3x3 neighborhood of (initRow, initCol)
    void placeBombs(int initRow, int initCol);

    // Sets adjacentBombs on every non-bomb square
    void calculateAdjBomb();

    // Access a square in the grid
    Square& getSquare(int row, int col);
    const Square& getSquare(int row, int col) const;

    // Getters
    int getRows() const;
    int getCols() const;
    int getNumBombs() const;

    // Counts bombs in the 8 neighbors of (row, col)
    int countAdjBombs(int row, int col) const;

    bool inBounds(int row, int col) const;
};
