#include "board.h"

Board::Board(QWidget *parent, int s) :  QFrame(parent), size(s)
{
   setFocusPolicy(Qt::StrongFocus);
   Cell t(0, 0);
   cells = std::vector<std::vector<Cell>> (size, std::vector<Cell> (size, t));
   start();
}

void Board::clearBoard() {
    for (size_t i = 0; i < cells.size(); ++i) {
        for(size_t j = 0; j < cells[0].size(); ++j) {
            cells[i][j].setCell(0, 0);
        }
    }
}

void Board::drawSquare(QPainter &painter, int x, int y, Cell cell) {

    painter.fillRect(x, y, DEFAULT_CELL_SIZE, DEFAULT_CELL_SIZE, QColor(224, 224, 224));
    painter.fillRect(x+2, y+2, DEFAULT_CELL_SIZE-4, DEFAULT_CELL_SIZE-4, cell.getCellColor());
    if(cell.getValue() != 0) {
        QFont font;
        painter.setPen(BASE_FONT_COLOR);
        font.setPixelSize(30);
        painter.setFont(font);
        int yIndent = DEFAULT_CELL_SIZE / 2 + 7;
        int xIndent = DEFAULT_CELL_SIZE / 2 - 7 - (cell.getIntColor() - 1) / 3 * 6;
        painter.drawText(x + xIndent, y + yIndent, QString::number(cell.getValue()));
    }
}

void Board::clearNullCellsUp()  {
    for(int i = 0; i < size; ++i) {
        for(int j = 0, k = 0; j < size; ++j) {
            if(cells[i][j].getValue() != 0) {
                if(j != k) {
                    cells[i][k] = cells[i][j];
                    cells[i][j].setCell(0, 0);
                }
                ++k;
            }
        }
    }
}

void Board::clearNullCellsDown()  {
    for(int i = 0; i < size; ++i) {
        for(int j = size - 1, k = size-1; j >= 0; --j) {
            if(cells[i][j].getValue() != 0) {
                if(j != k) {
                    cells[i][k] = cells[i][j];
                    cells[i][j].setCell(0, 0);
                }
                --k;
            }
        }
    }
}

void Board::clearNullCellsLeft()  {
    for(int i = 0; i < size; ++i) {
        for(int j = 0, k = 0; j < size; ++j) {
            if(cells[j][i].getValue() != 0) {
                if(j != k) {
                    cells[k][i] = cells[j][i];
                    cells[j][i].setCell(0, 0);
                }
                ++k;
            }
        }
    }
}

void Board::clearNullCellsRight()  {
    for(int i = 0; i < size; ++i) {
        for(int j = size - 1, k = size-1; j >= 0; --j) {
            if(cells[j][i].getValue() != 0) {
                if(j != k) {
                    cells[k][i] = cells[j][i];
                    cells[j][i].setCell(0, 0);
                }
                --k;
            }
        }
    }
}

void Board::moveUp() {
    clearNullCellsUp();
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size-1; ++j) {
            if(cells[i][j].getValue() != 0 && cells[i][j].getValue() == cells[i][j+1].getValue()) {
                cells[i][j].increment();
                cells[i][j+1].setCell(0, 0);
                renewMaxCell(cells[i][j].getValue());
                emit scoreChanged(score);
                ++j;
            }
        }
    }
    clearNullCellsUp();
    update();
}

void Board::moveDown() {
    clearNullCellsDown();
    for(int i = 0; i < size; ++i) {
        for(int j = size - 1; j >= 0; --j) {
            if(cells[i][j].getValue() == cells[i][j+1].getValue() && cells[i][j].getValue() != 0) {
                cells[i][j].increment();
                cells[i][j+1].setCell(0, 0);
                renewMaxCell(cells[i][j].getValue());
                emit scoreChanged(score);
                --j;
            }
        }
    }
    clearNullCellsDown();
    update();
}

void Board::moveLeft() {
    clearNullCellsLeft();
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size-1; ++j) {
            if(cells[j][i].getValue() == cells[j+1][i].getValue() && cells[j][i].getValue() != 0) {
                cells[j][i].increment();
                cells[j+1][i].setCell(0, 0);
                renewMaxCell(cells[j][i].getValue());
                emit scoreChanged(score);
                ++j;
            }
        }
    }
    clearNullCellsLeft();
    update();
}

void Board::moveRight() {
    clearNullCellsRight();
    for(int i = 0; i < size; ++i) {
        for(int j = size - 1; j > 0; --j) {
            if(cells[j][i].getValue() == cells[j-1][i].getValue() && cells[j][i].getValue() != 0) {
                cells[j-1][i].increment();
                cells[j][i].setCell(0, 0);
                renewMaxCell(cells[j-1][i].getValue());
                emit scoreChanged(score);
                --j;
            }
        }
    }
    clearNullCellsRight();
    update();
}

void Board::keyPressEvent(QKeyEvent *event) {

    if(winFlag || loseFlag) {
        start();
    }
    else {
        if (!isStarted) {
                QFrame::keyPressEvent(event);
                return;
        }

        switch (event->key()) {
            case Qt::Key_Left:
                moveLeft();
                break;
            case Qt::Key_Right:
                moveRight();
                break;
            case Qt::Key_Up:
                moveUp();
                break;
            case Qt::Key_Down:
                moveDown();
                break;
            default:
                QFrame::keyPressEvent(event);
        }


            generateNewCellValue();

            if(maxCell == 2048) {
                winFlag = true;

            }

           if(!areZeroCells() && !areSameNeighbourCells()) {
                loseFlag = true;
            }
    }
}

void Board::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
    QPainter painter(this);
    QRect rect = contentsRect();


    if(winFlag) {
        painter.fillRect(rect, QBrush(WIN_BACKGROUND_COLOR));
        QFont font;
        font.setPixelSize(32);
        painter.setPen(WIN_FONT_COLOR);
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignCenter, "You win");
        return;
    }

    if(loseFlag) {
        painter.fillRect(rect, QBrush(LOSE_BACKGROUND_COLOR));
        QFont font;
        font.setPixelSize(32);
        painter.setPen(LOSE_FONT_COLOR);
        painter.setFont(font);
        painter.drawText(rect, Qt::AlignCenter, "You lose");
        return;
    }

    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            int x = i * DEFAULT_CELL_SIZE;
            int y = j * DEFAULT_CELL_SIZE;
            drawSquare(painter, x, y, cells[i][j]);
        }
    }
}

void Board::start()
{
    isStarted = true;
    score = 0;
    maxCell = 2;
    winFlag = false;
    loseFlag = false;
    emit scoreChanged(0);
    clearBoard();
    generateNewCellValue();
    update();
}

void Board::generateNewCellValue() {
    if(areZeroCells()) {
        int column = rand() % size;
        int row = rand() % size;
        if(cells[column][row].getValue() == 0) {
            if(rand()%8 != 0) {
                cells[column][row].setCell(2, 1);
            }
            else {
                cells[column][row].setCell(4, 2);
            }
        }
        else  generateNewCellValue();
    }
}

bool Board::areZeroCells() {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size; ++j) {
            if(cells[i][j].getValue() == 0) {
               return true;
            }
        }
    }
    return false;
}
bool Board::areSameNeighbourCells() {
    for(int i = 0; i < size; ++i) {
        for(int j = 0; j < size-1; ++j) {
            if(cells[i][j].getValue() == cells[i][j+1].getValue()) {
               return true;
            }
            if(cells[j][i].getValue() == cells[j+1][i].getValue()) {
               return true;
            }
        }
    }
    return false;
}

void Board::renewMaxCell(int v) {
    maxCell = v > maxCell ? v : maxCell;
    score += v;
}
