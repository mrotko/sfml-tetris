#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "Board.h"
#include <string>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <ctime>
#include <iomanip>

#define LEVEL_SPEED 10

class Game {
    std::string name;
    Board board;
    int lines = 0, points = 0, level = 1;
    std::vector <std::vector <std::string>> hallOfFame;
public:
    bool gamePause;
    Game(std::string name = "");
    void newGame();
    void setName(std::string name);
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
    void saveHallOfFame();
    void updateHallOfFame();
    std::vector <std::vector <std::string>> getHallOfFame();
};

#endif //TETRIS_GAME_H

