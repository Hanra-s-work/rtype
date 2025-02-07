//NetworkManager.hpp
#pragma once

#include <asio.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <optional>
#include <iostream>
#include <cstdint>
#include <chrono>
#include <unordered_map>
#include <cstring>
#include <mutex>
#include <functional>
#include "../../common/NetworkProtocol.hpp"
#include "Player.hpp"
#include "Missile.hpp"
#include "GameWorld.hpp"

struct PlayerInfo {
    uint32_t playerId;
    uint32_t entityId;
};

class GameWorld;

class NetworkManager {
public:
    explicit NetworkManager(GameWorld& world);
    ~NetworkManager();

    void start();
    void stop();

    void sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload, const asio::ip::udp::endpoint& target);
    void sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload);

    void sendEntitySpawnMessage(Entity* entity, const asio::ip::udp::endpoint& target);
    void broadcastEntityUpdate(Entity* entity);
    void broadcastEntityDestroy(Entity* entity);
    void broadcastEntityDestroy(uint8_t type, uint32_t id);

    void checkHeartbeats();

    void broadcastPlayerLeft(const asio::ip::udp::endpoint& clientEndpoint);
    void sendLifeMessage(Player* player, const asio::ip::udp::endpoint& target);
    bool shouldSendLifeUpdate(uint32_t entityId, uint32_t currentLife);
    bool shouldSendScoreUpdate(uint32_t entityId, int currentScore);
    void sendScoreMessage(uint32_t score, const asio::ip::udp::endpoint& target);
    std::function<void(const asio::ip::udp::endpoint&)> onNewConnection;

    std::unordered_map<uint32_t, Vector2> _lastBroadcastedEntityPositions;

    bool hasClients() const;
    asio::ip::udp::endpoint getEndpointForEntity(uint32_t entityId) const;
    std::unordered_map<uint32_t, uint32_t> _lastBroadcastedLife;
    mutable std::mutex _lifeMutex;
    mutable std::mutex _mutex;
    std::vector<asio::ip::udp::endpoint> getClients();
    void sendCollisionUpdate(float posX, float posY);
    void removeClient(const asio::ip::udp::endpoint& ep);

private:
    void doReceive();

    void onDataReceived(const std::string& dataStr, const asio::ip::udp::endpoint& senderEndpoint);

    GameWorld& _gameWorld;

    asio::io_context _ioContext;
    std::unique_ptr<asio::ip::udp::socket> _socket;
    std::vector<std::thread> _ioThreads;
    std::atomic<bool> _running { false };

    std::vector<asio::ip::udp::endpoint> _clients;

    std::unordered_map<asio::ip::udp::endpoint, PlayerInfo> _connectedPlayers;

    std::unordered_map<asio::ip::udp::endpoint, std::chrono::steady_clock::time_point> _clientHeartbeats;
    std::unordered_map<uint32_t, int> _lastBroadcastedScore;
    mutable std::mutex _scoreMutex;
};

std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);
std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);
std::vector<uint8_t> buildEntityPayload(Entity* entity);
std::vector<uint8_t> buildDestroyEntityPayload(Entity* entity);
std::vector<uint8_t> buildLifePayload(Entity* entity, uint8_t life_remaining);
std::vector<uint8_t> buildScorePayload(uint32_t score);