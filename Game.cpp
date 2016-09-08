#include "Game.h"

Game::Game(string name) {
    this->name = name;
    board = Board();
    board.randBlock(BOARD_WIDTH / 2, 0);
    board.randBlock(BOARD_WIDTH / 2, 0);
}

void Game::pause() {

}

void Game::resume() {

}

void Game::end() {

}

bool Game::move(int x, int y) {
    if(board.moveIsPossible(x, y)) {
        board.move(x, y);
        return true;
    } else if(y == 1) {
        board.setBlock();
        lines += board.checkLines();

        if(board.checkEnd())
            return false;

        board.randBlock(BOARD_WIDTH / 2, 0);
    }
    return true;
}

Board &Game::getBoard() {
    return board;
}



