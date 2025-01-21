#include "src/server.hpp"
#include <thread>
#include <iostream>

/**
 * @file main.cpp
 * @brief Entry point for the R-Type server application.
 */
int main()
{
    try {
        asio::io_context io_context;

        // Create the server listening on UDP port 9000
        auto server = std::make_shared<Server>(io_context, 9000);

        // Start multiple I/O threads
        unsigned int numThreads = std::max(4u, std::thread::hardware_concurrency());
        std::vector<std::thread> threadPool;
        threadPool.reserve(numThreads);
        for (unsigned i = 0; i < numThreads; ++i) {
            threadPool.emplace_back([&io_context]() {
                io_context.run();
                });
        }

        bool running = true;
        std::thread gameLoopThread([&]() {
            using clock = std::chrono::steady_clock;
            auto lastTime = clock::now();

            while (running) {
                auto now = clock::now();
                float dt = std::chrono::duration<float>(now - lastTime).count();
                lastTime = now;

                // Update the Game instances
                server->getGameManager().updateAllGames(dt);

                // Sleep ~16ms => ~60 FPS
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
            });

        std::cout << "[Server] Listening on 0.0.0.0:9000 (UDP)\n";
        std::cout << "[Server] Press ENTER to quit.\n";
        std::cin.get();

        running = false;
        io_context.stop();

        for (auto &t : threadPool) {
            if (t.joinable()) t.join();
        }
        if (gameLoopThread.joinable()) {
            gameLoopThread.join();
        }

    }
    catch (std::exception &e) {
        std::cerr << "[Server] Exception: " << e.what() << "\n";
    }

    return 0;
}
