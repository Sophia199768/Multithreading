#include <gtest/gtest.h>
#include "../playLogic/PlayLogic.h"
#include <boost/shared_ptr.hpp>

class PlayLogicTest : public testing::Test {
protected:
    boost::shared_ptr<Player> firstPlayer;
    boost::shared_ptr<Player> secondPlayer;
    boost::shared_ptr<Board> board;

    void SetUp() override {
        board = boost::shared_ptr<Board>(new Board());
        firstPlayer = boost::shared_ptr<Player>(new Player(board, 5));
        secondPlayer = boost::shared_ptr<Player>(new Player(board, 5));
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
