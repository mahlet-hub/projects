#include "square.h"

Square::Square() : isBomb(false), isRevealed(false), isFlagged(false), adjacentBombs(0) {}

void Square::setBomb() { 
    isBomb = true; 
}

void Square::reveal() {   
    isRevealed = true; 
}

void Square::toggleFlag() { 
    isFlagged = !isFlagged; 
}

void Square::setAdjacentBomb(int num) { 
    adjacentBombs = num; 
}

int Square::getAdjacentBomb() const { 
    return adjacentBombs; 
}

bool Square::getIsBomb() const { 
    return isBomb; 
}

bool Square::getIsRevealed() const { 
    return isRevealed; 
}

bool Square::getIsFlagged() const { 
    return isFlagged; 
}
