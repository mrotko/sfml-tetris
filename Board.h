#ifndef TETRIS_BOARD_H
#define TETRIS_BOARD_H

#include "Pieces.h"
#include <cstdlib>
#include <ctime>

#define BOARD_WIDTH 12
#define BOARD_HEIGHT 25

class Board {
    int **board;
    Pieces block, nextBlock;
    bool boardIsFull;
public:
    int **boardToDisplay;

    Board();
    void deleteLine(int y);
    int checkLines();
    void checkEnd();
    void move(int x, int y);
    bool moveIsPossible(int xNext, int yNext);
    void rotateBlock();
    void randBlock(int x, int y);
    void setBlock();
    void updateBoardToDisplay(bool updateBlock = true);
    Pieces & getNextBlock();
    bool getBoardIsFull();
};

#endif //TETRIS_BOARD_H
