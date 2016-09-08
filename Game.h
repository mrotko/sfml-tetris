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
    bool move(int x, int y);
    void rotate();
    int getBoardValue(int x, int y);
    Board &getBoard();

};

#endif //TETRIS_GAME_H

