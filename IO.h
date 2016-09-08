#ifndef TETRIS_IO_H
#define TETRIS_IO_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <ctime>
#include <cstdlib>
#include <string>

#define SHAPES 9
#define SHAPE_SIZE 20
#define HOLD_TIME 500

class IO {
public:
    sf::RenderWindow window;
    sf::RectangleShape rect[SHAPES];
    sf::Clock clock;
    sf::Time time;
    sf::Texture tileTexture;

    Game *game;
    IO(Game &game);
    void drawBoard();
};

#endif //TETRIS_IO_H
