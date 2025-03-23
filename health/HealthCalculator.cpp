#include "HealthCalculator.h"

int HealthCalculator::calculate(int amountOfShipTypes, int theBiggestDeskShip) {
    int health = 0;
    for (int i = 1; i <= amountOfShipTypes; i++) {
        for (int j = i; j <= theBiggestDeskShip; j++) {
            health += i;
        }
    }
    return health;
}