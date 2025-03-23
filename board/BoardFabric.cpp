#include "BoardFabric.h"

std::shared_ptr<Board> BoardFabric::boardCreate(int boardSize, int amountOfShipTypes, int theBiggestDeskShip) {
    auto board = std::shared_ptr<Board>(new Board(boardSize));
    FillingTheBoard::fill(board, amountOfShipTypes, theBiggestDeskShip);
    return board;
}
