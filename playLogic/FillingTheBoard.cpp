#include "FillingTheBoard.h"


bool FillingTheBoard::canPlaceShip(int x, int y, const std::shared_ptr<Ship>& ship, const std::shared_ptr<Board>& board) {
    if (ship->isHorizontal()) {
        if (y + ship->getSize() > board->getBoardSizeWithoutBounds()) {
            return false;
        }
        for (int i = 0; i < ship->getSize(); i++) {
            if (board->getBoard()[x][y + i] != '.') {
                return false;
            }
        }
    } else {
        if (x + ship->getSize() > board->getBoardSizeWithoutBounds()) {
            return false;
        }
        for (int i = 0; i < ship->getSize(); i++) {
            if (board->getBoard()[x + i][y] != '.') {
                return false;
            }
        }
    }
    return true;
}

bool FillingTheBoard::placeShip(const std::shared_ptr<Ship>& ship, const std::shared_ptr<Board>& board) {
    std::random_device rd;
    std::mt19937 gen(rd());

    int x, y;
    int attempts = 0;
    int board_size = board->getBoardSizeWithoutBounds();
    const int maxAttempts = 1000;

    std::uniform_int_distribution dist(1, board_size - 1);

    do {
        x = dist(gen);
        y = dist(gen);
        attempts++;
        if (attempts > maxAttempts) {
            return false;
        }
    } while (!canPlaceShip(x, y, ship, board));

    if (ship->isHorizontal()) {
        for (int i = 0; i < ship->getSize(); i++) {
            board->set(x, y + i, '!');
        }
        for (int i = 0; i <= ship->getSize(); i++) {
            board->set(x - 1, y + i - 1, '|');
            board->set(x + 1, y + i - 1, '|');
        }
        board->set(x, y + ship->getSize(), '|');
        board->set(x, y - 1, '|');
    } else {
        for (int i = 0; i < ship->getSize(); i++) {
            board->set(x + i, y, '!');
        }
        for (int i = 0; i <= ship->getSize() + 1; i++) {
            board->set(x + i - 1, y - 1, '|');
            board->set(x + i - 1, y + 1, '|');
        }
        board->set(x + ship->getSize(), y, '|');
        board->set(x - 1, y, '|');
    }

    return true;
}

void FillingTheBoard::fill(const std::shared_ptr<Board>& board, int amountOfShipTypes, int amountOfBiggestDesk) {
    std::vector<std::shared_ptr<Ship>> ships;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution bool_dist(0.5);
    for (int i = 0; i < amountOfShipTypes; ++i) {
        for (int j = 0; j < amountOfBiggestDesk; ++j) {
            ships.push_back(std::make_shared<Ship>(j + 1, bool_dist(gen)));
        }
    }

    bool allShipsPlaced;
    do {
        board->clear();
        allShipsPlaced = true;

        for (const auto& ship : ships) {
            if (!placeShip(ship, board)) {
                allShipsPlaced = false;
                break;
            }
        }
    } while (!allShipsPlaced);
}
