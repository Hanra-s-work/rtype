#include "src/server.hpp"
#include <thread>
#include <iostream>

/**
 * @file main.cpp
 * @brief Entry point for the multigame server integrating the Game class.
 */

int main() {
    try {
        // Create an Asio I/O context for async operations
        asio::io_context io_context;

        // Create our Server listening on UDP port 9000
        auto server = std::make_shared<Server>(io_context, 9000);

        // Spawn a thread pool for I/O
        unsigned int numThreads = std::max(4u, std::thread::hardware_concurrency());
        std::vector<std::thread> threadPool;
        threadPool.reserve(numThreads);

        for (unsigned i = 0; i < numThreads; ++i) {
            threadPool.emplace_back([&io_context]() {
                io_context.run();
            });
        }

        // A separate thread to update all Game instances at ~60 FPS
        bool running = true;
        std::thread gameLoopThread([&]() {
            using clock = std::chrono::steady_clock;
            auto lastTime = clock::now();

            while (running) {
                auto now = clock::now();
                float dt = std::chrono::duration<float>(now - lastTime).count();
                lastTime = now;

                // Update all active games
                server->getGameManager().updateAllGames(dt);

                // Aim for 60 fps => ~16ms
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
        });

        // Wait for user input to stop
        std::cout << "[Server] Press ENTER to quit.\n";
        std::cin.get(); // blocking

        // Signal stop
        running = false;
        io_context.stop();

        // Join all threads
        for (auto &t : threadPool) {
            if (t.joinable()) t.join();
        }
        if (gameLoopThread.joinable()) {
            gameLoopThread.join();
        }

    } catch (std::exception& e) {
        std::cerr << "Server exception: " << e.what() << "\n";
    }

    return 0;
}
