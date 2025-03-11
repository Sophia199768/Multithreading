#include "FillingTheBoard.h"
#include <cstdlib>
#include <ctime>

bool FillingTheBoard::canPlaceShip(int x, int y, const boost::shared_ptr<Ship>& ship, const boost::shared_ptr<Board>& board) {
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

bool FillingTheBoard::placeShip(const boost::shared_ptr<Ship>& ship, const boost::shared_ptr<Board>& board) {
    int x, y;
    int attempts = 0;
    int board_size = board->getBoardSizeWithoutBounds();
    const int maxAttempts = 1000;
    srand(time(nullptr));

    do {
        x = rand() % board_size + 1;
        y = rand() % board_size + 1;
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

void FillingTheBoard::fill(const boost::shared_ptr<Board>& board, int amountOfShipTypes, int amountOfBiggestDesk) {
    std::vector<boost::shared_ptr<Ship>> ships;
    for (int i = 0; i < amountOfShipTypes; ++i) {
        for (int j = 0; j < amountOfBiggestDesk; ++j) {
            ships.push_back(boost::shared_ptr<Ship>(new Ship(j + 1, rand() % 2 == 0)));
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
