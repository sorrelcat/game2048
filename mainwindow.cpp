#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow()
{
    board = new Board();

    startButton = new QPushButton(tr("&Start"));
    startButton->setFocusPolicy(Qt::NoFocus);

    pauseButton = new QPushButton(tr("&Pause"));
    pauseButton->setFocusPolicy(Qt::NoFocus);

    scoreLcd = new QLCDNumber(7);
    winLoseLabel = new QLabel();

    connect(startButton, &QPushButton::clicked, board, &Board::start);
    connect(board, &Board::scoreChanged, scoreLcd, QOverload<int>::of(&QLCDNumber::display));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(board, 0, 0, 2, 2);
    layout->addWidget(scoreLcd, 1, 1);
    layout->addWidget(startButton, 1, 0);

    setLayout(layout);

    scoreLcd->setFixedHeight(50);
    startButton->setFixedHeight(50);

    setFixedSize(DEFAULT_WINDOW_WIDTH + BORDER_SIZE, DEFAULT_WINDOW_HEIGHT + ADDITIONAL_SIZE);
    setWindowTitle("2048");
}

