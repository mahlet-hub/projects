#include "AppController.h"
#include <iostream>
using namespace std;

AppController::AppController(Game* g){
    this->game = g;
}
void AppController::startGame() {
    game->startGame();
}
