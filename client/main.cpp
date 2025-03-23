#include <boost/asio.hpp>
#include <iostream>

class Client {
public:
    Client(boost::asio::io_context& io_context, const std::string& host, short port)
        : socket_(io_context) {
        boost::asio::ip::tcp::resolver resolver(io_context);
        auto endpoints = resolver.resolve(host, std::to_string(port));
        boost::asio::connect(socket_, endpoints);
    }

    std::string sendCommand(const std::string& command) {
        boost::asio::write(socket_, boost::asio::buffer(command));
        boost::asio::streambuf buffer;
        boost::asio::read_until(socket_, buffer, "\n");
        return std::string(std::istreambuf_iterator<char>(&buffer), {});
    }

    void close() { socket_.close(); }

private:
    boost::asio::ip::tcp::socket socket_;
};

int main() {
    boost::asio::io_context io_context;

    // Клиент 1: Создаёт сессию
    Client client1(io_context, "127.0.0.1", 12345);
    std::cout << "Client 1: " << client1.sendCommand("CREATE\n");

    // Клиент 2: Присоединяется к сессии
    Client client2(io_context, "127.0.0.1", 12345);
    std::cout << "Client 2: " << client2.sendCommand("JOIN 3\n");

    // Клиент 1 делает ход
    std::cout << "Client 1 shot: " << client1.sendCommand("SHOT 3 4\n");
    std::cout << "Client 2 state: " << client2.sendCommand("STATE\n");

    client1.sendCommand("QUIT\n");
    client2.sendCommand("QUIT\n");

    return 0;
}