#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QLCDNumber>
#include "board.h"

class QPushButton;

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow();

private:
    MainWindow *ui;
    Board *board;
    QPushButton *startButton;
    QPushButton *pauseButton;
    QLCDNumber *scoreLcd;
    QLabel *winLoseLabel;

};

#endif // MAINWINDOW_H
