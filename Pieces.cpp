#include <iostream>
#include "Pieces.h"

Pieces::Pieces() {
    listOfPieces.push_back({2, 7, 12, 17});
    listOfPieces.push_back({6, 7, 8, 12});
    listOfPieces.push_back({6, 7, 11, 12});
    listOfPieces.push_back({6, 11, 16, 17});
    listOfPieces.push_back({7, 12, 16, 17});
    listOfPieces.push_back({7, 8, 11, 12});
    listOfPieces.push_back({6, 7, 12, 13});
}

void Pieces::rotate() {
    int n = BLOCK_SIZE;
    int array[BLOCK_SIZE][BLOCK_SIZE];
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            array[i][j] = this->area[n - j - 1][i];

    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            area[i][j] = array[i][j];
}

void Pieces::move(int changeX, int changeY) {
    this->lastX = this->x;
    this->lastY = this->y;
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
    int i = 0, j = 0, k = 0;
    int value = type + 2;
    this->x = posX;
    this->y = posY;
    while(i < BLOCK_SIZE) {
        if(listOfPieces[type][k] == BLOCK_SIZE * i + j) {
            this->area[i][j] = value;
            k++;
        } else this->area[i][j] = 0;

        j++;
        if(j % BLOCK_SIZE == 0) {
            i++;
            j = 0;
        }
    }

    for(i = 0; i < rotation; i++)
        rotate();
}

