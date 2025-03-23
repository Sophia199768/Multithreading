#include "Player.h"

Player::Player(std::shared_ptr<Board> board, const int health)
        : board(std::move(board)), health(health) {}

void Player::minusHealth() {
    if (health > 0) {
        health--;
    }
}

std::shared_ptr<Board> Player::getBoard() {
    return board;
}

int Player::getHealth() const {
    return health;
}
