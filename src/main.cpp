#include <iostream>
#include "model/game.h"
#include "controller/AppController.h"
#include "model/MessageModel.h"

int main() {
    //creates/instantiates the game
    Game game("easy");     
    //instantiate controller            
    AppController controller(&game);   
    MessageModel msg;

    msg.setMessage("Game started successfully!");

    
    std::cout << msg.getMessage() << std::endl;

    MessageModel model;
    model.setMessage("hello");
    std::cout << model.getMessage() << std::endl;

    return 0;
}