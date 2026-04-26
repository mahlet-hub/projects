#include "board.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

void Board::initGrid() {
    grid.assign(rows, vector<Square>(cols));
}

Board::Board() : rows(9), cols(9), numBombs(10) {
    initGrid();
}

Board::Board(string difficulty) {
    if (difficulty == "medium") {
        rows = 11; cols = 11; numBombs = 21;
    } else if (difficulty == "hard") {
        rows = 18; cols = 18; numBombs = 35;
    } else {
        rows = 8; cols = 8; numBombs = 10;
    }
    initGrid();
}

void Board::placeBombs(int initRow, int initCol) {
    srand(time(0));

    vector<pair<int,int>> potentialBombs;
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (abs(r - initRow) <= 1 && abs(c - initCol) <= 1) continue;
            potentialBombs.push_back({r, c});
        }
    }

    for (int i = potentialBombs.size() - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(potentialBombs[i], potentialBombs[j]);
    }

    for (int i = 0; i < numBombs; i++) {
        grid[potentialBombs[i].first][potentialBombs[i].second].setBomb();
    }
}

void Board::calculateAdjBomb() {
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (!grid[r][c].getIsBomb()) {
                grid[r][c].setAdjacentBomb(countAdjBombs(r, c));
            }
        }
    }
}

Square& Board::getSquare(int row, int col) {
    return grid[row][col];
}

const Square& Board::getSquare(int row, int col) const {
    return grid[row][col];
}

int Board::getRows() const { return rows; }
int Board::getCols() const { return cols; }
int Board::getNumBombs() const { return numBombs; }

int Board::countAdjBombs(int row, int col) const {
    int count = 0;
    for (int dr = -1; dr <= 1; dr++) {
        for (int dc = -1; dc <= 1; dc++) {
            if (dr == 0 && dc == 0) continue;
            int r = row + dr, c = col + dc;
            if (inBounds(r, c) && grid[r][c].getIsBomb()) count++;
        }
    }
    return count;
}

bool Board::inBounds(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}
