#include "server.h"
#include <iostream>

Server::Server(boost::asio::io_context& io_context, short port)
    : io_context_(io_context),
      acceptor_(io_context, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)) {
    startAccept();
}

void Server::startAccept() {
    auto socket = std::make_shared<boost::asio::ip::tcp::socket>(io_context_);
    acceptor_.async_accept(*socket, [this, socket](const boost::system::error_code& error) {
        if (!error) {
            handleClient(socket);
        }
        startAccept();
    });
}

int Server::createSession() {
    boost::unique_lock lock(mutex_);
    int sessionId = nextSessionId_++;
    sessions_[sessionId] = GameFactory::createGame();
    return sessionId;
}

bool Server::joinSession(int sessionId, const std::shared_ptr<boost::asio::ip::tcp::socket> &socket, bool& isFirstPlayer) {
    boost::unique_lock lock(mutex_);
    auto it = sessions_.find(sessionId);
    if (it == sessions_.end()) {
        return false;
    }
    if (!firstPlayerSockets_.count(sessionId)) {
        firstPlayerSockets_[sessionId] = socket;
        isFirstPlayer = true;
        return true;
    } else if (!secondPlayerSockets_.count(sessionId)) {
        secondPlayerSockets_[sessionId] = socket;
        isFirstPlayer = false;
        return true;
    }
    return false;
}

void Server::handleClient(const std::shared_ptr<boost::asio::ip::tcp::socket>& socket) {
    boost::thread([this, socket]() {
        try {
            int sessionId = -1;
            bool isFirstPlayer = false;

            boost::asio::streambuf buffer;
            read_until(*socket, buffer, "\n");
            std::string command(std::istreambuf_iterator(&buffer), {});

            if (command == "CREATE\n") {
                sessionId = createSession();
                firstPlayerSockets_[sessionId] = socket;
                isFirstPlayer = true;
                std::string response = "SESSION " + std::to_string(sessionId) + " PLAYER 1\n";
                boost::asio::write(*socket, boost::asio::buffer(response));
            } else if (command.find("JOIN") == 0) {
                sessionId = std::stoi(command.substr(5));
                if (joinSession(sessionId, socket, isFirstPlayer)) {
                    std::string response = "SESSION " + std::to_string(sessionId) + " PLAYER " + (isFirstPlayer ? "1" : "2") + "\n";
                    boost::asio::write(*socket, boost::asio::buffer(response));
                } else {
                    boost::asio::write(*socket, boost::asio::buffer("SESSION FULL OR NOT FOUND\n"));
                    return;
                }
            } else {
                boost::asio::write(*socket, boost::asio::buffer("INVALID COMMAND\n"));
                return;
            }

            while (true) {
                read_until(*socket, buffer, "\n");
                std::string cmd(std::istreambuf_iterator(&buffer), {});

                if (cmd.find("SHOT") == 0) {
                    int x = std::stoi(cmd.substr(5, cmd.find(' ') - 5));
                    int y = std::stoi(cmd.substr(cmd.find(' ') + 1));
                    {
                        boost::unique_lock lock(mutex_);
                        auto game = sessions_[sessionId];
                        bool isFirstTurn = game->getPlayLogic()->isCounter();
                        if (isFirstPlayer == isFirstTurn) {
                            game->getPlayLogic()->shot(x, y);
                            std::string response = game->getPlayLogic()->endOfGame() ? "GAME OVER\n" : "OK\n";
                            boost::asio::write(*socket, boost::asio::buffer(response));

                            if (auto otherSocket = isFirstPlayer ? secondPlayerSockets_[sessionId] : firstPlayerSockets_[sessionId]) {
                                game->getConsole()->write(game->getPlayLogic());
                                std::string state = "UPDATE\n";
                                boost::asio::write(*otherSocket, boost::asio::buffer(state));
                            }
                        } else {
                            boost::asio::write(*socket, boost::asio::buffer("NOT YOUR TURN\n"));
                        }
                    }
                } else if (cmd == "STATE\n") {
                    std::string state;
                    {
                        boost::unique_lock lock(mutex_);
                        auto game = sessions_[sessionId];
                        game->getConsole()->write(game->getPlayLogic());
                        state = "TURN " + std::string(game->getPlayLogic()->isCounter() ? "1" : "2") + "\n";
                    }
                    boost::asio::write(*socket, boost::asio::buffer(state));
                } else if (cmd == "QUIT\n") {
                    break;
                }
            }
        } catch (const std::exception& e) {
            std::cerr << "Client error: " << e.what() << std::endl;
        }
    }).detach();
}