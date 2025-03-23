#include "server.h"

int main() {
    boost::asio::io_context io_context;
    Server server(io_context, 12345);

    boost::thread_group threads;
    for (int i = 0; i < 4; ++i) {
        threads.create_thread([&io_context]() { io_context.run(); });
    }
    threads.join_all();

    return 0;
}