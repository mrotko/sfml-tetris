#include "Game.h"

Game::Game(std::string name) {
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
        int lines = board.checkLines();
        this->lines += lines;
        addPoints(lines);

        if(lines > 0) {
            if(this->lines >= (level * LEVEL_SPEED))
                level++;
        }

        if(board.checkEnd()) {
            //  cos gdy koniec gry;
        }
        board.randBlock(BOARD_WIDTH / 2, 0);
        return false;
    }
    return true;
}

Board &Game::getBoard() {
    return board;
}

int Game::getLines() {
    return lines;
}

int Game::getPoints() {
    return points;
}

int Game::getLevel() {
    return level;
}

void Game::addPoints(int lines) {
    switch(lines) {
        case 1:
            points += 100 * level;
            break;
        case 2:
            points += 300 * level;
            break;
        case 3:
            points += 500 * level;
            break;
        case 4:
            points += 800 * level;
            break;
        default:
            break;
    }

    points += 4;

    /*
        single 100 * level
        double 300 * level
        triple 500 * level
        tetris 800 * level
        soft drop 1 per cell
        hard drop 2 per cell
    */
}


