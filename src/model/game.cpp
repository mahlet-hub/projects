#include "game.h"

Game::Game(std::string difficulty) {}
void Game::startGame() {}
void Game::resetGame() {}
bool Game::checkWin() { return false; }
void Game::endGame(bool hitMine) {}
std::string Game::getGameState() const { return ""; }
Board& Game::getBoard() { return board; }
std::string Game::getDifficulty() const { return ""; }
