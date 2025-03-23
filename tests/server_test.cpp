#include <gtest/gtest.h>
#include "../server/server.h"
#include <boost/asio.hpp>


class ServerTest : public ::testing::Test {
protected:
    void SetUp() override {
        server = std::make_unique<Server>(io_context_, 12345);
    }

    boost::asio::io_context io_context_;
    std::unique_ptr<Server> server;
};

TEST_F(ServerTest, CreateSession) {
    int sessionId = server->createSession();
    EXPECT_EQ(sessionId, 1);

    int sessionId2 = server->createSession();
    EXPECT_EQ(sessionId2, 2);
}

TEST_F(ServerTest, JoinSession) {
    int sessionId = server->createSession();
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    bool isFirstPlayer;

    bool joined = server->joinSession(sessionId, socket, isFirstPlayer);
    EXPECT_TRUE(joined);
    EXPECT_TRUE(isFirstPlayer);

    auto socket2 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    joined = server->joinSession(sessionId, socket2, isFirstPlayer);
    EXPECT_TRUE(joined);
    EXPECT_FALSE(isFirstPlayer);
}

TEST_F(ServerTest, JoinFullSession) {
    int sessionId = server->createSession();

    auto socket1 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    bool isFirstPlayer;
    server->joinSession(sessionId, socket1, isFirstPlayer);

    auto socket2 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    server->joinSession(sessionId, socket2, isFirstPlayer);

    auto socket3 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    bool joined = server->joinSession(sessionId, socket3, isFirstPlayer);
    EXPECT_FALSE(joined);
}

TEST_F(ServerTest, JoinNonExistentSession) {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    bool isFirstPlayer;
    bool joined = server->joinSession(999, socket, isFirstPlayer);
    EXPECT_FALSE(joined);
}

TEST_F(ServerTest, ThreeSessionsSixPlayers) {
    int sessionId1 = server->createSession();
    int sessionId2 = server->createSession();
    int sessionId3 = server->createSession();

    EXPECT_EQ(sessionId1, 1);
    EXPECT_EQ(sessionId2, 2);
    EXPECT_EQ(sessionId3, 3);

    auto socket1 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    auto socket2 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    auto socket3 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    auto socket4 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    auto socket5 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());
    auto socket6 = std::make_shared<boost::asio::ip::tcp::socket>(server->getIoContext());

    bool isFirstPlayer;

    bool joined1 = server->joinSession(sessionId1, socket1, isFirstPlayer);
    EXPECT_TRUE(joined1);
    EXPECT_TRUE(isFirstPlayer);

    bool joined2 = server->joinSession(sessionId1, socket2, isFirstPlayer);
    EXPECT_TRUE(joined2);
    EXPECT_FALSE(isFirstPlayer);

    bool joined3 = server->joinSession(sessionId2, socket3, isFirstPlayer);
    EXPECT_TRUE(joined3);
    EXPECT_TRUE(isFirstPlayer);

    bool joined4 = server->joinSession(sessionId2, socket4, isFirstPlayer);
    EXPECT_TRUE(joined4);
    EXPECT_FALSE(isFirstPlayer);

    bool joined5 = server->joinSession(sessionId3, socket5, isFirstPlayer);
    EXPECT_TRUE(joined5);
    EXPECT_TRUE(isFirstPlayer);

    bool joined6 = server->joinSession(sessionId3, socket6, isFirstPlayer);
    EXPECT_TRUE(joined6);
    EXPECT_FALSE(isFirstPlayer);
}
