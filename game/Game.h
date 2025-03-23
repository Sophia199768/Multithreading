#pragma once
#include "../board/BoardFabric.h"
#include "../console/Console.h"
#include "../playLogic/PlayLogic.h"

class Game {
public:
    Game(std::shared_ptr<Console> console, std::shared_ptr<PlayLogic> playLogic);

    int start() const;

    std::shared_ptr<Console> getConsole() { return console; }
    std::shared_ptr<PlayLogic> getPlayLogic() { return playLogic; }

private:
    std::shared_ptr<Console> console;
    std::shared_ptr<PlayLogic> playLogic;
};
