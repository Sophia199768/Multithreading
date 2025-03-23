#include <gtest/gtest.h>
#include "../player/Player.h"

TEST(PlayerTest, MinusHealth) {
    Player player(nullptr, 10);
    player.minusHealth();
    EXPECT_EQ(player.getHealth(), 9);
    player.minusHealth();
    EXPECT_EQ(player.getHealth(), 8);
}