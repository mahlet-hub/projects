#ifndef GAME_H
#define GAME_H

#include <string>
#include "board.h"

class Game {
private:
    Board board;
    std::string gameState;
    std::string difficulty;

public:
    //Constructor

    Game(std::string difficulty);

    //Methods

    void startGame();
    void resetGame();
    bool checkWin();  
    void endGame(bool hitMine);

    //Getters
    std::string getGameState() const;
    Board& getBoard();
    std::string getDifficulty() const;
};

#endif