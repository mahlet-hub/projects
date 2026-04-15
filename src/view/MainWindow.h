#pragma once

#include <QMainWindow>

class QLabel;
class QLineEdit;
class QPushButton;

class MainWindow : public QMainWindow {
public:
    MainWindow();

    void setMessage(const QString& text);
    QString getInputText() const;

    QPushButton* getUpdateButton() const;

private:
    QLabel* label;
    QLineEdit* input;
    QPushButton* updateButton;
};