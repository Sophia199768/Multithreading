#pragma once

#include "../board/Board.h"
#include <boost/shared_ptr.hpp>

class Player {
    boost::shared_ptr<Board> board;
    int health;

public:
    Player(boost::shared_ptr<Board> board, int health);

    void minusHealth();
    boost::shared_ptr<Board> getBoard();
    int getHealth() const;
};

