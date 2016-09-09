#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "Board.h"
#include <string>
#include <fstream>

#define LEVEL_SPEED 10

class Game {
    std::string name;
    Board board;
    int lines = 0, points = 0, level = 1;
    std::vector <std::string> hallOfFame;
public:
    bool gamePause;
    Game(std::string name);
    void pause();
    void resume();
    void end();
    bool move(int x, int y);
    Board &getBoard();
    int getLines();
    int getPoints();
    int getLevel();
    void addPoints(int lines);
    void loadHallOfFame();
    void updateHallOfFame();
    std::vector <std::string> getHallOfFame();
};

#endif //TETRIS_GAME_H

