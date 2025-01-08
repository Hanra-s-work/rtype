#include "src/server.hpp"
#include <thread>
#include <iostream>

int main() {
    try {
        asio::io_context io_context;

        // Create server on UDP port 9000, binding to 0.0.0.0 so it’s accessible on the LAN
        auto server = std::make_shared<Server>(io_context, 9000);

        // Thread pool for running async I/O
        unsigned int numThreads = std::max(4u, std::thread::hardware_concurrency());
        std::vector<std::thread> threadPool;
        threadPool.reserve(numThreads);

        for (unsigned i = 0; i < numThreads; ++i) {
            threadPool.emplace_back([&io_context]() {
                io_context.run();
            });
        }

        // Optional: A dedicated update loop for the games if needed
        // (some people run game update logic in each GameLogic object on separate threads,
        //  or on a single loop in main. This example does a single “manager” loop.)
        bool running = true;
        std::thread gameLoopThread([&]() {
            using clock = std::chrono::steady_clock;
            auto lastTime = clock::now();

            while (running) {
                auto now = clock::now();
                float dt = std::chrono::duration<float>(now - lastTime).count();
                lastTime = now;

                // Update all games
                server->getGameManager().updateAllGames(dt);

                // Sleep to aim for ~60 fps or so
                std::this_thread::sleep_for(std::chrono::milliseconds(16));
            }
        });

        // Wait for user input to exit or do some other means
        std::cout << "[Server] Press ENTER to quit.\n";
        std::cin.get(); // blocking read

        running = false; // signal to stop game loop
        io_context.stop(); // stop I/O

        // Join threads
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
