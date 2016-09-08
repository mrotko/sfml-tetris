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
            }
        }
        io.window.clear();
        io.control();
        io.time = io.clock.getElapsedTime();
        if(io.time.asMilliseconds() > HOLD_TIME) {
            io.clock.restart();
            if(io.game->move(0, 1) == FALSE) {
                std::cout << "Koniec gry\n";
                //  wyswietlenie podsumowania, koniec gry
            }
        }
        io.drawBoard();
        io.window.display();
    }
}
