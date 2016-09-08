#include "Game.h"

Game::Game(string name) {
    srand((unsigned int) time(NULL));
    this->name = name;
    board = Board();
    board.drawBlock(BOARD_WIDTH / 2, 0);
    board.drawBlock(BOARD_WIDTH / 2, 0);
}

void Game::start() {
    this->lines = 0;
    time(&startTime);
    clock_t time1 = 0, time2 = 0;

    while(true) {
        time(&currentTime);
        time1 = clock();
        while((time2 - time1) / CLOCKS_PER_SEC * 1000 < HOLD_TIME) {
            changePosition(getKey());
            time2 = clock();
        }
        if(board.moveIsPossible(0, 1) == FALSE) {
            board.setBlock();
            lines += board.checkLines();
            if(board.checkEnd()) {
                end();
                break;
            }
            board.drawBlock(BOARD_WIDTH / 2, 0);
        }
        time2 = clock();
        board.move(0, 1);
    }
}


void Game::end() {
    cout << "Koniec gry. Przegrales!\n";
    show_result();
    cout << "Czas gry: " << difftime(currentTime, startTime);

}

void Game::show_result() {
    cout << name << ": " << lines << endl;
}

int Game::getKey() {
    if(kbhit()) return getch();
    return 0;
}

void Game::changePosition(int key) {
    const int LEFT_ARROW = 75;
    const int RIGHT_ARROW = 77;
    const int UP_ARROW = 72;
    const int DOWN_ARROW = 80;

    if(key == LEFT_ARROW) board.move(-1, 0);
    if(key == RIGHT_ARROW) board.move(1, 0);
    if(key == DOWN_ARROW) {
        while(board.moveIsPossible(0, 1))
            board.move(0, 1);
    }
    if(key == UP_ARROW)
        board.rotateBlock();
}
