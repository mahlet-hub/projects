#ifndef GAME_H
#define GAME_H
#include <string>
#include "board.h"
#include "square.h"
 
class Game {
private:
    Board board;
    std::string gameState;
    std::string difficulty;
    bool firstClick;
 
public:
    // Constructor
    Game(std::string difficulty);
 
    // Methods
    void startGame();
    void resetGame();
    bool checkWin();
    void endGame(bool hitMine);
 

    bool isFirstClick() const;
    void setFirstClick(bool val);
 
    // Getters
    std::string getGameState() const;
    Board& getBoard();
    std::string getDifficulty() const;
};
 
#endif
 