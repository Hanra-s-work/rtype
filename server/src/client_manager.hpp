#pragma once
#include <asio.hpp>
#include <unordered_map>
#include <mutex>
#include <cstdint>

/**
 * @class ClientManager
 * @brief Tracks (ip::udp::endpoint)->clientId for consistent identification of clients.
 */
class ClientManager {
public:
    /**
     * @brief Resolves or creates a clientId for a given remote endpoint.
     * @param ep The client's (IP,port) endpoint.
     * @return The clientId assigned to that endpoint.
     */
    uint32_t resolveClientID(const asio::ip::udp::endpoint& ep);

    /**
     * @brief Removes a client from the manager by endpoint.
     * @param ep The endpoint to remove.
     */
    void removeClient(const asio::ip::udp::endpoint& ep);

private:
    std::mutex mutex_; ///< Protects the maps below
    std::unordered_map<asio::ip::udp::endpoint, uint32_t> epToId_;
    std::unordered_map<uint32_t, asio::ip::udp::endpoint> idToEp_;
    uint32_t nextId_ = 1;
};
