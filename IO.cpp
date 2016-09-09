#include "IO.h"

IO::IO(Game &game) {
    unsigned videoHeight = SHAPE_SIZE * (BOARD_HEIGHT - BLOCK_SIZE);
    unsigned videoWidth = SHAPE_SIZE * BOARD_WIDTH + BLOCK_SIZE * SHAPE_SIZE;

    window.create(sf::VideoMode(videoWidth, videoHeight), "Tetris");

    tileTexture.loadFromFile("tiles.png");
    font.loadFromFile("consola.ttf");

    for(int i = 0; i < SHAPES; i++) {
        rect[i].setSize(sf::Vector2f(SHAPE_SIZE, SHAPE_SIZE));
        rect[i].setTexture(&tileTexture);
        rect[i].setTextureRect(sf::IntRect(SHAPE_SIZE * i, 0, SHAPE_SIZE, SHAPE_SIZE));
    }

    this->game = &game;
    time = clock.restart();

    boardPosition.x = -SHAPE_SIZE;
    boardPosition.y = -SHAPE_SIZE * BLOCK_SIZE + SHAPE_SIZE;
    nextBlockPosition.x = boardPosition.x + BOARD_WIDTH * SHAPE_SIZE;
    nextBlockPosition.y = 0;
    textPosition.x = BOARD_WIDTH * SHAPE_SIZE - SHAPE_SIZE;
    textPosition.y = BOARD_HEIGHT * SHAPE_SIZE / 4;

    sf::Text tmp("", font, 20);

    points = lines = level = tmp;

    points.setPosition(textPosition);
    lines.setPosition(textPosition.x, textPosition.y + 70);
    level.setPosition(textPosition.x, textPosition.y + 140);

}

void IO::drawBoard() {
    for(int i = 1; i < BOARD_WIDTH - 1; i++) {
        for(int j = BLOCK_SIZE - 1; j < BOARD_HEIGHT - 1; j++) {
            int value = game->getBoard().boardToDisplay[j][i];
            rect[value].setPosition(boardPosition.x + i * SHAPE_SIZE, boardPosition.y + j * SHAPE_SIZE);
            window.draw(rect[value]);
        }
    }

    for(int i = 0; i < BLOCK_SIZE; i++) {
        for(int j = 0; j < BLOCK_SIZE; j++) {
            int value = game->getBoard().getNextBlock().getValue(i, j);
            rect[value].setPosition(nextBlockPosition.x + i * SHAPE_SIZE, j * SHAPE_SIZE);
            window.draw(rect[value]);
        }
    }
}

void IO::drawText() {
    std::ostringstream ss;
    ss << game->getPoints();
    points.setString("Points\n" + ss.str());
    ss.str("");
    ss << game->getLevel();
    level.setString("Level\n" + ss.str());
    ss.str("");
    ss << game->getLines();
    lines.setString("Lines\n" + ss.str());

    window.draw(points);
    window.draw(level);
    window.draw(lines);
}
