#include "Game.h"

Game::Game(std::shared_ptr<Console> console, std::shared_ptr<PlayLogic> playLogic)
: console(std::move(console)), playLogic(std::move(playLogic)) {}

int Game::start() const {
    while (!playLogic->endOfGame()) {
        try {
            console->write(playLogic);
            auto turn = console->cell();
            playLogic->shot(turn[0], turn[1]);
        } catch (const SeaBattleException& e) {
            console->writeMessage(e.what());
        }
    }

    if (playLogic->getFirstPlayer()->getHealth() == 0) {
        console->writeMessage("First player wins!");
    } else {
        console->writeMessage("Second player wins!");
    }

    return 0;
}
