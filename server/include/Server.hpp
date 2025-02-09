//Server.hpp
#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include "asio.hpp"

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
    void resetGameSession();

    std::unique_ptr<NetworkManager> _networkManager;
    std::unique_ptr<GameWorld> _gameWorld;

    std::thread _gameLoopThread;
    std::atomic<bool> _running { false };

    bool _sessionActive = false;
};