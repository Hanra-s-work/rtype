#pragma once
#include <unordered_map>
#include <memory>
#include <vector>
#include <cstdint>
#include "../../game_source/manager/include/Game.hpp"
#include "message.hpp"

// A struct representing one active game
struct GameInstance {
    uint32_t gameId;
    std::unique_ptr<Game> logic;
    std::vector<uint32_t> clients; // list of client IDs
};

class GameManager {
public:
    // Create or pick a game that isn't full, assign the client
    uint32_t assignClientToGame(uint32_t clientId);

    // Remove client from whichever game they're in
    void removeClientFromGame(uint32_t clientId);

    // Return the gameId for a client
    uint32_t getGameIdForClient(uint32_t clientId) const;

    // Called each frame by main or server
    void updateAllGames(float dt);

    // Handle a message for a given game
    void handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg);

private:
    // You might store each game in a map
    std::unordered_map<uint32_t, GameInstance> games_;
    // clientId -> gameId
    std::unordered_map<uint32_t, uint32_t> clientToGame_;
    uint32_t nextGameId_ = 1;

    // pick a game or create a new one
    uint32_t findOrCreateGame();
};
