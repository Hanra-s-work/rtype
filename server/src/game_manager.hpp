#pragma once
#include <unordered_map>
#include <vector>
#include <cstdint>
#include <functional>
#include "Game.hpp"
#include "message.hpp"
#include "memory"

/**
 * @struct GameInstance
 * @brief A single game session: a Game object plus the connected clients.
 */
struct GameInstance {
    uint32_t gameId;
    std::unique_ptr<Game> game;
    std::vector<uint32_t> clients;
};

/**
 * @class GameManager
 * @brief Manages multiple Game instances and routes messages/events.
 *
 * broadcastFunc_ is a callback for sending network messages: 
 *   broadcastFunc_(clientId, Message);
 */
class GameManager {
public:
    using BroadcastFunc = std::function<void(uint32_t, const Message&)>;

    /**
     * @brief Constructor that takes a broadcast function (to send packets to clients).
     * @param broadcastFunc A function that can do "sendToClient(clientId, msg)".
     */
    explicit GameManager(BroadcastFunc broadcastFunc);

    /**
     * @brief Gets the current game state for syncing.
     */
    std::forward_list<std::string> syncClientToGame(uint32_t clientId);

    /**
     * @brief Assign a client to a new or existing game.
     */
    uint32_t assignClientToGame(uint32_t clientId);

    /**
     * @brief Remove a client from whichever game they are in.
     */
    void removeClientFromGame(uint32_t clientId);

    /**
     * @brief Get the game ID for a client, or 0 if none.
     */
    uint32_t getGameIdForClient(uint32_t clientId) const;

    /**
     * @brief Update all games with the given deltaTime and broadcast events to clients.
     */
    void updateAllGames(float dt);

    /**
     * @brief Handle a message from a client in a specific game.
     */
    void handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg);

private:
    /**
     * @brief Finds a game that isn't full or creates a new one.
     */
    uint32_t findOrCreateGame();

    // The broadcast function to call: broadcastFunc_(clientId, msg).
    BroadcastFunc broadcastFunc_;

    std::unordered_map<uint32_t, GameInstance> games_;
    std::unordered_map<uint32_t, uint32_t> clientToGame_;
    uint32_t nextGameId_ = 1;

    static const size_t MAX_PLAYERS_PER_GAME = 4; // Example capacity
};
