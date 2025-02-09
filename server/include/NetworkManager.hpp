/**
 * @file NetworkManager.hpp
 * @brief Declaration of the NetworkManager class.
 *
 * The NetworkManager handles UDP networking using ASIO. It is responsible for
 * sending and receiving game messages, broadcasting updates, and handling client connections.
 */

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

/**
 * @struct PlayerInfo
 * @brief Stores information about a connected player.
 */
struct PlayerInfo {
    uint32_t playerId; /**< The player's unique ID. */
    uint32_t entityId; /**< The player's associated entity ID. */
};

/**
 * @class NetworkManager
 * @brief Handles network communication for the server.
 *
 * This class uses ASIO to send and receive UDP messages, and is responsible for
 * broadcasting entity updates, sending life and score updates, and handling client heartbeats.
 */
class NetworkManager {
public:
    /**
     * @brief Constructs a new NetworkManager object.
     * @param world Reference to the game world.
     */
    explicit NetworkManager(GameWorld& world);

    /**
     * @brief Destroys the NetworkManager object.
     */
    ~NetworkManager();

    /**
     * @brief Starts the network manager.
     */
    void start();

    /**
     * @brief Stops the network manager.
     */
    void stop();

    /**
     * @brief Sends a binary message to a specific target.
     * @param type The message type.
     * @param payload The message payload.
     * @param target The target UDP endpoint.
     */
    void sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload, const asio::ip::udp::endpoint& target);

    /**
     * @brief Sends a binary message to all connected clients.
     * @param type The message type.
     * @param payload The message payload.
     */
    void sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload);

    /**
     * @brief Sends a spawn entity message to a target.
     * @param entity Pointer to the entity to spawn.
     * @param target The target UDP endpoint.
     */
    void sendEntitySpawnMessage(Entity* entity, const asio::ip::udp::endpoint& target);

    /**
     * @brief Broadcasts an update entity message to all clients.
     * @param entity Pointer to the entity to update.
     */
    void broadcastEntityUpdate(Entity* entity);

    /**
     * @brief Broadcasts a destroy entity message to all clients for a given entity.
     * @param entity Pointer to the entity to destroy.
     */
    void broadcastEntityDestroy(Entity* entity);

    /**
     * @brief Broadcasts a destroy entity message using the specified type and id.
     * @param type The entity type.
     * @param id The entity id.
     */
    void broadcastEntityDestroy(uint8_t type, uint32_t id);

    /**
     * @brief Checks the heartbeat of each client and removes timed-out clients.
     */
    void checkHeartbeats();

    /**
     * @brief Broadcasts a player left message to all clients.
     * @param clientEndpoint The endpoint of the client that left.
     */
    void broadcastPlayerLeft(const asio::ip::udp::endpoint& clientEndpoint);

    /**
     * @brief Sends a life update message for a player.
     * @param player Pointer to the player.
     * @param target The target UDP endpoint.
     */
    void sendLifeMessage(Player* player, const asio::ip::udp::endpoint& target);

    /**
     * @brief Determines whether a life update should be sent.
     * @param entityId The entity id.
     * @param currentLife The current life value.
     * @return true if an update should be sent, false otherwise.
     */
    bool shouldSendLifeUpdate(uint32_t entityId, uint32_t currentLife);

    /**
     * @brief Determines whether a score update should be sent.
     * @param entityId The entity id.
     * @param currentScore The current score.
     * @return true if an update should be sent, false otherwise.
     */
    bool shouldSendScoreUpdate(uint32_t entityId, int currentScore);

    /**
     * @brief Sends a score update message to a target.
     * @param score The global score.
     * @param target The target UDP endpoint.
     */
    void sendScoreMessage(uint32_t score, const asio::ip::udp::endpoint& target);

    /**
     * @brief Callback for new client connections.
     */
    std::function<void(const asio::ip::udp::endpoint&)> onNewConnection;

    std::unordered_map<uint32_t, Vector2> _lastBroadcastedEntityPositions; /**< Last broadcasted entity positions. */

    /**
     * @brief Checks if there are any connected clients.
     * @return true if at least one client is connected, false otherwise.
     */
    bool hasClients() const;

    /**
     * @brief Retrieves the UDP endpoint associated with an entity id.
     * @param entityId The entity id.
     * @return asio::ip::udp::endpoint The associated endpoint.
     * @throws std::runtime_error if no endpoint is found.
     */
    asio::ip::udp::endpoint getEndpointForEntity(uint32_t entityId) const;

    std::unordered_map<uint32_t, uint32_t> _lastBroadcastedLife; /**< Last broadcasted life values. */
    mutable std::mutex _lifeMutex;  /**< Mutex for protecting life updates. */
    mutable std::mutex _mutex;      /**< General mutex for internal data protection. */

    /**
     * @brief Gets the list of all client endpoints.
     * @return std::vector<asio::ip::udp::endpoint> List of client endpoints.
     */
    std::vector<asio::ip::udp::endpoint> getClients();

    /**
     * @brief Sends a collision update message.
     * @param posX The x-coordinate of the collision.
     * @param posY The y-coordinate of the collision.
     */
    void sendCollisionUpdate(float posX, float posY);

    /**
     * @brief Removes a client from the internal list.
     * @param ep The client's UDP endpoint.
     */
    void removeClient(const asio::ip::udp::endpoint& ep);

private:
    /**
     * @brief Starts asynchronous receive operations.
     */
    void doReceive();

    /**
     * @brief Handles incoming data.
     * @param dataStr The raw data string.
     * @param senderEndpoint The sender's UDP endpoint.
     */
    void onDataReceived(const std::string& dataStr, const asio::ip::udp::endpoint& senderEndpoint);

    GameWorld& _gameWorld; /**< Reference to the game world. */
    asio::io_context _ioContext; /**< ASIO I/O context. */
    std::unique_ptr<asio::ip::udp::socket> _socket; /**< UDP socket. */
    std::vector<std::thread> _ioThreads; /**< I/O threads. */
    std::atomic<bool> _running { false }; /**< Flag indicating whether networking is running. */
    std::vector<asio::ip::udp::endpoint> _clients; /**< List of connected client endpoints. */
    std::unordered_map<asio::ip::udp::endpoint, PlayerInfo> _connectedPlayers; /**< Mapping of client endpoints to player info. */
    std::unordered_map<asio::ip::udp::endpoint, std::chrono::steady_clock::time_point> _clientHeartbeats; /**< Client heartbeat timestamps. */
    std::unordered_map<uint32_t, int> _lastBroadcastedScore; /**< Last broadcasted score values. */
    mutable std::mutex _scoreMutex; /**< Mutex for score updates. */
};

/// @brief Parses a raw data vector into a ParsedMessage.
/// @param data The raw data.
/// @return std::optional<ParsedMessage> The parsed message, or nullopt if invalid.
std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);

/// @brief Builds a message from a type and payload.
/// @param type The message type.
/// @param payload The message payload.
/// @return std::vector<uint8_t> The complete message.
std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);

/// @brief Builds the payload for an entity update/spawn message.
/// @param entity Pointer to the entity.
/// @return std::vector<uint8_t> The payload data.
std::vector<uint8_t> buildEntityPayload(Entity* entity);

/// @brief Builds the payload for a destroy entity message.
/// @param entity Pointer to the entity.
/// @return std::vector<uint8_t> The payload data.
std::vector<uint8_t> buildDestroyEntityPayload(Entity* entity);

/// @brief Builds the payload for a life update message.
/// @param entity Pointer to the entity.
/// @param life_remaining The remaining life value.
/// @return std::vector<uint8_t> The payload data.
std::vector<uint8_t> buildLifePayload(Entity* entity, uint8_t life_remaining);

/// @brief Builds the payload for a score update message.
/// @param score The score value.
/// @return std::vector<uint8_t> The payload data.
std::vector<uint8_t> buildScorePayload(uint32_t score);

/// @brief Broadcasts a server advertisement (for LAN discovery).
/// @param io_context The ASIO I/O context.
/// @param advertisementPort The port used for advertisement.
/// @param serverPort The server port.
void broadcastServerAdvertisement(asio::io_context& io_context,
                                  unsigned short advertisementPort,
                                  unsigned short serverPort);