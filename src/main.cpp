#include <QApplication>

#include "model/MessageModel.h"
#include "view/MainWindow.h"
#include "controller/AppController.h"

#include "model/game.h"
#include "model/MessageModel.h"
#include "model/square.h"

int main() {
    // MessageModel model;
    // MainWindow view;
    // AppController controller(&model, &view);

    AppController controller;
    AppController(&model, &view);
    controller.startGame();

    return 0;
}