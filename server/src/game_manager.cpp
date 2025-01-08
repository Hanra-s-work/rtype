#include "game_manager.hpp"
#include <iostream>

// Suppose each GameLogic can handle 4 players
static const size_t MAX_PLAYERS_PER_GAME = 4;

uint32_t GameManager::assignClientToGame(uint32_t clientId) {
    // Already assigned?
    auto it = clientToGame_.find(clientId);
    if (it != clientToGame_.end()) {
        return it->second; // already assigned
    }

    // find or create a game
    uint32_t gameId = findOrCreateGame();
    auto &game = games_.at(gameId);

    game.clients.push_back(clientId);
    clientToGame_[clientId] = gameId;

    // Let the game logic know we have a new player
    game.logic->addPlayer(clientId); // assume a method addPlayer(clientId) exists

    std::cout << "[GameManager] Assigned client " << clientId 
              << " to game " << gameId << "\n";

    return gameId;
}

uint32_t GameManager::findOrCreateGame() {
    // find any existing game that is not full
    for (auto &pair : games_) {
        auto &inst = pair.second;
        if (inst.clients.size() < MAX_PLAYERS_PER_GAME) {
            return inst.gameId;
        }
    }
    // otherwise create a new game
    uint32_t newId = nextGameId_++;
    GameInstance inst;
    inst.gameId = newId;
    inst.logic = std::make_unique<Game>(); // your existing logic class
    games_[newId] = std::move(inst);

    std::cout << "[GameManager] Created new game with id " << newId << "\n";
    return newId;
}

void GameManager::removeClientFromGame(uint32_t clientId) {
    auto it = clientToGame_.find(clientId);
    if (it == clientToGame_.end()) return;

    uint32_t gameId = it->second;
    auto &game = games_.at(gameId);

    // remove from vector
    auto &vec = game.clients;
    vec.erase(std::remove(vec.begin(), vec.end(), clientId), vec.end());

    // notify the game logic
    game.logic->removePlayer(clientId);

    clientToGame_.erase(clientId);

    std::cout << "[GameManager] Removed client " << clientId 
              << " from game " << gameId << "\n";

    // If the game is empty, you could destroy it:
    if (vec.empty()) {
        games_.erase(gameId);
        std::cout << "[GameManager] Destroyed game " << gameId 
                  << " (no clients left).\n";
    }
}

uint32_t GameManager::getGameIdForClient(uint32_t clientId) const {
    auto it = clientToGame_.find(clientId);
    if (it == clientToGame_.end()) return 0;
    return it->second;
}

void GameManager::updateAllGames(float dt) {
    // for each game, call logic->update(dt)
    for (auto &pair : games_) {
        auto &gameInst = pair.second;
        gameInst.logic->update(dt);
        // If the logic has events to broadcast, handle them.
        // E.g. if (auto event = gameInst.logic->popEvent()) { ... }
    }
}

void GameManager::handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg) {
    auto it = games_.find(gameId);
    if (it == games_.end()) return; // no such game

    auto &g = it->second;

    // interpret your message types. E.g. if msg.type=10 => move
    // decode payload, call g.logic->moveEntity(...), etc.
    // This depends on your game logic interface.
    // For example:
    // if (msg.type == 10) { g.logic->movePlayer(clientId, x, y); }
    // else if (msg.type == 11) { g.logic->fireWeapon(clientId); }

    // Also handle crash detection or errors if needed.
}
