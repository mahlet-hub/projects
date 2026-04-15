#include <QApplication>

#include "model/MessageModel.h"
#include "view/MainWindow.h"
#include "controller/AppController.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MessageModel model;
    MainWindow view;
    AppController controller(&model, &view);

    controller.initialize();
    view.show();

    return app.exec();
}