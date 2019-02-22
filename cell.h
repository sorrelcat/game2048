#ifndef CELL_H
#define CELL_H

#include <QColor>
#include <QDebug>

class Cell
{
    static const QColor* colors;
    int value;
    int colorNumber;

public:
    Cell();
    Cell(int v, int cn);
    Cell(const Cell &c) {value = c.value; colorNumber = c.colorNumber;}
    void setCell(int, int);
    int getValue() {return value;}
    int getIntColor() {return colorNumber;}
    QColor getCellColor();

    void increment();
};

#endif // CELL_H
