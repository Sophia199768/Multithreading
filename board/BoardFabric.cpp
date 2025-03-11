#include "BoardFabric.h"

boost::shared_ptr<Board> BoardFabric::boardCreate(int boardSize, int amountOfShipTypes, int theBiggestDeskShip) {
    auto board = boost::shared_ptr<Board>(new Board(boardSize));
    FillingTheBoard::fill(board, amountOfShipTypes, theBiggestDeskShip);
    return board;
}
