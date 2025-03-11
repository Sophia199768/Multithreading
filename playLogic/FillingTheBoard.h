#pragma once
#include "../board/Board.h"
#include "../ship/Ship.h"
#include <boost/shared_ptr.hpp>

class FillingTheBoard {
    static bool canPlaceShip(int x, int y, const boost::shared_ptr<Ship>& ship, const boost::shared_ptr<Board>& board);
    static bool placeShip(const boost::shared_ptr<Ship>& ship, const boost::shared_ptr<Board>& board);
public:
    static void fill(const boost::shared_ptr<Board>& board, int amountOfShipTypes, int amountOfBiggestDesk);
};
