#include "Game.h"
#include <iostream>

Game::Game(std::string name) {
    this->name = name;
    gamePause = false;
    board = Board();
    board.randBlock(BOARD_WIDTH / 2, 0);
    board.randBlock(BOARD_WIDTH / 2, 0);
    hallOfFame.clear();
    loadHallOfFame();
}

void Game::pause() {
    gamePause = true;
}

void Game::resume() {
    gamePause = false;
}

void Game::end() {
    updateHallOfFame();
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

        board.checkEnd();

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

void Game::loadHallOfFame() {
    std::fstream load("hallOfFame.txt", std::ios::in);
    if(load.good()) {
        std::string name, points, line;
        while(!load.eof()) {
            std::getline(load, line);
            name = line.substr(0, line.find(' '));
            points = line.substr(line.find(' ') + 1);
            if(name != "" && points != "") {
                hallOfFame.push_back(name);
                hallOfFame.push_back(points);
            }
        }
    } else {
        load.open("hallOfFame.txt", std::ios::out);
    }
    load.close();
}

void Game::updateHallOfFame() {
    std::fstream save("hallOfFame.txt", std::ios::out | std::ios::trunc);
    if(save.good()) {
        for(int i = 0; i < hallOfFame.size(); i += 2) {
            save << hallOfFame.at(i) + " " + hallOfFame.at(i + 1) + "\n";
        }
    }
    save.close();
}

std::vector <std::string> Game::getHallOfFame() {
    return std::vector <std::string>();
}


