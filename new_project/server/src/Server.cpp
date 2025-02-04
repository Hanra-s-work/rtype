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
    const double broadcastInterval = 0.1;

    while (_running) {
        auto current = clock::now();
        double dt = std::chrono::duration<double>(current - previous).count();
        previous = current;
        broadcastTimer += dt;

        bool spawnEnemies = _networkManager->hasClients();

        std::vector<Entity*> destroyedEntities;
        _gameWorld->update(static_cast<float>(dt), spawnEnemies, destroyedEntities);

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
                    }
                }
            }
        }
        for (Entity* destroyed : destroyedEntities)
            _networkManager->broadcastEntityDestroy(destroyed);
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