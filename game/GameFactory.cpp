#include "GameFactory.h"

boost::shared_ptr<Game> GameFactory::createGame(int boardSize, int amountOfShipTypes, int theBiggestDeskShip) {

  HealthCalculator::calculate(boardSize, amountOfShipTypes);
  auto firstPlayer = boost::shared_ptr<Player>(new Player(BoardFabric::boardCreate(boardSize, amountOfShipTypes, theBiggestDeskShip),
                            HealthCalculator::calculate(boardSize, amountOfShipTypes)));

  auto secondPlayer = boost::shared_ptr<Player> (new Player(BoardFabric::boardCreate(boardSize, amountOfShipTypes, theBiggestDeskShip),
                             HealthCalculator::calculate(boardSize, amountOfShipTypes)));

  srand(time(nullptr));
  bool firstPlayerStarts = rand() % 2 == 0;

  auto console = boost::shared_ptr<Console>(new Console(boardSize));

  auto playLogic = boost::shared_ptr<PlayLogic>(new PlayLogic(firstPlayerStarts, firstPlayer, secondPlayer));

  return boost::shared_ptr<Game>(new Game(console, playLogic));
}

boost::shared_ptr<Game> GameFactory::createGame() {
  return createGame(10, 2, 4);
}
