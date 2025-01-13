#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <cstdint>
#include <iostream>
#include <algorithm> // for std::remove
#include "../../game_source/manager/include/Game.hpp"           // Your main game logic
#include "message.hpp"        // Our minimal net message structure

/**
 * @struct GameInstance
 * @brief Holds a single `Game` instance plus a list of clients in that session.
 */
struct GameInstance {
    uint32_t gameId;                 ///< Unique ID for this game session
    std::unique_ptr<Game> game;      ///< The Game class instance
    std::vector<uint32_t> clients;   ///< The IDs of clients in this game
};

/**
 * @class GameManager
 * @brief Manages multiple `Game` sessions, assigning clients to them, and routing messages.
 */
class GameManager {
public:
    /**
     * @brief Assigns a client to an existing or newly created game.
     * @param clientId The unique ID of the client.
     * @return The ID of the game session the client is assigned to.
     */
    uint32_t assignClientToGame(uint32_t clientId);

    /**
     * @brief Removes a client from their current game (if any).
     * @param clientId The unique ID of the client.
     */
    void removeClientFromGame(uint32_t clientId);

    /**
     * @brief Retrieves the game ID for a given client.
     * @param clientId The unique ID of the client.
     * @return The game ID, or 0 if none.
     */
    uint32_t getGameIdForClient(uint32_t clientId) const;

    /**
     * @brief Updates all active games by calling `Game::update(dt)` on each.
     * @param dt The time delta since last frame, in seconds.
     */
    void updateAllGames(float dt);

    /**
     * @brief Routes a network-level Message to the appropriate `Game` instance.
     * @param gameId The ID of the game to handle the message.
     * @param clientId The ID of the client who sent it.
     * @param msg The decoded network message (4-byte header + payload).
     */
    void handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg);

private:
    /**
     * @brief Finds an existing game that isn't full, or creates a new one.
     * @return The ID of the chosen game.
     */
    uint32_t findOrCreateGame();

    std::unordered_map<uint32_t, GameInstance> games_;  ///< Maps gameId -> GameInstance
    std::unordered_map<uint32_t, uint32_t> clientToGame_; ///< Maps clientId -> gameId
    uint32_t nextGameId_ = 1; ///< Counter for assigning new game IDs

    static const size_t MAX_PLAYERS_PER_GAME = 4; ///< Example capacity
};
