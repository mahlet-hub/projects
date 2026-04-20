#include "AppController.h"
#include <iostream>
using namespace std;

AppController::AppController(Game* g){
    this->game = g;
}
void AppController::handleReveal(int row, int col){
    cout << "Reveal at: (" << row << "," << col << ")" << endl;
    game->getBoard().revealTile(row, col);
}
void AppController::handleFlag(int row, int col) {
    std::cout << "Flag at (" << row << ", " << col << ")" << std::endl;
    game->getBoard().flagTile(row, col);
}
void AppController::startGame() {
    game->startGame();
}
