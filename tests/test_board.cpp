#include <gtest/gtest.h>
#include "../board/Board.h"

TEST(BoardTest, SizeConstructor) {
    int size = 5;
    Board board(size);
    EXPECT_EQ(board.getBoardSizeWithoutBounds(), size);
    EXPECT_EQ(board.getBoardSizeWithBounds(), size + 2);
}

TEST(BoardTest, SetAndGet) {
    Board board(3);
    board.set(1, 1, 'X');
    auto& boardData = board.getBoard();
    EXPECT_EQ(boardData[1][1], 'X');
}
