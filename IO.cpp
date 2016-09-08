#include "IO.h"

IO::IO(Game &game) {
    unsigned videoHeight = SHAPE_SIZE*(BOARD_HEIGHT-BLOCK_SIZE);
    unsigned videoWidth = SHAPE_SIZE * BOARD_WIDTH + BLOCK_SIZE*SHAPE_SIZE;
    window.create(sf::VideoMode(videoWidth, videoHeight, 32), "Tetris");

    tileTexture.loadFromFile("tiles.png");

    for(int i = 0; i < SHAPES; i++) {
        rect[i].setSize(sf::Vector2f(SHAPE_SIZE, SHAPE_SIZE));
        rect[i].setTexture(&tileTexture);
        rect[i].setTextureRect(sf::IntRect(SHAPE_SIZE * i, 0, SHAPE_SIZE, SHAPE_SIZE));
    }
    this->game = &game;
    time = clock.restart();

}

void IO::drawBoard() {
    int marginLeft = -SHAPE_SIZE, marginTop = -SHAPE_SIZE * BLOCK_SIZE + SHAPE_SIZE;

    for(int i = 1; i < BOARD_WIDTH - 1; i++) {
        for(int j = BLOCK_SIZE - 1; j < BOARD_HEIGHT - 1; j++) {
            int value = game->getBoard().boardToDisplay[j][i];
            rect[value].setPosition(marginLeft + i * SHAPE_SIZE, marginTop + j * SHAPE_SIZE);
            window.draw(rect[value]);
        }
    }

    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            int value = game->getBoard().getNextBlock().getValue(i, j);
            rect[value].setPosition(marginLeft + BOARD_WIDTH * SHAPE_SIZE + i * SHAPE_SIZE, j * SHAPE_SIZE);
            window.draw(rect[value]);
        }
    }
}