#include "IO.h"

int main() {
    Game game;
    IO io(game);
    bool isNick = false;
    std::string name = "";
    sf::Vector2i move;
    sf::Text text("nick: ", io.font, 30);

    io.window.setFramerateLimit(60);

    while(io.window.isOpen()) {
        io.window.clear(sf::Color(75, 75, 75));
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
                    if(!game.getBoard().getBoardIsFull())
                        game.resume();
                    break;
                case sf::Event::KeyPressed:
                    move = io.controlInGame(event);
                    break;
                case sf::Event::TextEntered:
                    if(isNick) break;
                    if(event.key.code == 13) {
                        if(name != "") {
                            game.setName(name);
                            isNick = true;
                        }
                        break;
                    }
                    if(event.text.unicode == 32) break;
                    if(event.text.unicode == 8)
                        name = name.substr(0, name.length() - 1);
                    else
                        name += (char) event.text.unicode;
                    break;
                default:
                    break;
            }
        }

        if(!isNick) {
            text.setString("nick: " + name);
            io.window.draw(text);
            io.window.display();
            continue;
        }

        io.time = io.clock.getElapsedTime();

        io.drawBoard();
        io.drawText();

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

            if(game.getBoard().getBoardIsFull()) {
                game.end();
                game.pause();
            }
        } else {
            move = sf::Vector2i(0, 0);
            if(game.getBoard().getBoardIsFull()) {
                io.drawEndGame();
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
                    game.newGame();
                }
            } else
                io.drawPause();
        }
        io.window.display();
    }
}
