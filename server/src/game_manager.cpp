#include "game_manager.hpp"
#include <iostream>
#include <algorithm>

// Suppose each GameLogic can handle up to 4 players.
static const size_t MAX_PLAYERS_PER_GAME = 4;

/**
 * @file game_manager.cpp
 * @brief Implementation of GameManager methods.
 */

uint32_t GameManager::assignClientToGame(uint32_t clientId) {
    // If the client is already assigned, return that existing game.
    auto it = clientToGame_.find(clientId);
    if (it != clientToGame_.end()) {
        return it->second;
    }

    // Otherwise, find or create a game that isn't full.
    uint32_t gameId = findOrCreateGame();
    auto &game = games_.at(gameId);

    // Add this client to the game.
    game.clients.push_back(clientId);
    clientToGame_[clientId] = gameId;

    // Notify the game logic that a new player joined.
    game.logic->addPlayer(clientId); // A hypothetical method in GameLogic.

    std::cout << "[GameManager] Assigned client " << clientId 
              << " to game " << gameId << "\n";
    return gameId;
}

void GameManager::removeClientFromGame(uint32_t clientId) {
    auto it = clientToGame_.find(clientId);
    if (it == clientToGame_.end()) {
        return; // client is not in any game
    }

    uint32_t gameId = it->second;
    auto &instance = games_.at(gameId);

    // Remove the clientId from the game's list of clients.
    auto &vec = instance.clients;
    vec.erase(std::remove(vec.begin(), vec.end(), clientId), vec.end());

    // Notify the game logic that a player left or crashed.
    instance.logic->removePlayer(clientId); // Hypothetical method in GameLogic.

    // Remove from client->game mapping.
    clientToGame_.erase(clientId);

    std::cout << "[GameManager] Removed client " << clientId 
              << " from game " << gameId << "\n";

    // If no clients remain, we can destroy the game.
    if (vec.empty()) {
        games_.erase(gameId);
        std::cout << "[GameManager] Destroyed game " << gameId 
                  << " (no remaining clients).\n";
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
    for (auto &pair : games_) {
        auto &inst = pair.second;
        // Update the GameLogic for each game.
        inst.logic->update(dt);
        // If the game logic has events to broadcast, you’d handle them here.
    }
}

void GameManager::handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg) {
    auto it = games_.find(gameId);
    if (it == games_.end()) return; // no such game

    auto &game = it->second;
    // Interpret the msg.type/payload and call the appropriate GameLogic method.
    // Example:
    // if (msg.type == 10) { decode payload, game.logic->movePlayer(clientId, x, y); }
    // else if (msg.type == 11) { game.logic->playerFire(clientId); }
    // This depends entirely on how your GameLogic is structured.

    (void)clientId; // silence unused warnings if not used.
    (void)msg;      // same reason
}

uint32_t GameManager::findOrCreateGame() {
    // Look for an existing game that isn’t full
    for (auto &pair : games_) {
        if (pair.second.clients.size() < MAX_PLAYERS_PER_GAME) {
            return pair.first;
        }
    }
    // Otherwise, create a new game
    uint32_t newId = nextGameId_++;
    GameInstance inst;
    inst.gameId = newId;
    inst.logic = std::make_unique<Game>(); // your existing logic
    games_[newId] = std::move(inst);

    std::cout << "[GameManager] Created new game with id " << newId << "\n";
    return newId;
}
