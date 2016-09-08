#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "Pieces.h"
#include <iostream>
#include <windows.h>

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 25

using namespace std;

class Board {
    int **board;
    Pieces block, nextBlock;
public:
    Board();
    void show();
    void deleteLine(int y);
    int checkLines();
    bool checkEnd();
    void move(int x, int y);
    bool moveIsPossible(int xNext, int yNext);
    void rotateBlock();
    void drawBlock(int x, int y);
    void setBlock();
};

#endif //TETRIS_BOARD_H
