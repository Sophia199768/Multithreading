#pragma once
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <memory>
#include <unordered_map>
#include "../game/Game.h"
#include "../game/GameFactory.h"

class Server {
public:
    Server(boost::asio::io_context& io_context, short port);

    void startAccept();
    void handleClient(const std::shared_ptr<boost::asio::ip::tcp::socket>& socket);

    int createSession();
    bool joinSession(int sessionId, const std::shared_ptr<boost::asio::ip::tcp::socket> &socket, bool& isFirstPlayer);

    boost::asio::io_context& getIoContext() { return io_context_; }
private:
    boost::asio::io_context& io_context_;
    boost::asio::ip::tcp::acceptor acceptor_;
    std::unordered_map<int, std::shared_ptr<Game>> sessions_;
    std::unordered_map<int, std::shared_ptr<boost::asio::ip::tcp::socket>> firstPlayerSockets_;
    std::unordered_map<int, std::shared_ptr<boost::asio::ip::tcp::socket>> secondPlayerSockets_;
    boost::mutex mutex_;
    int nextSessionId_ = 1;
};