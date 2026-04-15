#pragma once

class MessageModel;
class MainWindow;

class AppController {
public:
    AppController(MessageModel* model, MainWindow* view);

    void initialize();
    void handleUpdateMessage();

private:
    MessageModel* model;
    MainWindow* view;
};