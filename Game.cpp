#include "Game.h"

Game::Game(string name) {
    this->name = name;
    board = Board();
    board.drawBlock(BOARD_WIDTH / 2, 0);
    board.drawBlock(BOARD_WIDTH / 2, 0);
}

void Game::pause() {

}

void Game::resume() {

}

void Game::end() {
    cout << "Koniec gry. Przegrales!\n";
    show_result();
//    cout << "Czas gry: " << difftime(currentTime, startTime);

}

void Game::show_result() {
    cout << name << ": " << lines << endl;
}

bool Game::move(int x, int y) {
    if(board.moveIsPossible(x, y)) {
        board.move(x, y);
        board.updateDisplayBoard();
        return true;
    } else if(y == 1) {
        board.setBlock();
        lines += board.checkLines();

        if(board.checkEnd())
            return false;

        board.drawBlock(BOARD_WIDTH / 2, 0);
    }
    return true;
}

int Game::getBoardValue(int x, int y) {
    return board.boardToDisplay[y][x];
}

