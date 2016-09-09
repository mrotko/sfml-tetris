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

void IO::drawPause() {
    sf::Text pause("PAUSE", font, 50);
    pause.setOutlineThickness(4);
    sf::Vector2f position(window.getSize().x / 6, window.getSize().y / 4);
    pause.setPosition(position);
    window.draw(pause);
}

void IO::drawEndGame() {
    sf::Vector2f position(window.getSize().x / 10, window.getSize().y / 20);
    std::ostringstream ss;

    ss << "Points " << game->getPoints() << std::endl
       << "Level  " << game->getLevel() << std::endl
       << "Lines  " << game->getLines();

    sf::Text summary(ss.str(), font, 15);
    summary.setPosition(position);
    summary.setOutlineThickness(2);
    window.draw(summary);

    sf::Text endGame("GAME IS OVER!", font, 30);
    endGame.setOutlineThickness(3);
    position = sf::Vector2f(window.getSize().x / 10, window.getSize().y / 4);
    endGame.setPosition(position);
    window.draw(endGame);

    position.y += 40;
    sf::Text record("", font, 12);
    record.setOutlineThickness(2);
    record.setPosition(position);

    ss.str("");
    std::left(ss);

    for(int i = 0; i < game->getHallOfFame().size(); i++) {

        ss << std::setw(2) << i + 1 << " "
           << std::setw(15) << game->getHallOfFame()[i][0].substr(0, 10) << " "
           << std::setw(10) << game->getHallOfFame()[i][1].substr(0, 10) << " "
           << game->getHallOfFame()[i][2];

        record.setString(ss.str());
        window.draw(record);

        ss.str("");
        position.y += 20;
        record.setPosition(position);
    }
}

sf::Vector2i IO::controlInGame(sf::Event &event) {
    if(event.key.code == sf::Keyboard::Right)
        return sf::Vector2i(1, 0);
    else if(event.key.code == sf::Keyboard::Left)
        return sf::Vector2i(-1, 0);
    else if(event.key.code == sf::Keyboard::Up)
        return sf::Vector2i(2, 0);
    else if(event.key.code == sf::Keyboard::Down)
        return sf::Vector2i(0, 1);
    else if(event.key.code == sf::Keyboard::Space) {
        return sf::Vector2i(3, 0);
    } else if(event.key.code == sf::Keyboard::P) {
        if(game->gamePause)
            game->resume();
        else
            game->pause();
        return sf::Vector2i(0, 0);
    } else return sf::Vector2i(0, 0);
}
