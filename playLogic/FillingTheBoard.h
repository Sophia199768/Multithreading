#pragma once
#include <random>
#include "../board/Board.h"
#include "../ship/Ship.h"

class FillingTheBoard {
    static bool canPlaceShip(int x, int y, const std::shared_ptr<Ship>& ship, const std::shared_ptr<Board>& board);
    static bool placeShip(const std::shared_ptr<Ship>& ship, const std::shared_ptr<Board>& board);
public:
    static void fill(const std::shared_ptr<Board>& board, int amountOfShipTypes, int amountOfBiggestDesk);
};
