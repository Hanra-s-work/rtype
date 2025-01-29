#include "Server.hpp"
#include <iostream>
#include <chrono>

Server::Server()
{
    _networkManager = std::make_unique<NetworkManager>();
    _gameWorld = std::make_unique<GameWorld>();
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
    const double dt = 1.0 / 60.0;
    const auto step = std::chrono::duration<double>(dt);

    while (_running) {
        auto current = clock::now();
        auto elapsed = std::chrono::duration<double>(current - previous);

        if (elapsed >= step) {
            previous = current;
        }

        _networkManager->pollMessages(*_gameWorld);

        _gameWorld->update(dt);

        _networkManager->broadcastState(*_gameWorld);

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