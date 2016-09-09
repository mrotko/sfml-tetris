#include "Game.h"
#include <iostream>

Game::Game(std::string name) {
    this->name = name;
    newGame();
}

void Game::newGame() {
    gamePause = false;
    lines = 0; points = 0; level = 1;
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
    saveHallOfFame();
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
        std::string name = "", points = "", date = "", line = "";
        while(!load.eof()) {
            std::getline(load, line);
            name = line.substr(0, line.find(' '));
            points = line.substr(line.find(' ') + 1, line.rfind(' ') - line.find(' ') - 1);
            date = line.substr(line.rfind(' ') + 1);
            if(name != "" && points != "" && date != "") {
                hallOfFame.push_back({name, points, date});
            }
        }
    } else {
        load.open("hallOfFame.txt", std::ios::out);
    }
    load.close();
}

void Game::saveHallOfFame() {
    std::fstream save("hallOfFame.txt", std::ios::out | std::ios::trunc);
    std::ostringstream ss;
    if(save.good()) {
        for(int i = 0; i < hallOfFame.size(); i++) {
            ss << hallOfFame[i][1];
            save << hallOfFame[i][0] + " " + ss.str() + " " + hallOfFame[i][2] + "\n";
            ss.str("");
        }
    }
    save.close();
}

void Game::updateHallOfFame() {
    std::vector <std::string> tmp;
    std::ostringstream ss;

    ss << points;
    tmp.push_back(name);
    tmp.push_back(ss.str());
    ss.str(" ");

    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);

    ss << std::put_time(&tm, "%d-%m-%Y");
    tmp.push_back(ss.str());

    hallOfFame.push_back(tmp);

    int i = hallOfFame.size() - 1;
    while(i > 0) {
        if(atoi(hallOfFame[i][1].c_str()) > atoi(hallOfFame[i - 1][1].c_str())) {
            tmp = hallOfFame[i - 1];
            hallOfFame[i - 1] = hallOfFame[i];
            hallOfFame[i] = tmp;
            i--;
        } else {
            break;
        }
    }
    while(hallOfFame.size() > 10)
        hallOfFame.pop_back();
}

std::vector <std::vector <std::string>> Game::getHallOfFame() {
    return hallOfFame;
}


