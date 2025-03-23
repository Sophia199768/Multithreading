#pragma once

#include "../board/Board.h"

class Player {
    std::shared_ptr<Board> board;
    int health;

public:
    Player(std::shared_ptr<Board> board, int health);

    void minusHealth();
    std::shared_ptr<Board> getBoard();
    int getHealth() const;
};

