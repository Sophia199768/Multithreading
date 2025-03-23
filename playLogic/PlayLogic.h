#pragma once

#include "../player/Player.h"

class PlayLogic {

public:
    explicit PlayLogic(bool counter, std::shared_ptr<Player> firstPlayer, std::shared_ptr<Player> secondPlayer);
    bool endOfGame() const;
    void shot(int x, int y);
    bool isCounter() const { return counter; }
    std::shared_ptr<Player> getFirstPlayer() { return firstPlayer; }
    std::shared_ptr<Player> getSecondPlayer() { return secondPlayer; }

private:
    bool counter;
    std::shared_ptr<Player> firstPlayer;
    std::shared_ptr<Player> secondPlayer;
};

class SeaBattleException : public std::runtime_error {
public:
    explicit SeaBattleException(const char* message)
            : std::runtime_error(message) {}

};
