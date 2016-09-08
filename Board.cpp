#include "Board.h"

Board::Board() {
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

    drawBlock(BOARD_WIDTH / 2, 0);
    updateDisplayBoard();
}

/*
void Board::show() {
    char c;

    system("cls");
    for(int y = BLOCK_SIZE; y < BOARD_HEIGHT; ++y) {
        for(int x = 0; x < BOARD_WIDTH; ++x) {

            bool isBlock = TRUE;
            isBlock = isBlock && x >= block.getX();
            isBlock = isBlock && x < block.getX() + BLOCK_SIZE;
            isBlock = isBlock && y >= block.getY();
            isBlock = isBlock && y < block.getY() + BLOCK_SIZE;

            if(isBlock && block.getValue(x - block.getX(), y - block.getY()))
                c = '*';
            else if(board[y][x] == 1) c = '*';
            else c = ' ';
            cout << c;
        }
        cout << endl;
    }
    for(int y = 0; y < BLOCK_SIZE; y++) {
        for(int x = 0; x < BLOCK_SIZE; x++) {
            if(nextBlock.getValue(x, y)) cout << "*";
            else cout << " ";
        }
        cout << endl;
    }
}
*/

void Board::deleteLine(int y) {

    for(int i = y; i > BLOCK_SIZE; i--)
        for(int j = 0; j < BOARD_WIDTH; j++)
            board[i][j] = board[i - 1][j];
}

int Board::checkLines() {
    int combo = 0;

    for(int i = BOARD_HEIGHT - 2; i >= BLOCK_SIZE; i--) {
        bool remove = TRUE;
        for(int j = 0; j < BOARD_WIDTH; j++)
            if(board[i][j] == 0)
                remove = FALSE;
        if(remove) {
            deleteLine(i);
            combo++;
            i++;
        }
    }
    return combo;
}

bool Board::checkEnd() {
    for(int i = 1; i < BOARD_WIDTH - 1; i++)
        if(board[BLOCK_SIZE - 1][i])
            return true;
    return false;
}

void Board::move(int x, int y) {
    if(moveIsPossible(x, y)) {
        block.move(x, y);
//        show();
    }
}

bool Board::moveIsPossible(int xNext, int yNext) {
    int x = block.getX() + xNext;
    int y = block.getY() + yNext;

    for(int i = 0; i < BLOCK_SIZE && y + i < BOARD_HEIGHT; i++)
        for(int j = 0; j < BLOCK_SIZE && x + j < BOARD_WIDTH; j++)
            if(board[y + i][x + j] && block.getValue(j, i))
                return false;
    return true;
}

void Board::rotateBlock() {
    Pieces b = block;
    block.rotate();
    if(!moveIsPossible(0, 0))
        block = b;
//    else
//        show();
}

void Board::setBlock() {
    int x = block.getX();
    int y = block.getY();

    for(int i = 0; i < BLOCK_SIZE && i + y < BOARD_HEIGHT; i++)
        for(int j = 0; j < BLOCK_SIZE && j + x < BOARD_WIDTH; j++)
            if(board[y + i][x + j] == 0)
                board[y + i][x + j] = block.getValue(j, i);
}

void Board::setBlockToDisplay() {
    int x = block.getX();
    int y = block.getY();

    for(int i = 0; i < BLOCK_SIZE && i + y < BOARD_HEIGHT; i++)
        for(int j = 0; j < BLOCK_SIZE && j + x < BOARD_WIDTH; j++)
            if(boardToDisplay[y + i][x + j] == 0)
                boardToDisplay[y + i][x + j] = block.getValue(j, i);
}

void Board::drawBlock(int x, int y) {
    block = nextBlock;
    nextBlock = Pieces();
    nextBlock.updateBlock((rand() % 7), 0, x - 3, y);
}

int Board::value(int x, int y) {
    return board[y][x];
}

int Board::updateDisplayBoard() {
    for(int i = 0; i < BOARD_HEIGHT; i++) {
        for(int j = 0; j < BOARD_WIDTH; j++) {
            boardToDisplay[i][j] = board[i][j];
        }
    }

    setBlockToDisplay();
}

