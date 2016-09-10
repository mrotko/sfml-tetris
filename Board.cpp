#include "Board.h"

Board::Board() {
    boardIsFull = false;
    board = new int *[BOARD_HEIGHT];
    boardToDisplay = new int *[BOARD_HEIGHT];

    for(int i = 0; i < BOARD_HEIGHT; ++i) {
        board[i] = new int[BOARD_WIDTH];
        boardToDisplay[i] = new int[BOARD_WIDTH];
        board[i][0] = board[i][BOARD_WIDTH - 1] = 1;
        for(int j = 1; j < BOARD_WIDTH - 1; ++j)
            board[i][j] = 0;
    }

    for(int i = 0; i < BOARD_WIDTH; ++i)
        board[BOARD_HEIGHT - 1][i] = 1;

    randBlock(BOARD_WIDTH / 2, 0);
    randBlock(BOARD_WIDTH / 2, 0);
    updateBoardToDisplay();
    srand(time(NULL));
}

void Board::deleteLine(int y) {

    for(int i = y; i >= BLOCK_SIZE; i--)
        for(int j = 0; j < BOARD_WIDTH; j++)
            board[i][j] = board[i - 1][j];
}

int Board::checkLines() {
    int combo = 0;

    for(int i = 0; i < BOARD_HEIGHT - 1; i++) {
        bool remove = true;
        for(int j = 0; j < BOARD_WIDTH; j++)
            if(board[i][j] == 0)
                remove = false;
        if(remove) {
            deleteLine(i);
            combo++;
        }
    }

    updateBoardToDisplay(false);
    return combo;
}

void Board::checkEnd() {
    for(int i = 1; i < BOARD_WIDTH - 1; i++)
        if(board[BLOCK_SIZE - 1][i]) {
            boardIsFull = true;
            break;
        }
}

void Board::move(int x, int y) {
    if(moveIsPossible(x, y)) {
        block.move(x, y);
        updateBoardToDisplay();
    }
}

bool Board::moveIsPossible(int xNext, int yNext) {
    int x = block.getX() + xNext;
    int y = block.getY() + yNext;

    int max_x = x + BLOCK_SIZE > BOARD_WIDTH ? BOARD_WIDTH : x + BLOCK_SIZE;
    int max_y = y + BLOCK_SIZE > BOARD_HEIGHT ? BOARD_HEIGHT : y + BLOCK_SIZE;

    for(int i = 0; y + i < max_y; i++)
        for(int j = 0; x + j < max_x; j++)
            if(board[y + i][x + j] && block.getValue(j, i))
                return false;
    return true;
}

void Board::rotateBlock() {
    Pieces b = block;
    block.rotate();
    if(!moveIsPossible(0, 0))
        block = b;
    updateBoardToDisplay();
}

void Board::setBlock() {
    int x = block.getX();
    int y = block.getY();

    int max_x = x + BLOCK_SIZE > BOARD_WIDTH ? BOARD_WIDTH : x + BLOCK_SIZE;
    int max_y = y + BLOCK_SIZE > BOARD_HEIGHT ? BOARD_HEIGHT : y + BLOCK_SIZE;

    for(int i = 0; i + y < max_y; i++)
        for(int j = 0; j + x < max_x; j++)
            if(board[y + i][x + j] == 0)
                board[y + i][x + j] = block.getValue(j, i);
}

void Board::randBlock(int x, int y) {
    block = nextBlock;
    nextBlock = Pieces();
    nextBlock.updateBlock(rand() % 7, rand() % 5, x - 3, y);
}

void Board::updateBoardToDisplay(bool updateBlock) {
    for(int i = 0; i < BOARD_HEIGHT; i++) {
        for(int j = 0; j < BOARD_WIDTH; j++) {
            boardToDisplay[i][j] = board[i][j];
        }
    }

    int x = block.getX();
    int y = block.getY();

    int max_x = x + BLOCK_SIZE > BOARD_WIDTH ? BOARD_WIDTH : x + BLOCK_SIZE;
    int max_y = y + BLOCK_SIZE > BOARD_HEIGHT ? BOARD_HEIGHT : y + BLOCK_SIZE;

    if(updateBlock) {
        for(int i = 0; i + y < max_y; i++)
            for(int j = 0; j + x < max_x; j++)
                if(boardToDisplay[y + i][x + j] == 0)
                    boardToDisplay[y + i][x + j] = block.getValue(j, i);
    }
}

Pieces & Board::getNextBlock() {
    return nextBlock;
}

bool Board::getBoardIsFull() {
    return boardIsFull;
}
