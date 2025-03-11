#pragma once

#include <boost/shared_ptr.hpp>
#include "Board.h"
#include "../playLogic/FillingTheBoard.h"

class BoardFabric {
    BoardFabric() {}
public:
    static boost::shared_ptr<Board> boardCreate(int boardSize, int amountOfShipTypes, int theBiggestDeskShip);
};
