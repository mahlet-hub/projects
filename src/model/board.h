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
        int numFlags;
    public:
        // Constructors
        
        Board(string difficulty);

        // Places bombs on the board
        void placeBombs(int initRow, int initCol);

        // Computes adjacent bomb counts for non-bomb squares
        void calculateAdjBomb();

        // Getters
        int getRows() const;
        int getCols() const;
        int getNumBombs() const;

        // Counts bombs around a square
        int countAdjBombs(int row, int col) const;

        // Reveals a single tile
        void revealTile(int row, int col);

        // Toggles flag on a tile
        void flagTile(int row, int col);

        // Reveals adjacent blank/numbered squares
        void revealAdjBlanks(int row, int col);

        // Checks if a position is inside the board
        bool inBounds(int row, int col) const;

};