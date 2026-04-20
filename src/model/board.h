#pragma once

#include <vector>
#include "square.h"
using namespace std;

class Board {
    private:
    vector<vector<Square>> grid;
        int rows;
        int cols;
        int numBombs;
    public:
        // Constructor
        Board(int rows, int cols, int numBombs);

        // Places bombs on the board
        void placeBombs();

        // Computes adjacent bomb counts for non-bomb squares
        void calculateAdjBomb();

        // Getters
        int getRows() const;
        int getCols() const;
        int getNumBombs() const;

        // Counts bombs around a square
        int countAdjBombs(int row, int col) const;

        // Reveals adjacent blank/numbered squares
        void revealAdjBlanks(int row, int col);

        // Checks if a position is inside the board
        bool inBounds(int row, int col) const;

};