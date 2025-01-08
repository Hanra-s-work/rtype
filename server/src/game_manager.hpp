#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <cstdint>
#include "../../game_source/manager/include/Game.hpp"
#include "message.hpp"

/**
 * @struct GameInstance
 * @brief Holds a single instance of the game: a GameLogic object and a list of clients in that game.
 */
struct GameInstance {
    uint32_t gameId;                     ///< Unique ID for this game instance
    std::unique_ptr<Game> logic;    ///< The underlying GameLogic (already implemented)
    std::vector<uint32_t> clients;       ///< The client IDs currently in this game
};

/**
 * @class GameManager
 * @brief Manages multiple GameLogic instances (multiple games) and assigns clients to them.
 *
 * The GameManager can find a game that is not full, create new games, remove clients,
 * and dispatch messages to the appropriate GameLogic instance.
 */
class GameManager {
public:
    /**
     * @brief Assigns a client to an existing or new game.
     * @param clientId The unique client ID to assign.
     * @return The ID of the game the client was assigned to.
     */
    uint32_t assignClientToGame(uint32_t clientId);

    /**
     * @brief Removes a client from the game they are currently in.
     * @param clientId The unique client ID to remove.
     */
    void removeClientFromGame(uint32_t clientId);

    /**
     * @brief Retrieves the game ID for a given client, or 0 if not assigned.
     * @param clientId The unique client ID.
     * @return The ID of the game the client is in, or 0 if not found.
     */
    uint32_t getGameIdForClient(uint32_t clientId) const;

    /**
     * @brief Updates all active games, calling each game’s update(dt).
     * @param dt The time delta in seconds since the last update.
     */
    void updateAllGames(float dt);

    /**
     * @brief Dispatches a message to a specific game’s logic for handling (move, fire, etc.).
     * @param gameId The ID of the game instance.
     * @param clientId The client ID who sent the message.
     * @param msg The message to handle.
     */
    void handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg);

private:
    /**
     * @brief Searches for an existing game that isn’t full, or creates a new one.
     * @return The ID of the chosen or newly created game.
     */
    uint32_t findOrCreateGame();

    /// Maps gameId -> a GameInstance (includes the GameLogic).
    std::unordered_map<uint32_t, GameInstance> games_;

    /// Maps clientId -> gameId (which game a client belongs to).
    std::unordered_map<uint32_t, uint32_t> clientToGame_;

    /// Counter for assigning new game IDs.
    uint32_t nextGameId_ = 1;
};
