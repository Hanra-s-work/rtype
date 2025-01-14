#include "game_manager.hpp"
#include <algorithm>
#include <iostream>

const size_t GameManager::MAX_PLAYERS_PER_GAME;

GameManager::GameManager(BroadcastFunc broadcastFunc)
  : broadcastFunc_(std::move(broadcastFunc))
{ }

uint32_t GameManager::assignClientToGame(uint32_t clientId) {
    // If already assigned, return existing
    auto it = clientToGame_.find(clientId);
    if (it != clientToGame_.end()) {
        return it->second;
    }

    // Otherwise find/create
    uint32_t gid = findOrCreateGame();
    auto &gInst = games_.at(gid);

    gInst.clients.push_back(clientId);
    clientToGame_[clientId] = gid;

    std::cout << "[GameManager] Added client " << clientId 
              << " to game " << gid << "\n";

    // Possibly let the Game know about a connect event:
    // e.g. some string or a custom GameMessage
    std::string evt = "\x01" + std::to_string(clientId);
    gInst.game->onServerEventReceived(evt);

    return gid;
}

void GameManager::removeClientFromGame(uint32_t clientId) {
    auto it = clientToGame_.find(clientId);
    if (it == clientToGame_.end()) {
        return;
    }

    uint32_t gid = it->second;
    auto &gInst = games_.at(gid);

    // remove from vector
    auto &cList = gInst.clients;
    cList.erase(std::remove(cList.begin(), cList.end(), clientId), cList.end());

    // Possibly inform the game of a disconnect
    std::string evt = "\x02" + std::to_string(clientId);
    gInst.game->onServerEventReceived(evt);

    clientToGame_.erase(clientId);

    std::cout << "[GameManager] Removed client " << clientId 
              << " from game " << gid << "\n";

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
    for (auto &pair : games_) {
        auto &gInst = pair.second;

        // 1) Update the game logic
        gInst.game->update(dt);

        // 2) Suppose getGameEvents() returns a list of strings
        auto events = gInst.game->getGameEvents();

        // 3) For each event, broadcast to each client in gInst.clients
        for (const auto &evt : events) {
            // Let's build a small Message to send
            Message outMsg;
            outMsg.type = 100; // some code meaning "GameEvent"

            // Put the string in outMsg.payload
            outMsg.payload.assign(evt.begin(), evt.end());

            // Send to each client
            for (auto cid : gInst.clients) {
                broadcastFunc_(cid, outMsg);
            }
        }
    }
}

void GameManager::handleGameMessage(uint32_t gameId, uint32_t clientId, const Message& msg) {
    auto it = games_.find(gameId);
    if (it == games_.end()) return;

    auto &gInst = it->second;

    // For demonstration, let's say we interpret the payload as a string
    if (!msg.payload.empty()) {
        std::string eventString(
            reinterpret_cast<const char*>(msg.payload.data()),
            msg.payload.size()
        );
        // Then feed that into the game as an event
        gInst.game->onServerEventReceived(eventString);
    } else {
        // or do something if no payload
    }
}

uint32_t GameManager::findOrCreateGame() {
    // Look for an existing not-full game
    for (auto &pair : games_) {
        if (pair.second.clients.size() < MAX_PLAYERS_PER_GAME) {
            return pair.first;
        }
    }
    // Otherwise create new
    uint32_t gid = nextGameId_++;
    GameInstance gInst;
    gInst.gameId = gid;
    gInst.game = std::make_unique<Game>(); // your actual game constructor
    games_[gid] = std::move(gInst);

    std::cout << "[GameManager] Created new game " << gid << "\n";
    return gid;
}
