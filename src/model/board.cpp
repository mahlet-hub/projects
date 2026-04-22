#include "board.h"
using namespace std;

#include <string>


Board::Board(string difficulty) {}
void Board::placeBombs(int initRow, int initCol) {}
void Board::calculateAdjBomb() {}
int Board::getRows() const { return 0; }
int Board::getCols() const { return 0; }
int Board::getNumBombs() const { return 0; }
int Board::countAdjBombs(int row, int col) const { return 0; }
void Board::revealAdjBlanks(int row, int col) {}
bool Board::inBounds(int row, int col) const { return false; }
void Board::revealTile(int row, int col) {}
void Board::flagTile(int row, int col) {}
