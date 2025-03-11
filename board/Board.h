#pragma once
#include <vector>

class Board {
public:
    Board();
    explicit Board(int boardSize);

    void set(int x, int y, char val);
    void clear();

    std::vector<std::vector<char>>& getBoard();
    int getBoardSizeWithBounds() const;
    int getBoardSizeWithoutBounds() const;
private:
    static const int BOUNDS = 2;
    int boardSizeWithBounds = 0;
    std::vector<std::vector<char>> board;
};
