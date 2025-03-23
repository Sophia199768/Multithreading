#pragma once

#include "Board.h"
#include "../playLogic/FillingTheBoard.h"

class BoardFabric {
    BoardFabric() {}
public:
    static std::shared_ptr<Board> boardCreate(int boardSize, int amountOfShipTypes, int theBiggestDeskShip);
};
