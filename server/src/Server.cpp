//Server.cpp
#include "Server.hpp"
#include <iostream>
#include <chrono>

Server::Server()
{
    _gameWorld = std::make_unique<GameWorld>();
    _networkManager = std::make_unique<NetworkManager>(*_gameWorld);
    _networkManager->onNewConnection = [this](const asio::ip::udp::endpoint& ep) {
        _networkManager->sendScoreMessage(_globalScore, ep);
    };
}

Server::~Server()
{
    if (_running)
        shutdown();
}

void Server::run()
{
    std::cout << "Server is starting..." << std::endl;
    _running = true;
    _networkManager->start();
    _gameLoopThread = std::thread(&Server::gameLoop, this);
    if (_gameLoopThread.joinable())
        _gameLoopThread.join();
}

void Server::gameLoop()
{
    using clock = std::chrono::steady_clock;
    auto previous = clock::now();
    double broadcastTimer = 0.0;
    const double broadcastInterval = 0.1; // every 100ms

    while (_running) {
        auto current = clock::now();
        double dt = std::chrono::duration<double>(current - previous).count();
        previous = current;
        broadcastTimer += dt;

        bool spawnEnemies = _networkManager->hasClients();

        // Use a vector of DestroyEvent (as defined in GameWorld.hpp)
        std::vector<GameWorld::DestroyEvent> destroyEvents;
        _gameWorld->update(static_cast<float>(dt), spawnEnemies, destroyEvents);

        if (broadcastTimer >= broadcastInterval) {
            broadcastTimer = 0.0;
            auto entitiesSnapshot = _gameWorld->getEntitiesSnapshot();
            for (Entity* entity : entitiesSnapshot) {
                _networkManager->broadcastEntityUpdate(entity);

                if (Player* player = dynamic_cast<Player*>(entity)) {
                    uint32_t currentLife = player->getLife();
                    try {
                        asio::ip::udp::endpoint ep = _networkManager->getEndpointForEntity(player->getId());
                        if (_networkManager->shouldSendLifeUpdate(player->getId(), currentLife))
                            _networkManager->sendLifeMessage(player, ep);
                    } catch (const std::exception &ex) {
                        std::cerr << "Error sending life message for entity " 
                                  << player->getId() << ": " << ex.what() << std::endl;
                    }

                    int currentScore = player->getScore();
                    try {
                        asio::ip::udp::endpoint ep = _networkManager->getEndpointForEntity(player->getId());
                        if (_networkManager->shouldSendScoreUpdate(player->getId(), currentScore))
                            _networkManager->sendScoreMessage(static_cast<uint32_t>(currentScore), ep);
                    } catch (const std::exception &ex) {
                        std::cerr << "Error sending score message for entity " 
                                  << player->getId() << ": " << ex.what() << std::endl;
                    }
                }
            }
        }

        // For each destroy event, broadcast the corresponding DESTROY_ENTITY message.
        for (const auto &ev : destroyEvents) {
            _networkManager->broadcastEntityDestroy(ev.type, ev.id);
        }

        _networkManager->checkHeartbeats();
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    std::cout << "Game loop ended." << std::endl;
}

void Server::shutdown()
{
    _running = false;
    _networkManager->stop();
    if (_gameLoopThread.joinable())
        _gameLoopThread.join();
}