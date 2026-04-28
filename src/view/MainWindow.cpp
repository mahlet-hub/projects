#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QApplication>
#include <QTimer>

MainWindow::MainWindow(Game* game, QWidget* parent)
    : QMainWindow(parent), game(game)
{
    controller = new AppController(game);

    bgSound = new QSoundEffect(this);
    bgSound->setSource(QUrl::fromLocalFile("src/view/start.wav"));
    bgSound->setLoopCount(1);
    bgSound->setVolume(1.0);

    QTimer::singleShot(200, [=]() {
        bgSound->play();
    });

    firstClickSound = new QSoundEffect(this);
    firstClickSound->setSource(QUrl::fromLocalFile("src/view/firstclick.wav"));
    firstClickSound->setVolume(0.8);


    bombRevealSound = new QSoundEffect(this);
    bombRevealSound->setSource(QUrl::fromLocalFile("src/view/bombsound.wav"));
    bombRevealSound->setVolume(0.8);


    defeatSound = new QSoundEffect(this);
    defeatSound->setSource(QUrl::fromLocalFile("src/view/defeat.wav"));
    defeatSound->setVolume(1.0);

    stackedWidget = new QStackedWidget(this);
    setCentralWidget(stackedWidget);

    setupStartPage();
    setupDifficultyPage();
    setupGameUI();
    setupGameOverPage();

    stackedWidget->addWidget(startPage);
    stackedWidget->addWidget(difficultyPage);
    stackedWidget->addWidget(gamePage);
    stackedWidget->addWidget(gameOverPage);

    stackedWidget->setCurrentWidget(startPage);

    setFixedSize(700, 800);
}

MainWindow::~MainWindow() {
    delete controller;
}


void MainWindow::setupStartPage() {
    startPage = new QWidget();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins(30, 60, 30, 30);
    layout->setSpacing(40);

    QLabel* title = new QLabel("MINESWEEPER");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(R"(
        font-size: 48px;
        font-weight: 900;
        color: black;
        font-family: 'Courier New', 'Lucida Console', monospace;
        letter-spacing: 4px;
        text-transform: uppercase;
    )");

    QPushButton* startBtn = new QPushButton("START");
    startBtn->setFixedSize(220, 70);

    startBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #98fb98;
            border-top: 4px solid #d4ffd4;
            border-left: 4px solid #d4ffd4;
            border-right: 4px solid #2a2a2a;
            border-bottom: 4px solid #2a2a2a;
            border-radius: 0px;
            color: black;
            font-family: 'Courier New', 'Lucida Console', monospace;
            font-size: 22px;
            font-weight: bold;
            letter-spacing: 3px;
            padding: 10px;
        }
        QPushButton:hover {
            background-color: #aafdaa;
        }
        QPushButton:pressed {
            background-color: #7ed67e;
            border-top: 4px solid #2a2a2a;
            border-left: 4px solid #2a2a2a;
            border-right: 4px solid #d4ffd4;
            border-bottom: 4px solid #d4ffd4;
            padding-top: 14px;
            padding-left: 14px;
        }
    )");

    layout->addWidget(title, 0, Qt::AlignTop | Qt::AlignCenter);
    layout->addStretch();
    layout->addWidget(startBtn, 0, Qt::AlignCenter);
    layout->addStretch();

    startPage->setStyleSheet("background-color: #E6D6FF;");
    startPage->setLayout(layout);

    connect(startBtn, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(difficultyPage);
    });
}

//
// ===== DIFFICULTY PAGE =====
//
void MainWindow::setupDifficultyPage() {
    difficultyPage = new QWidget();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(25);

    QLabel* title = new QLabel("Select Difficulty");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(R"(
        font-size: 36px;
        font-weight: bold;
        color: black;
        font-family: 'Courier New', 'Lucida Console', monospace;
        letter-spacing: 3px;
    )");
    layout->addWidget(title);

    QPushButton* easyBtn = new QPushButton("Easy");
    QPushButton* mediumBtn = new QPushButton("Medium");
    QPushButton* hardBtn = new QPushButton("Hard");

    QList<QPushButton*> btns = {easyBtn, mediumBtn, hardBtn};

    for (auto btn : btns) {
        btn->setFixedSize(220, 60);
        btn->setStyleSheet(R"(
            QPushButton {
                background-color: #C3B1E1;
                border-top: 4px solid #e0d4f7;
                border-left: 4px solid #e0d4f7;
                border-right: 4px solid #2a2a2a;
                border-bottom: 4px solid #2a2a2a;
                border-radius: 0px;
                color: black;
                font-family: 'Courier New', 'Lucida Console', monospace;
                font-size: 20px;
                font-weight: bold;
                letter-spacing: 2px;
                padding: 8px;
            }
            QPushButton:hover {
                background-color: #d0bff0;
            }
            QPushButton:pressed {
                background-color: #a88cd6;
                border-top: 4px solid #2a2a2a;
                border-left: 4px solid #2a2a2a;
                border-right: 4px solid #e0d4f7;
                border-bottom: 4px solid #e0d4f7;
                padding-top: 12px;
                padding-left: 12px;
            }
        )");
        layout->addWidget(btn, 0, Qt::AlignCenter);
    }

    difficultyPage->setStyleSheet("background-color: #E6D6FF;");
    difficultyPage->setLayout(layout);

    connect(easyBtn, &QPushButton::clicked, [=]() {
        game = new Game("easy");
        controller = new AppController(game);
        setupGrid();
        updateUI();
        stackedWidget->setCurrentWidget(gamePage);
    });

    connect(mediumBtn, &QPushButton::clicked, [=]() {
        game = new Game("medium");
        controller = new AppController(game);
        setupGrid();
        updateUI();
        stackedWidget->setCurrentWidget(gamePage);
    });

    connect(hardBtn, &QPushButton::clicked, [=]() {
        game = new Game("hard");
        controller = new AppController(game);
        setupGrid();
        updateUI();
        stackedWidget->setCurrentWidget(gamePage);
    });
}

//
// ===== GAME PAGE =====
//
void MainWindow::setupGameUI() {
    gamePage = new QWidget();

    QVBoxLayout* outerLayout = new QVBoxLayout();
    outerLayout->setSpacing(20);

    QLabel* title = new QLabel("M 🚩NESWEEPER");
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet(R"(
        font-size: 42px;
        font-weight: bold;
        color: black;
        font-family: 'Courier New', 'Lucida Console', monospace;
        letter-spacing: 4px;
    )");
    outerLayout->addWidget(title);

    QWidget* gridContainer = new QWidget();
    gridLayout = new QGridLayout();
    gridLayout->setSpacing(4);
    gridContainer->setLayout(gridLayout);
    outerLayout->addWidget(gridContainer);

    QPushButton* backBtn = new QPushButton("Back");
    backBtn->setFixedSize(150, 50);
    backBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #C3B1E1;
            border-top: 4px solid #e0d4f7;
            border-left: 4px solid #e0d4f7;
            border-right: 4px solid #2a2a2a;
            border-bottom: 4px solid #2a2a2a;
            border-radius: 0px;
            color: black;
            font-family: 'Courier New', 'Lucida Console', monospace;
            font-size: 16px;
            font-weight: bold;
            letter-spacing: 2px;
            padding: 6px;
        }
        QPushButton:hover {
            background-color: #d0bff0;
        }
        QPushButton:pressed {
            background-color: #a88cd6;
            border-top: 4px solid #2a2a2a;
            border-left: 4px solid #2a2a2a;
            border-right: 4px solid #e0d4f7;
            border-bottom: 4px solid #e0d4f7;
            padding-top: 10px;
            padding-left: 10px;
        }
    )");

    connect(backBtn, &QPushButton::clicked, [=]() {
        stackedWidget->setCurrentWidget(difficultyPage);
    });

    outerLayout->addWidget(backBtn, 0, Qt::AlignCenter);

    gamePage->setStyleSheet("background-color: #E6D6FF;");
    gamePage->setLayout(outerLayout);
}


void MainWindow::setupGrid() {
    QLayoutItem* item;
    while ((item = gridLayout->takeAt(0)) != nullptr) {
        delete item->widget();
        delete item;
    }

    int rows = game->getBoard().getRows();
    int cols = game->getBoard().getCols();

    buttons.clear();
    buttons.resize(rows, std::vector<QPushButton*>(cols));

    int size = 60;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            QPushButton* button = new QPushButton();
            button->setFixedSize(size, size);
            button->setStyleSheet(R"(
                QPushButton {
                    background-color: #C3B1E1;
                    border-top: 3px solid #e0d4f7;
                    border-left: 3px solid #e0d4f7;
                    border-right: 3px solid #2a2a2a;
                    border-bottom: 3px solid #2a2a2a;
                    border-radius: 0px;
                    font-size: 20px;
                    color: #1a1a1a;
                }
                QPushButton:hover {
                    background-color: #d0bff0;
                }
                QPushButton:pressed {
                    background-color: #a88cd6;
                    border-top: 3px solid #2a2a2a;
                    border-left: 3px solid #2a2a2a;
                    border-right: 3px solid #e0d4f7;
                    border-bottom: 3px solid #e0d4f7;
                }
                QPushButton:disabled {
                    background-color: #b8a8d8;
                    border: 2px solid #6a5a8a;
                    color: #1a1a1a;
                }
            )");

            gridLayout->addWidget(button, r, c);
            buttons[r][c] = button;

            connectButton(button, r, c);
        }
    }
}

void MainWindow::connectButton(QPushButton* button, int row, int col) {
    connect(button, &QPushButton::clicked, [=]() {
        bool wasFirst = game->isFirstClick();
        controller->handleReveal(row, col);
        if (wasFirst) firstClickSound->play();
        updateUI();
    });
}


void MainWindow::setupGameOverPage() {
    gameOverPage = new QWidget();
    gameOverPage->setStyleSheet("background-color: #E6D6FF;");

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setAlignment(Qt::AlignCenter);
    layout->setSpacing(40);

    QLabel* bombLabel = new QLabel("💣");
    bombLabel->setAlignment(Qt::AlignCenter);
    bombLabel->setStyleSheet("font-size: 80px;");

    QLabel* gameOverLabel = new QLabel("GAME OVER");
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->setStyleSheet(R"(
        font-size: 48px;
        font-weight: 900;
        color: black;
        font-family: 'Courier New', 'Lucida Console', monospace;
        letter-spacing: 4px;
    )");

    QPushButton* restartBtn = new QPushButton("MENU");
    restartBtn->setFixedSize(220, 70);
    restartBtn->setStyleSheet(R"(
        QPushButton {
            background-color: #98fb98;
            border-top: 4px solid #d4ffd4;
            border-left: 4px solid #d4ffd4;
            border-right: 4px solid #2a2a2a;
            border-bottom: 4px solid #2a2a2a;
            border-radius: 0px;
            color: black;
            font-family: 'Courier New', 'Lucida Console', monospace;
            font-size: 22px;
            font-weight: bold;
            letter-spacing: 3px;
            padding: 10px;
        }
        QPushButton:hover {
            background-color: #aafdaa;
        }
        QPushButton:pressed {
            background-color: #7ed67e;
            border-top: 4px solid #2a2a2a;
            border-left: 4px solid #2a2a2a;
            border-right: 4px solid #d4ffd4;
            border-bottom: 4px solid #d4ffd4;
            padding-top: 14px;
            padding-left: 14px;
        }
    )");

    connect(restartBtn, &QPushButton::clicked, [=]() {
        defeatSound->stop();
        bgSound->play();
        stackedWidget->setCurrentWidget(startPage);
    });

    layout->addWidget(bombLabel);
    layout->addWidget(gameOverLabel);
    layout->addWidget(restartBtn, 0, Qt::AlignCenter);

    gameOverPage->setLayout(layout);
}



void MainWindow::updateUI() {
    int rows = game->getBoard().getRows();
    int cols = game->getBoard().getCols();

    static const QStringList bombColors = {
        "#4fc3f7", 
        "#26c6da",  
        "#fff176",  
        "#a5d6a7",  
        "#ffb74d"   
    };

    int bombColorIndex = 0;

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            QPushButton* button = buttons[r][c];
            Square& square = game->getBoard().getSquare(r, c);

            if (square.getIsRevealed()) {
                if (square.getIsBomb()) {
                    
                    QString color = bombColors[bombColorIndex % bombColors.size()];
                    bombColorIndex++;
                    button->setText("💣");
                    button->setEnabled(false);
                    button->setStyleSheet(QString(R"(
                        QPushButton {
                            background-color: %1;
                            border: 2px solid #2a2a2a;
                            border-radius: 0px;
                            font-size: 20px;
                            text-align: top;
                            text-align: left;
                            
                        }
                        QPushButton:disabled {
                            background-color: %1;
                            border: 2px solid #2a2a2a;
                            color: #000000;
                        }
                    )").arg(color));
                } else {
                    int count = square.getAdjacentBomb();
                    button->setEnabled(false);
                    if (count > 0) {
                        button->setText(QString::number(count));
                        button->setStyleSheet(R"(
                            QPushButton {
                                background-color: #f48fb1;
                                border: 2px solid #2a2a2a;
                                border-radius: 0px;
                                font-size: 20px;
                                font-weight: bold;
                                color: #1a1a1a;
                                text-align: top;
                                text-align: left;
                            }
                            QPushButton:disabled {
                                background-color: #f48fb1;
                                border: 2px solid #2a2a2a;
                                color: #1a1a1a;
                            }
                        )");
                    } else {
                        // Light purple for blank tiles
                        button->setText("");
                        button->setStyleSheet(R"(
                            QPushButton {
                                background-color: #e1d5f5;
                                border: 2px solid #b39ddb;
                                border-radius: 0px;
                                font-size: 20px;
                                text-align: top;
                                text-align: left;
                            }
                            QPushButton:disabled {
                                background-color: #e1d5f5;
                                border: 2px solid #b39ddb;
                            }
                        )");
                    }
                }
            }
            else if (square.getIsFlagged()) {
                button->setText("🚩");
            }
            else {
                button->setText("");
                button->setEnabled(true);
            }
        }
    }

    std::string state = game->getGameState();

    if (state == "lost") {

        QList<QPair<int,int>> bombPositions;
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < cols; c++) {
                Square& sq = game->getBoard().getSquare(r, c);
                if (sq.getIsBomb() && !sq.getIsRevealed()) {
                    bombPositions.append({r, c});
                }
            }
        }


        for (int r = 0; r < rows; r++)
            for (int c = 0; c < cols; c++)
                buttons[r][c]->setEnabled(false);


        static const QStringList bombColors = {
            "#4fc3f7", "#26c6da", "#fff176", "#a5d6a7", "#ffb74d"
        };

        for (int i = 0; i < bombPositions.size(); i++) {
            int r = bombPositions[i].first;
            int c = bombPositions[i].second;
            QString color = bombColors[i % bombColors.size()];
            QPushButton* btn = buttons[r][c];

            QTimer::singleShot(i * 300, [=]() {
                game->getBoard().getSquare(r, c).reveal();
                btn->setText("💣");
                btn->setStyleSheet(QString(R"(
                    QPushButton {
                        background-color: %1;
                        border: 2px solid #2a2a2a;
                        border-radius: 0px;
                        font-size: 20px;
                        text-align: top;
                        text-align: left;
                    }
                    QPushButton:disabled {
                        background-color: %1;
                        border: 2px solid #2a2a2a;
                        color: #000000;
                    }
                )").arg(color));
                bombRevealSound->play();
            });
        }


        int totalDelay = bombPositions.size() * 300 + 600;
        QTimer::singleShot(totalDelay, [=]() {
            bgSound->stop();
            defeatSound->play();
            stackedWidget->setCurrentWidget(gameOverPage);
        });
    }

    if (state == "won") {
        QMessageBox::information(this, "You Win!", "🎉 Congratulations!");
    }
}