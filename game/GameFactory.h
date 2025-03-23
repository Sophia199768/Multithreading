#pragma once
#include "Game.h"
#include "../board/Board.h"
#include "../player/Player.h"
#include "../health/HealthCalculator.h""

class GameFactory {
  GameFactory() {}
public:
  static std::shared_ptr<Game> createGame();
  static std::shared_ptr<Game> createGame(int boardSize, int amountOfShipTypes, int theBiggestDeskShip);
};

