#include "cell.h"

static const QColor initColors[] = {
    QColor(255, 255, 255),
    QColor(255, 255, 204),
    QColor(255, 242, 204),
    QColor(255, 230, 204),
    QColor(255, 217, 204),
    QColor(255, 204, 204),
    QColor(255, 204, 217),
    QColor(255, 204, 230),
    QColor(255, 204, 242),
    QColor(242, 204, 255),
    QColor(230, 204, 255),
    QColor(217, 204, 255),
    QColor(204, 204, 255)

};

const QColor* Cell::colors = initColors;

Cell::Cell(int v, int cn) : value(v), colorNumber(cn)
{
}

Cell::Cell() : value(0), colorNumber(0)
{
}

void Cell::increment() {
    value *= 2;
    colorNumber++;
}

void Cell::setCell(int newValue, int newColorNumber) {
    value = newValue;
    colorNumber = newColorNumber;
}


QColor Cell::getCellColor() {
    return colors[colorNumber];
}
