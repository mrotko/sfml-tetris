#include "Pieces.h"

Pieces::Pieces() {
    listOfPieces.push_back({2, 7, 12, 17});
    listOfPieces.push_back({11, 12, 13, 17});
    listOfPieces.push_back({6, 7, 11, 12});
    listOfPieces.push_back({7, 12, 17, 18});
    listOfPieces.push_back({7, 12, 16, 17});
    listOfPieces.push_back({7, 8, 11, 12});
    listOfPieces.push_back({6, 7, 12, 13});
}

void Pieces::rotate() {
    const int n = BLOCK_SIZE;
    int array[n][n];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            array[i][j] = this->area[n - j - 1][i];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            area[i][j] = array[i][j];
}

void Pieces::move(int changeX, int changeY) {
    this->x += changeX;
    this->y += changeY;
}

int Pieces::getX() {
    return this->x;
}

int Pieces::getY() {
    return this->y;
}

int Pieces::getValue(int x, int y) {
    return area[y][x];
}

void Pieces::updateBlock(int type, int rotation, int posX, int posY) {
    int value = type + 2;
    this->x = posX;
    this->y = posY;
    vector <int> shape = listOfPieces[type];

    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            area[i][j] = 0;
        }
    }

    for(int i = 0; i < shape.size(); i++) {
        int x = shape[i] % BLOCK_SIZE;
        int y = shape[i] / BLOCK_SIZE;
        area[y][x] = value;
    }

    for(int i = 0; i < rotation; i++)
        rotate();
}

