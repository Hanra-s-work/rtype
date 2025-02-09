/**
 * @file Server.hpp
 * @brief Declaration of the Server class.
 *
 * The Server class is responsible for running the game server, handling network communication,
 * managing game sessions, and resetting the game state between sessions.
 */

#pragma once

#include <memory>
#include <thread>
#include <atomic>
#include "asio.hpp"
#include "NetworkManager.hpp"
#include "GameWorld.hpp"

/**
 * @class Server
 * @brief The main game server.
 *
 * The Server class initializes the game world and network manager, runs the main game loop,
 * and manages game sessions and shutdown.
 */
class Server {
public:
    /**
     * @brief Constructs a new Server object.
     */
    Server();

    /**
     * @brief Destroys the Server object.
     */
    ~Server();

    /**
     * @brief Runs the server.
     */
    void run();

private:
    /**
     * @brief The main game loop.
     */
    void gameLoop();

    /**
     * @brief Shuts down the server.
     */
    void shutdown();

    /**
     * @brief Resets the game session.
     *
     * This function clears the game world, resets scores, and marks the session as active.
     */
    void resetGameSession();

    std::unique_ptr<NetworkManager> _networkManager; /**< The network manager handling UDP communication. */
    std::unique_ptr<GameWorld> _gameWorld;           /**< The game world containing all entities. */
    std::thread _gameLoopThread;                     /**< Thread that runs the game loop. */
    std::atomic<bool> _running { false };            /**< Flag indicating if the server is running. */
    bool _sessionActive = false;                     /**< Indicates if a game session is currently active. */
};