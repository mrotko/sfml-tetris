#ifndef TETRIS_PIECES_H
#define TETRIS_PIECES_H

#include <vector>
using namespace std;

#define BLOCK_SIZE 5
class Pieces {
    int x, y;   //  left top corner
    int area[BLOCK_SIZE][BLOCK_SIZE];
    vector <vector <int>> listOfPieces;
public:
    Pieces();
    void rotate();
    void move(int changeX, int changeY);
    int getX();
    int getY();
    int getValue(int x, int y);
    void updateBlock(int type, int rotation, int posX, int posY);
};

#endif //TETRIS_PIECES_H
