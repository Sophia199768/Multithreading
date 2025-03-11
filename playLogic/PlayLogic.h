#pragma once

#include "../player/Player.h"

class PlayLogic {

public:
    explicit PlayLogic(bool counter, boost::shared_ptr<Player> firstPlayer, boost::shared_ptr<Player> secondPlayer);
    bool endOfGame() const;
    void shot(int x, int y);
    bool isCounter() const { return counter; }
    boost::shared_ptr<Player> getFirstPlayer() { return firstPlayer; }
    boost::shared_ptr<Player> getSecondPlayer() { return secondPlayer; }

private:
    bool counter;
    boost::shared_ptr<Player> firstPlayer;
    boost::shared_ptr<Player> secondPlayer;
};

class SeaBattleException : public std::runtime_error {
public:
    explicit SeaBattleException(const std::string &message)
            : std::runtime_error(message) {}
};
