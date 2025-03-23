#include "PlayLogic.h"


PlayLogic::PlayLogic(const bool counter, std::shared_ptr<Player> firstPlayer, std::shared_ptr<Player> secondPlayer)
        : counter(counter), firstPlayer(std::move(firstPlayer)), secondPlayer(std::move(secondPlayer)) {}

bool PlayLogic::endOfGame() const {
    return firstPlayer->getHealth() == 0 || secondPlayer->getHealth() == 0;
}

void PlayLogic::shot(const int x, const int y) {
    std::shared_ptr<Player> player = counter ? secondPlayer : firstPlayer;

    if (player->getBoard()->getBoard()[x][y] == '!') {
        player->getBoard()->getBoard()[x][y] = '#';
        player->minusHealth();
    } else if (player->getBoard()->getBoard()[x][y] == '#') {
        throw SeaBattleException("You have already shot there");
    } else {
        player->getBoard()->getBoard()[x][y] = '_';
        counter = !counter;
    }
}
