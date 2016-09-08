#ifndef TETRIS_IO_H
#define TETRIS_IO_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <random>

#define SHAPES 9
#define SHAPE_SIZE 20
#define HOLD_TIME 500

class IO {
public:
    sf::RenderWindow window;
    sf::RectangleShape rect[SHAPES];
    sf::Clock clock;
    sf::Time time;

    Game *game;
    IO(Game &game);
    void control();
    void drawBoard();
};

#endif //TETRIS_IO_H
