#include "src/server.hpp"
#include <thread>
#include <iostream>

int main() {
    try {
        asio::io_context io_context;

        // Create the server: port 9000 for clients, 9001 for logic
        auto server = std::make_shared<Server>(io_context, 9000, 9001);

        // Run io_context in multiple threads for concurrency
        std::vector<std::thread> thread_pool;
        unsigned int num_threads = std::thread::hardware_concurrency();
        if (num_threads == 0) num_threads = 4;

        for (unsigned int i = 0; i < num_threads; ++i) {
            thread_pool.emplace_back([&io_context]() {
                io_context.run();
            });
        }

        // Wait for all threads
        for (auto &t : thread_pool) {
            t.join();
        }

    } catch (std::exception& e) {
        std::cerr << "Server exception: " << e.what() << "\n";
    }

    return 0;
}
