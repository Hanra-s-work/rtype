#include "src/server.hpp"
#include <thread>
#include <iostream>

/**
 * @file main.cpp
 * @brief Entry point for the multigame server.
 *
 * Creates the server, spawns I/O threads, and runs a game loop thread.
 */

int main() {
    try {
        // Create an Asio I/O context for asynchronous operations.
        asio::io_context io_context;

        // Create the server object, listening on UDP port 9000.
        auto server = std::make_shared<Server>(io_context, 9000);

        // Decide how many threads to use for I/O.
        unsigned int numThreads = std::max(4u, std::thread::hardware_concurrency());
        std::vector<std::thread> threadPool;
        threadPool.reserve(numThreads);

        // Start multiple threads to call io_context.run(), enabling concurrent async operations.
        for (unsigned i = 0; i < numThreads; ++i) {
            threadPool.emplace_back([&io_context]() {
                io_context.run();
            });
        }

        // We'll run a dedicated game loop in a separate thread.
        bool running = true;
        std::thread gameLoopThread([&]() {
            using clock = std::chrono::steady_clock;
            auto lastTime = clock::now();

            while (running) {
                auto now = clock::now();
                float dt = std::chrono::duration<float>(now - lastTime).count();
                lastTime = now;

                // Update all active games in the server's GameManager.
                server->getGameManager().updateAllGames(dt);

                // Sleep to target ~60fps or so.
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
        });

        // Wait for the user to press ENTER, then stop.
        std::cout << "[Server] Press ENTER to quit.\n";
        std::cin.get(); // blocking read

        // Signal to stop the game loop and stop Asio I/O.
        running = false;
        io_context.stop();

        // Join all I/O threads.
        for (auto &t : threadPool) {
            if (t.joinable()) t.join();
        }
        // Join the game loop thread.
        if (gameLoopThread.joinable()) {
            gameLoopThread.join();
        }

    } catch (std::exception& e) {
        std::cerr << "Server exception: " << e.what() << "\n";
    }

    return 0;
}
