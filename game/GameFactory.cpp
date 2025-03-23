#include "GameFactory.h"

std::shared_ptr<Game> GameFactory::createGame(int boardSize, int amountOfShipTypes, int theBiggestDeskShip) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::bernoulli_distribution bool_dist(0.5);

    HealthCalculator::calculate(boardSize, amountOfShipTypes);
    auto firstPlayer = std::make_shared<Player>(
        BoardFabric::boardCreate(boardSize, amountOfShipTypes, theBiggestDeskShip),
        HealthCalculator::calculate(boardSize, amountOfShipTypes));

    auto secondPlayer = std::make_shared<Player>(
        BoardFabric::boardCreate(boardSize, amountOfShipTypes, theBiggestDeskShip),
        HealthCalculator::calculate(boardSize, amountOfShipTypes));

    bool firstPlayerStarts = bool_dist(gen);

    auto console = std::make_shared<Console>(boardSize);

    auto playLogic = std::make_shared<PlayLogic>(firstPlayerStarts, firstPlayer, secondPlayer);

    return std::make_shared<Game>(console, playLogic);
}

std::shared_ptr<Game> GameFactory::createGame() {
    return createGame(10, 2, 4);
}
