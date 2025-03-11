#include "game/Game.h"
#include "game/GameFactory.h"

int main() {
    GameFactory::createGame()->start();
    return 0;
}
