#include <iostream>
#include <windows.h>
#include "IO.h"

using namespace std;

int main() {
    Game game("michal");
    IO io(game);

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
                    if(event.key.code == sf::Keyboard::Right)
                        game.move(1, 0);
                    else if(event.key.code == sf::Keyboard::Left)
                        game.move(-1, 0);
                    else if(event.key.code == sf::Keyboard::Up)
                        game.getBoard().rotateBlock();
                    else if(event.key.code == sf::Keyboard::Down)
                        game.move(0, 1);
                    else if(event.key.code == sf::Keyboard::P)
                        game.pause();
                    else if(event.key.code == sf::Keyboard::R)
                        game.resume();
                    break;
            }
        }

        io.time = io.clock.getElapsedTime();
        if(io.time.asMilliseconds() > HOLD_TIME) {
            io.clock.restart();
            if(io.game->move(0, 1) == FALSE) {
                std::cout << "Koniec gry\n";
                io.window.close();
                //  wyswietlenie podsumowania, koniec gry
            }
        }
        io.window.clear();
        io.drawBoard();
        io.window.display();
    }
}
