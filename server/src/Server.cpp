//Server.cpp
#include "Server.hpp"
#include <iostream>
#include <chrono>
#include <thread>

// Resets the game session (for example, clear the GameWorld and reset global variables)
void Server::resetGameSession() {
    // Here you may call a reset method on GameWorld if you have one.
    // For simplicity, we recreate the GameWorld.
    _gameWorld = std::make_unique<GameWorld>();
    // (Optionally, reassign any callbacks on _gameWorld, such as onScoreUpdate.)
    _globalScore = 0;
    _bossSpawned = false;
    _sessionActive = true;
    std::cout << "Game session reset." << std::endl;
}

Server::Server() {
    _gameWorld = std::make_unique<GameWorld>();
    _networkManager = std::make_unique<NetworkManager>(*_gameWorld);
    
    // Set the callback so that when a client connects, the session is marked active.
    _networkManager->onNewConnection = [this](const asio::ip::udp::endpoint& ep) {
        if (!_sessionActive) {
            _sessionActive = true;
            std::cout << "New connection received from " << ep
                      << ". Marking session as active." << std::endl;
        }
    };

    // Optionally, set a callback on the GameWorld for score updates.
    _gameWorld->onScoreUpdate = [this](int points) {
        _globalScore += points;
        std::cout << "Global score updated to " << _globalScore << std::endl;
        // (You could broadcast the new score here if desired.)
    };
}

Server::~Server() {
    if (_running)
        shutdown();
}

void Server::run() {
    std::cout << "Server is starting..." << std::endl;
    _running = true;
    _networkManager->start();
    _gameLoopThread = std::thread(&Server::gameLoop, this);
    if (_gameLoopThread.joinable())
        _gameLoopThread.join();
}

void Server::gameLoop() {
    using clock = std::chrono::steady_clock;
    
    // Outer loop: the server keeps running.
    while (_running) {
        // Wait for at least one connected client.
        while (_running && !_networkManager->hasClients()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
            _networkManager->checkHeartbeats();
        }
        if (!_running)
            break;
        
        // Only reset the session if none is active.
        if (!_sessionActive) {
            resetGameSession();
            std::cout << "Starting new game session." << std::endl;
        }
        
        auto previous = clock::now();
        double broadcastTimer = 0.0;
        const double broadcastInterval = 0.1; // 100ms update interval
        
        bool sessionRunning = true;
        while (_running && sessionRunning) {
            auto current = clock::now();
            double dt = std::chrono::duration<double>(current - previous).count();
            previous = current;
            broadcastTimer += dt;
            
            // If no clients remain, end the session.
            if (!_networkManager->hasClients()) {
                std::cout << "No players connected. Ending game session." << std::endl;
                _networkManager->sendBinaryMessage(MessageType::HUB, {});
                sessionRunning = false;
                _sessionActive = false;
                break;
            }
            
            // Prepare containers for destruction and collision events.
            std::vector<GameWorld::DestroyEvent> destroyEvents;
            std::vector<GameWorld::CollisionEvent> collisionEvents;
            _gameWorld->update(static_cast<float>(dt), true, destroyEvents, collisionEvents);
            
            // Broadcast collision events.
            for (const auto &colEv : collisionEvents) {
                _networkManager->sendCollisionUpdate(colEv.posX, colEv.posY);
            }
            
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
                    }
                }
                // Broadcast global score to all clients.
                for (const auto &ep : _networkManager->getClients()) {
                    _networkManager->sendScoreMessage(_globalScore, ep);
                }
            }
            
            // Process destruction events.
            for (const auto &ev : destroyEvents) {
                _networkManager->broadcastEntityDestroy(ev.type, ev.id);
            }
            
            // Check lose condition by looking at connected players’ life.
            bool allPlayersDead = true;
            auto playersSnapshot = _gameWorld->getPlayersSnapshot();
            for (Entity* e : playersSnapshot) {
                if (Player* p = dynamic_cast<Player*>(e)) {
                    if (p->getLife() > 0) {
                        allPlayersDead = false;
                        break;
                    }
                }
            }
            if (allPlayersDead && !playersSnapshot.empty()) {
                _networkManager->sendBinaryMessage(MessageType::DEFEAT, {});
                std::cout << "All players are dead: DEFEAT condition reached." << std::endl;
                sessionRunning = false;
                _sessionActive = false;
                _networkManager->sendBinaryMessage(MessageType::HUB, {});
            }
            
            // Boss spawn and win condition.
            if (_globalScore >= 1000 && !_bossSpawned) {
                _bossSpawned = true;
                _gameWorld->spawnBoss();
            }
            if (_bossSpawned) {
                Entity* boss = nullptr;
                auto snapshot = _gameWorld->getEntitiesSnapshot();
                for (Entity* e : snapshot) {
                    if (e && e->getType() == EntityType::Boss) {
                        boss = e;
                        break;
                    }
                }
                if (boss == nullptr) { // Boss defeated.
                    _networkManager->sendBinaryMessage(MessageType::WIN, {});
                    std::cout << "Boss defeated: WIN condition reached." << std::endl;
                    sessionRunning = false;
                    _sessionActive = false;
                    _networkManager->sendBinaryMessage(MessageType::HUB, {});
                }
            }
            
            _networkManager->checkHeartbeats();
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        
        // After session ends, wait briefly before checking for new connections.
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    std::cout << "Game loop ended." << std::endl;
}

void Server::shutdown() {
    _running = false;
    _networkManager->stop();
    if (_gameLoopThread.joinable())
        _gameLoopThread.join();
}