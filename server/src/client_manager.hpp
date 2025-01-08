#pragma once
#include <asio.hpp>
#include <unordered_map>
#include <mutex>
#include <cstdint>

/**
 * @class ClientManager
 * @brief Tracks the mapping between (ip::udp::endpoint) and a unique client ID (uint32_t).
 *
 * This allows the server to consistently identify a client by an ID number,
 * even if it only knows the client’s (IP,port).
 */
class ClientManager {
public:
    /**
     * @brief Resolves or creates a client ID for a given remote endpoint.
     * @param ep The remote endpoint (IP + port).
     * @return The unique client ID associated with that endpoint.
     */
    uint32_t resolveClientID(const asio::ip::udp::endpoint& ep);

    /**
     * @brief Removes a client from the manager if it exists.
     * @param ep The remote endpoint to remove.
     */
    void removeClient(const asio::ip::udp::endpoint& ep);

private:
    std::mutex mutex_; ///< Protects access to the maps below.

    /// Maps endpoint -> assigned client ID.
    std::unordered_map<asio::ip::udp::endpoint, uint32_t> epToId_;

    /// Maps client ID -> endpoint (if needed).
    std::unordered_map<uint32_t, asio::ip::udp::endpoint> idToEp_;

    uint32_t nextId_ = 1; ///< Next ID to assign for a new client.
};
