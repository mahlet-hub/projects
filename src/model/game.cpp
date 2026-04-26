#include "game.h"
 
Game::Game(std::string difficulty) {
    this->difficulty = difficulty;
    gameState = "playing";
    firstClick = true;
 
    if (difficulty == "easy") {
        board = Board(9, 9, 10);
    } else if (difficulty == "medium") {
        board = Board(16, 16, 40);
    } else {
        board = Board(16, 30, 99);
    }
}
 
void Game::startGame() {
    gameState = "playing";
}
 
void Game::resetGame() {
    *this = Game(difficulty);
}
 
bool Game::checkWin() {
    int rows = board.getRows();
    int cols = board.getCols();
 
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            Square& sq = board.getSquare(r, c);
            
            if (!sq.getIsBomb() && !sq.getIsRevealed()) {
                return false;
            }
        }
    }
    return true;
}
 
void Game::endGame(bool hitMine) {
    gameState = hitMine ? "lost" : "won";
}
 
std::string Game::getGameState() const {
    return gameState;
}
 
Board& Game::getBoard() {
    return board;
}
 
std::string Game::getDifficulty() const {
    return difficulty;
}
 
bool Game::isFirstClick() const {
    return firstClick;
}
 
void Game::setFirstClick(bool val) {
    firstClick = val;
}
 