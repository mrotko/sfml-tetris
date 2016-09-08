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
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = 0; j < BOARD_HEIGHT; j++) {
            int getValue = game->getBoardValue(i, j);
            rect[getValue].setPosition(50 + i * SHAPE_SIZE, 20 + j * SHAPE_SIZE);
            window.draw(rect[getValue]);
        }
    }
}

