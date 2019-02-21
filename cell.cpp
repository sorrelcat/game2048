#include "cell.h"

static const Qt::GlobalColor initColors[] = {
    Qt::GlobalColor::white,
    Qt::GlobalColor::lightGray,
    Qt::GlobalColor::yellow,
    Qt::GlobalColor::darkYellow,
    Qt::GlobalColor::magenta,
    Qt::GlobalColor::red,
    Qt::GlobalColor::darkMagenta,
    Qt::GlobalColor::green,
    Qt::GlobalColor::darkGreen,
    Qt::GlobalColor::cyan,
    Qt::GlobalColor::darkCyan,
    Qt::GlobalColor::blue,
    Qt::GlobalColor::darkBlue

};

const Qt::GlobalColor* Cell::colors = initColors;

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


Qt::GlobalColor Cell::getCellColor() {
    return colors[colorNumber];
}
