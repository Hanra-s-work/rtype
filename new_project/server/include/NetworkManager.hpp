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
#include "../../common/NetworkProtocol.hpp"
#include "Player.hpp"
#include "Missile.hpp"

// Basic struct to hold network-level info for a client
struct PlayerInfo {
    uint32_t playerId;
    uint32_t entityId; // Link to in-game entity (e.g., the Player's ID)
    // e.g. lastHeartbeat, name, score, etc.
};

class GameWorld;

class NetworkManager {
public:
    // Construct with a reference (or pointer) to the GameWorld
    explicit NetworkManager(GameWorld& world);
    ~NetworkManager();

    void start();
    void stop();
    
    // Potentially used to process queued messages or do other periodic tasks
    void pollMessages();
    void broadcastState();

    // For sending a binary message to a specific client
    void sendBinaryMessage(MessageType type,
                           const std::vector<uint8_t>& payload,
                           const asio::ip::udp::endpoint& target);

    // Check for heartbeat timeouts
    void checkHeartbeats();

    // Notify other clients that a particular endpoint left the game
    void broadcastPlayerLeft(const asio::ip::udp::endpoint& clientEndpoint);

private:
    // Start async receive
    void doReceive();

    // Called when data arrives
    void onDataReceived(const std::string& dataStr,
                        const asio::ip::udp::endpoint& senderEndpoint);

private:
    // Reference (or pointer) to the game world for spawning/updating entities
    GameWorld& _gameWorld;

    asio::io_context _ioContext;
    std::unique_ptr<asio::ip::udp::socket> _socket;
    std::vector<std::thread> _ioThreads;
    std::atomic<bool> _running { false };

    // A list of all connected client endpoints for broadcasts
    std::vector<asio::ip::udp::endpoint> _clients;

    // Maps each endpoint -> PlayerInfo (which includes playerId, entityId, etc.)
    std::unordered_map<asio::ip::udp::endpoint, PlayerInfo> _connectedPlayers;

    // Used to generate unique player IDs
    std::atomic<uint32_t> _nextPlayerId {1};
    std::atomic<uint32_t> _nextMissileId {10000};

    // Heartbeat tracking: endpoint -> last heartbeat time
    std::unordered_map<asio::ip::udp::endpoint,
                       std::chrono::steady_clock::time_point> _clientHeartbeats;
};

// These remain your functions for building/parsing messages.
// Keep them in a shared location if both server & client use them.
std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);
std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);

