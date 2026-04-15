#include "controller/AppController.h"
#include "model/MessageModel.h"
#include "view/MainWindow.h"

#include <QObject>
#include <QString>
#include <QPushButton>

AppController::AppController(MessageModel* model, MainWindow* view)
    : model(model), view(view) {}

void AppController::initialize() {
    view->setMessage(QString::fromStdString(model->getMessage()));

    QObject::connect(
        view->getUpdateButton(),
        &QPushButton::clicked,
        [this]() {
            handleUpdateMessage();
        }
    );
}

void AppController::handleUpdateMessage() {
    std::string newMessage = view->getInputText().toStdString();
    model->setMessage(newMessage);
    view->setMessage(QString::fromStdString(model->getMessage()));
}