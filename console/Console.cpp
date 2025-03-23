#include "Console.h"

Console::Console(int boardSize) : boardSize(boardSize) {}

std::vector<int> Console::cell() const {
    int firstCoordinate = 1;
    int x, y;
    std::cout << "Write x, y: " << std::endl;
    std::cin >> x >> y;

    if ((x > boardSize || y > boardSize) || (x < firstCoordinate || y < firstCoordinate)) {
        throw SeaBattleException("You can choose only from 1 to 10");
    }
    return {x, y};
}

void Console::writeMessage(const char* message) {
    std::cout << message << std::endl;
}

void Console::write(const std::shared_ptr<PlayLogic>& playLogic) const {
    std::shared_ptr<Player> firstPlayer;
    std::shared_ptr<Player> secondPlayer;

    if (playLogic->isCounter()) {
        firstPlayer = playLogic->getFirstPlayer();
        secondPlayer = playLogic->getSecondPlayer();
    } else {
        secondPlayer = playLogic->getFirstPlayer();
        firstPlayer = playLogic->getSecondPlayer();
    }

    std::cout << "Your desk" << std::endl;
    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            char cell = firstPlayer->getBoard()->getBoard()[i][j];
            std::cout << (cell == '|' ? '.' : cell);
        }
        std::cout << std::endl;
    }

    std::cout << "Your partner desk" << std::endl;
    for (int i = 1; i <= boardSize; i++) {
        for (int j = 1; j <= boardSize; j++) {
            char cell = secondPlayer->getBoard()->getBoard()[i][j];
            std::cout << ((cell == '!' || cell == '|') ? '.' : cell);
        }
        std::cout << std::endl;
    }
}
