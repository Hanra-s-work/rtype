#include "game_manager.hpp"

/**
 * @file game_manager.cpp
 * @brief Implementation of the GameManager class methods.
 */

uint32_t GameManager::assignClientToGame(uint32_t clientId) {
    // Check if already assigned
    auto it = clientToGame_.find(clientId);
    if (it != clientToGame_.end()) {
        return it->second;
    }

    // Otherwise find or create a new game
    uint32_t gid = findOrCreateGame();
    auto &gInst = games_.at(gid);

    gInst.clients.push_back(clientId);
    clientToGame_[clientId] = gid;

    std::cout << "[GameManager] Added client " << clientId 
              << " to game " << gid << "\n";

    // The Game class might have some method to handle a new player, or an event:
    // For example, create a spawn event or call onServerEventReceived(...).
    // We'll just illustrate:
    std::string connectEvent = "Player connected ID=" + std::to_string(clientId);
    gInst.game->onServerEventReceived(connectEvent);

    return gid;
}

void GameManager::removeClientFromGame(uint32_t clientId) {
    auto it = clientToGame_.find(clientId);
    if (it == clientToGame_.end()) return;

    uint32_t gid = it->second;
    auto &gInst = games_.at(gid);

    // Remove from client list
    auto &cList = gInst.clients;
    cList.erase(std::remove(cList.begin(), cList.end(), clientId), cList.end());

    // Possibly notify the Game that this player left:
    std::string disconnectEvent = "Player disconnected ID=" + std::to_string(clientId);
    gInst.game->onServerEventReceived(disconnectEvent);

    clientToGame_.erase(clientId);

    std::cout << "[GameManager] Removed client " << clientId 
              << " from game " << gid << "\n";

    // If the game is empty, we can remove it:
    if (cList.empty()) {
        games_.erase(gid);
        std::cout << "[GameManager] Destroyed game " << gid 
                  << " (no players left)\n";
    }
}

uint32_t GameManager::getGameIdForClient(uint32_t clientId) const {
    auto it = clientToGame_.find(clientId);
    if (it != clientToGame_.end()) {
        return it->second;
    }
    return 0;
}

void GameManager::updateAllGames(float dt) {
    // For each active game, call update
    for (auto &pair : games_) {
        auto &gInst = pair.second;
        gInst.game->update(dt);
        // Optionally collect events from gInst.game->getGameEvents() and broadcast them
    }
}

void GameManager::handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg) {
    auto it = games_.find(gameId);
    if (it == games_.end()) {
        return; // no such game
    }

    auto &gInst = it->second;

    // Typically, you would parse msg.payload into a GameMessage or some command structure
    // Then call gInst.game->onGameEventReceived(...) or similar
    // For demonstration, let's do a minimal approach:

    // 1) Convert the raw `Message` into a `GameMessage` if you want
    // We'll pretend the payload is a single integer or something.
    // Real code: you'd do more robust serialization, e.g. using `Game::deserialize`.
    if (!msg.payload.empty()) {
        // Suppose we interpret the first byte as a messageType
        // Or use your 'deserialize' logic:
        std::istringstream iss(std::string(
            reinterpret_cast<const char*>(msg.payload.data()), msg.payload.size()));
        GameMessage gm = gInst.game->deserialize(iss);

        // Now pass this to the game:
        gInst.game->onGameEventReceived(gm);
    } 
    else {
        // If there's no payload, maybe handle it differently
        // or do nothing
    }
}

uint32_t GameManager::findOrCreateGame() {
    // Find existing non-full game
    for (auto &pair : games_) {
        if (pair.second.clients.size() < MAX_PLAYERS_PER_GAME) {
            return pair.first;
        }
    }

    // Otherwise create a new one
    uint32_t gid = nextGameId_++;
    GameInstance gInst;
    gInst.gameId = gid;
    gInst.game = std::make_unique<Game>(); // your actual Game constructor
    games_[gid] = std::move(gInst);

    std::cout << "[GameManager] Created new game " << gid << "\n";
    return gid;
}
