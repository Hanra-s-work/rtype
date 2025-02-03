#include "Server.hpp"
#include <iostream>
#include <chrono>

Server::Server()
{
    _gameWorld = std::make_unique<GameWorld>();
    _networkManager = std::make_unique<NetworkManager>(*_gameWorld);
}

Server::~Server()
{
    if (_running) {
        shutdown();
    }
}

void Server::run()
{
    std::cout << "Server is starting..." << std::endl;
    _running = true;

    _networkManager->start();

    _gameLoopThread = std::thread(&Server::gameLoop, this);

    if (_gameLoopThread.joinable()) {
        _gameLoopThread.join();
    }
}

void Server::gameLoop()
{
    using clock = std::chrono::steady_clock;
    auto previous = clock::now();

    while (_running) {
        auto current = clock::now();
        // Calculate dt as the actual elapsed time in seconds
        double dt = std::chrono::duration<double>(current - previous).count();
        previous = current; // Update previous time for the next iteration

        // Update game world with the actual dt
        _gameWorld->update(dt);

        // Check heartbeats
        _networkManager->checkHeartbeats();

        // Optionally broadcast state
        // _networkManager->broadcastState();

        // Sleep to avoid busy-waiting (adjust as needed)
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "Game loop ended.\n";
}

void Server::shutdown()
{
    _running = false;

    _networkManager->stop();

    if (_gameLoopThread.joinable()) {
        _gameLoopThread.join();
    }
}