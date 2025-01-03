#pragma once

#include <asio.hpp>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <cstdint>

/**
 * Each logic instance:
 *   - logicId (unique per instance)
 *   - endpoint (where to send messages for that logic)
 *   - clients (up to 4 client IDs assigned)
 */
struct LogicInstance {
    uint32_t logicId;
    asio::ip::udp::endpoint endpoint;
    std::vector<uint32_t> clients; // up to 4
};

/**
 * LogicManager:
 *   - registerLogicInstance(ep): game logic says "I exist"
 *   - assignClientToLogic(clientId): put a new client into a not-full instance
 *   - getLogicIdForClient(clientId): find which logic the client belongs to
 *   - getLogicEndpointForClient(clientId): returns the logic's (ip,port)
 *   - getClientsForLogicEndpoint(ep): which clients belong to that logic
 */
class LogicManager {
public:
    // Called when a new logic instance wants to register
    uint32_t registerLogicInstance(const asio::ip::udp::endpoint& ep);

    // Assign a client to a logic instance that isn't full
    // returns logicId, or 0 if none available
    uint32_t assignClientToLogic(uint32_t clientId);

    // Which logic is a client assigned to?
    uint32_t getLogicIdForClient(uint32_t clientId);

    // Return the logic endpoint for a given client
    asio::ip::udp::endpoint getLogicEndpointForClient(uint32_t clientId);

    // Return all clients assigned to the logic instance with endpoint=ep
    std::vector<uint32_t> getClientsForLogicEndpoint(const asio::ip::udp::endpoint& ep);

private:
    std::mutex mutex_;
    uint32_t nextLogicId_ = 1;

    // logicId -> LogicInstance
    std::unordered_map<uint32_t, LogicInstance> instances_;
    // logic endpoint -> logicId
    std::unordered_map<asio::ip::udp::endpoint, uint32_t> endpointToLogicId_;
    // clientId -> logicId
    std::unordered_map<uint32_t, uint32_t> clientToLogic_;
};
