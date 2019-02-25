#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <QColor>

const int DEFAULT_SIZE_IN_CELLS = 4;
const int MAX_SIZE_IN_CELLS = 10;
const int MIN_SIZE_IN_CELLS = 2;
const int DEFAULT_WINDOW_HEIGHT = 400;
const int DEFAULT_WINDOW_WIDTH = 400;
const int DEFAULT_CELL_SIZE = DEFAULT_WINDOW_WIDTH / DEFAULT_SIZE_IN_CELLS;
const int ADDITIONAL_SIZE = 80;
const int BORDER_SIZE = 22;
const int WIN_VALUE = 2048;
const QColor BASE_FONT_COLOR = QColor(100, 100, 100);
const QColor LOSE_BACKGROUND_COLOR = QColor(82, 82, 122);
const QColor LOSE_FONT_COLOR = QColor(240, 240, 245);
const QColor WIN_BACKGROUND_COLOR = QColor(255, 255, 204);
const QColor WIN_FONT_COLOR = QColor(255, 255, 102);



#endif // CONSTANTS_H
