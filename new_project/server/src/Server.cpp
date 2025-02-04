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
    double updateAccumulator = 0.0;
    const double broadcastInterval = 0.1; // broadcast updates every 100ms

    while (_running) {
        auto current = clock::now();
        double dt = std::chrono::duration<double>(current - previous).count();
        previous = current;
        updateAccumulator += dt;

        // Update the game world (spawning monsters, moving entities, collisions, etc.)
        _gameWorld->update(dt, /*spawnEnemies=*/_networkManager->hasClients());

        // Broadcast entity updates only every broadcastInterval seconds
        if (updateAccumulator >= broadcastInterval) {
            updateAccumulator = 0.0;
            // Take a snapshot of entities (raw pointers) from GameWorld.
            auto entitiesSnapshot = _gameWorld->getEntitiesSnapshot();
            for (Entity* entity : entitiesSnapshot) {
                // For each entity, send an UPDATE_ENTITY message.
                _networkManager->broadcastEntityUpdate(entity);
            }
        }

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