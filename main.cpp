#include "IO.h"
#include <iostream>

using namespace std;

int main() {
    Game game("michal");
    IO io(game);

    sf::Vector2i move;

    while(io.window.isOpen()) {
        sf::Event event;
        while(io.window.pollEvent(event)) {
            switch(event.type) {
                case sf::Event::Closed:
                    io.window.close();
                    break;
                case sf::Event::LostFocus:
                    game.pause();
                    break;
                case sf::Event::GainedFocus:
                    game.resume();
                    break;
                case sf::Event::KeyPressed:
                    move = io.controlInGame(event);
                    break;
            }
        }
        io.time = io.clock.getElapsedTime();

        if(!game.gamePause) {
            if(move.x != 0 || move.y != 0) {
                if(move.x == 2)
                    game.getBoard().rotateBlock();
                else if(move.x == 3) {
                    while(game.move(0, 1));
                    game.addPoints(0);
                } else
                    game.move(move.x, move.y);
                move = sf::Vector2i(0, 0);
            }

            if(io.time.asMilliseconds() > HOLD_TIME - (game.getLevel() * ACCELERATION)) {
                io.clock.restart();
                io.game->move(0, 1);
            }

            if(!game.getBoard().getBoardIsFull()) {
                io.window.clear(sf::Color(75, 75, 75));
                io.drawBoard();
                io.drawText();
            } else {
                game.end();
                io.drawEndGame();
            }
        } else {
            move = sf::Vector2i(0, 0);
            io.drawPause();
        }
        io.window.display();
    }
}
