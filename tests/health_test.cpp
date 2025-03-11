#include <gtest/gtest.h>
#include "../health/HealthCalculator.h"

TEST(HealthCalculatorTest, CalculateHealth) {
    int health = HealthCalculator::calculate(3, 4);

    EXPECT_EQ(health, 16);
}

TEST(HealthCalculatorTest, ZeroShips) {
    int health = HealthCalculator::calculate(0, 5);
    EXPECT_EQ(health, 0);
}

TEST(HealthCalculatorTest, ZeroBiggestShip) {
    int health = HealthCalculator::calculate(5, 0);
    EXPECT_EQ(health, 0);
}