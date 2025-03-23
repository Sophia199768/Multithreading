#include <gtest/gtest.h>
#include "../playLogic/PlayLogic.h"

class PlayLogicTest : public testing::Test {
protected:
    std::shared_ptr<Player> firstPlayer;
    std::shared_ptr<Player> secondPlayer;
    std::shared_ptr<Board> board;

    void SetUp() override {
        board = std::make_shared<Board>();
        firstPlayer = std::make_shared<Player>(board, 5);
        secondPlayer = std::make_shared<Player>(board, 5);
    }
};

TEST_F(PlayLogicTest, ConstructorAndGetters) {
    PlayLogic logic(true, firstPlayer, secondPlayer);
    EXPECT_TRUE(logic.isCounter());
    EXPECT_EQ(logic.getFirstPlayer(), firstPlayer);
    EXPECT_EQ(logic.getSecondPlayer(), secondPlayer);
}

TEST_F(PlayLogicTest, EndOfGame) {
    PlayLogic logic(false, firstPlayer, secondPlayer);
    EXPECT_FALSE(logic.endOfGame());


    while (firstPlayer->getHealth() > 0) {
        firstPlayer->minusHealth();
    }
    EXPECT_TRUE(logic.endOfGame());
}
