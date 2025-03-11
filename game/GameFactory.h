#pragma once
#include <boost/shared_ptr.hpp>
#include "Game.h"
#include "../board/Board.h"
#include "../player/Player.h"
#include "../health/HealthCalculator.h""

class GameFactory {
  GameFactory() {}
public:
  static boost::shared_ptr<Game> createGame();
  static boost::shared_ptr<Game> createGame(int boardSize, int amountOfShipTypes, int theBiggestDeskShip);
};

