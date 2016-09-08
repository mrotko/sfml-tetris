#ifndef TETRIS_GAME_H
#define TETRIS_GAME_H

#include "Board.h"
#include <string>
#include <windows.h>
#include <ctime>
#include <conio.h>
#include <cstdlib>

using namespace std;

class Game {
    string name;
    Board board;
    int lines;
    static const int HOLD_TIME = 500;
    time_t startTime, currentTime;
public:
    Game(string name);
    void start();
    void end();
    void show_result();
    int getKey();
    void changePosition(int key);
};

#endif //TETRIS_GAME_H

