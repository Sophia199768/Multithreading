#pragma once
#include "../board/BoardFabric.h"
#include "../console/Console.h"
#include "../playLogic/PlayLogic.h"

class Game {
public:
    Game(boost::shared_ptr<Console> console, boost::shared_ptr<PlayLogic> playLogic);

    void start() const;

private:
    boost::shared_ptr<Console> console;
    boost::shared_ptr<PlayLogic> playLogic;
};
