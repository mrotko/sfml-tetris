#include "IO.h"

IO::IO(Game &game) {
    window.create(sf::VideoMode(800, 600, 32), "Tetris");

    for(int i = 0; i < SHAPES; i++) {
        sf::Uint8 red, green, blue;
        red = (sf::Uint8) (rand() % 255);
        green = (sf::Uint8) (rand() % 255);
        blue = (sf::Uint8) (rand() % 255);

        rect[i].setFillColor(sf::Color(red, green, blue));
        rect[i].setSize(sf::Vector2f(SHAPE_SIZE, SHAPE_SIZE));
    }
    rect[0].setFillColor(sf::Color::Blue);
    rect[1].setFillColor(sf::Color::Cyan);
    this->game = &game;
    time = clock.restart();

}

void IO::drawBoard() {
    int marginLeft = 50, marginTop = 20;

    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = BLOCK_SIZE - 1; j < BOARD_HEIGHT; j++) {
            int value = game->getBoardValue(i, j);
            rect[value].setPosition(marginLeft + i * SHAPE_SIZE, marginTop + j * SHAPE_SIZE);
            window.draw(rect[value]);
        }
    }

    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            int value = game->getBoard().getNextBlock().getValue(i, j);
            rect[value].setPosition(marginLeft + BOARD_WIDTH * SHAPE_SIZE + i * SHAPE_SIZE,
                                    marginTop + BOARD_HEIGHT * SHAPE_SIZE / 2 + j * SHAPE_SIZE);
            window.draw(rect[value]);
        }
    }
}

