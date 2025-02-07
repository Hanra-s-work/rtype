//Server.hpp
#pragma once

#include "memory"
#include "thread"
#include "atomic"
#include "NetworkManager.hpp"
#include "GameWorld.hpp"

class Server {
public:
    Server();
    ~Server();
    void run();

private:
    void gameLoop();
    void shutdown();
    void resetGameSession(); // reinitialize the game state

    std::unique_ptr<NetworkManager> _networkManager;
    std::unique_ptr<GameWorld> _gameWorld;

    std::thread _gameLoopThread;
    std::atomic<bool> _running { false };

    uint32_t _globalScore = 0;
    bool _bossSpawned = false;

    bool _sessionActive = false;
};