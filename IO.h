#ifndef TETRIS_IO_H
#define TETRIS_IO_H

#include <SFML/Graphics.hpp>
#include "Game.h"
#include <string>
#include <sstream>

#define SHAPES 9
#define SHAPE_SIZE 20
#define HOLD_TIME 500
#define ACCELERATION 20

class IO {
public:
    sf::RenderWindow window;
    sf::RectangleShape rect[SHAPES];
    sf::Clock clock;
    sf::Time time;
    sf::Texture tileTexture;
    sf::Text points, lines, level;
    sf::Font font;
    sf::Vector2f boardPosition, nextBlockPosition, textPosition;

    Game *game;
    IO(Game &game);
    void drawBoard();
    void drawText();
    void drawPause();
    void drawEndGame();
    sf::Vector2i controlInGame(sf::Event &event);
};

#endif //TETRIS_IO_H
