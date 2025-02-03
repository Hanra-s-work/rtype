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
    double broadcastTimer = 0.0;
    const double broadcastInterval = 0.1; // broadcast delta updates every 100ms

    while (_running) {
        auto current = clock::now();
        double dt = std::chrono::duration<double>(current - previous).count();
        previous = current;

        // Update the game world (spawning monsters, moving entities, collision detection, etc.)
        _gameWorld->update(dt);

        // Accumulate time for broadcasting updates.
        broadcastTimer += dt;
        if (broadcastTimer >= broadcastInterval) {
            broadcastTimer = 0.0;
            _networkManager->broadcastStateDelta(); // You can rename broadcastStateDelta to broadcastStateDelta() as implemented above.
        }

        // Check heartbeats
        _networkManager->checkHeartbeats();

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