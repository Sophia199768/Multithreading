#include "Board.h"

Board::Board() = default;

Board::Board(const int boardSize)
        : boardSizeWithBounds(boardSize + BOUNDS),
          board(boardSizeWithBounds, std::vector(boardSizeWithBounds, '.')) {}

void Board::set(const int x, const int y, const char val) {
    board[x][y] = val;
}

void Board::clear() {
    for (int i = 0; i < boardSizeWithBounds; i++) {
        for (int j = 0; j < boardSizeWithBounds; j++) {
            board[i][j] = '.';
        }
    }
}

std::vector<std::vector<char>>& Board::getBoard() {
    return board;
}

int Board::getBoardSizeWithBounds() const {
    return boardSizeWithBounds;
}

int Board::getBoardSizeWithoutBounds() const {
    return boardSizeWithBounds - BOUNDS;
}
