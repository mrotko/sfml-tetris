#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "Board.h"
#include <string>

using namespace std;

class Game {
    string name;
    Board board;
    int lines;
public:
    Game(string name);
    void pause();
    void resume();
    void end();
    void show_result();
    bool move(int x, int y);
    int getBoardValue(int x, int y);
};

#endif //TETRIS_GAME_H

