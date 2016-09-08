#include "IO.h"

IO::IO(Game &game) {
    window.create(sf::VideoMode(800, 600, 32), "Tetris");

    std::default_random_engine generator;
    std::uniform_int_distribution <int> distribution(0, 255);

    for(int i = 0; i < SHAPES; i++) {
        sf::Uint8 red, green, blue;
        red = (sf::Uint8) distribution(generator);
        green = (sf::Uint8) distribution(generator);
        blue = (sf::Uint8) distribution(generator);

        rect[i].setFillColor(sf::Color(red, green, blue));
        rect[i].setSize(sf::Vector2f(SHAPE_SIZE, SHAPE_SIZE));
    }
    this->game = &game;
    time = clock.restart();
}

void IO::control() {
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        game->move(1, 0);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        game->move(-1, 0);
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//        game.move();
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
//        game.move();
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//        game.rotate().
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)) {
//        game.pause();
    } else if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
//        game.resume();
    }

    //  ustawienie, przyspieszenie, obrot
}

void IO::drawBoard() {
    for(int i = 0; i < BOARD_WIDTH; i++) {
        for(int j = BLOCK_SIZE; j < BOARD_HEIGHT; j++) {
            int value = game->getBoardValue(i, j);
            rect[value].setPosition(50 + i * SHAPE_SIZE, 20 + j * SHAPE_SIZE);
            window.draw(rect[value]);
        }
    }
}

