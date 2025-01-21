#include "src/server.hpp"
#include <thread>
#include <iostream>
#include <string>

/**
 * @file main.cpp
 * @brief Entry point for the R-Type server application.
 */

// A small helper to print usage
static void print_usage(const char* progName) {
    std::cout << "Usage: " << progName << " [OPTIONS]\n"
              << "\nOptions:\n"
              << "  --help           Show this help message and exit\n"
              << "  --port <number>  Specify the UDP port to use (default: 9000)\n"
              << std::endl;
}

int main(int argc, char* argv[])
{
    // Default port
    unsigned short port = 9000;

    // Parse command-line arguments
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "--help") {
            // Print usage and exit
            print_usage(argv[0]);
            return 0;
        } 
        else if (arg == "--port") {
            if (i + 1 < argc) {
                ++i; // move to the next argument
                try {
                    port = static_cast<unsigned short>(std::stoi(argv[i]));
                } catch (...) {
                    std::cerr << "[Error] Invalid or out-of-range port: " << argv[i] << "\n";
                    return 1;
                }
            } else {
                // Missing port number
                std::cerr << "[Error] '--port' requires an argument.\n";
                print_usage(argv[0]);
                return 1;
            }
        } 
        else {
            std::cerr << "[Error] Unknown option: " << arg << "\n";
            print_usage(argv[0]);
            return 1;
        }
    }

    try {
        // Create the io_context
        asio::io_context io_context;

        // Create the server listening on the parsed 'port'
        auto server = std::make_shared<Server>(io_context, port);

        // Start multiple I/O threads
        unsigned int numThreads = std::max(4u, std::thread::hardware_concurrency());
        std::vector<std::thread> threadPool;
        threadPool.reserve(numThreads);
        for (unsigned i = 0; i < numThreads; ++i) {
            threadPool.emplace_back([&io_context]() {
                io_context.run();
            });
        }

        // Run game loop
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

        // Inform user
        std::cout << "[Server] Listening on 0.0.0.0:" << port << " (UDP)\n";
        std::cout << "[Server] Press ENTER to quit.\n";
        std::cin.get();

        // Stop
        running = false;
        io_context.stop();

        for (auto &t : threadPool) {
            if (t.joinable()) t.join();
        }
        if (gameLoopThread.joinable()) {
            gameLoopThread.join();
        }

    } catch (std::exception& e) {
        std::cerr << "[Server] Exception: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
