#include "model/game.h"
#include "controller/AppController.h"

int main() {
    //creates/instantiates the game
    Game game("easy");     
    //instantiate controller            
    AppController controller(&game);   

    return 0;
}