#ifndef BOARD_H
#define BOARD_H

#include "cell.h"
#include "constants.h"
#include <QWidget>
#include <QPainter>
#include <QFrame>
#include <QLabel>
#include <QKeyEvent>
#include <QPaintEvent>
#include <QRect>
#include <vector>
#include <stack>

class Board : public QFrame
{
    Q_OBJECT

public:
    Board(QWidget *parent = 0, int s = DEFAULT_SIZE_IN_CELLS);

public slots:
    void start();

signals:
    void scoreChanged(int score);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:

    int size;
    std::vector<std::vector<Cell>> cells;
    std::stack<std::vector<std::vector<Cell>>> states;
    std::stack<int> scores;

    void drawSquare(QPainter &painter, int x, int y, Cell cell);
    void clearBoard();

    void clearNullCellsUp();
    void moveUp();

    void clearNullCellsDown();
    void moveDown();

    void clearNullCellsLeft();
    void moveLeft();

    void clearNullCellsRight();
    void moveRight();

    void generateNewCellValue();
    void renewMaxCellAndScore(int v);

    bool areZeroCells();
    bool areSameNeighbourCells();

    void stepBack();
    void renewStacks();

    bool isStarted;
    int score;
    int maxCell;
    bool winFlag;
    bool loseFlag;
};

#endif // BOARD_H
