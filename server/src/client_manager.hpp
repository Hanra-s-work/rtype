#pragma once
#include <asio.hpp>
#include <unordered_map>
#include <mutex>
#include <cstdint>

/**
 * @class ClientManager
 * @brief Tracks (ip::udp::endpoint)->clientId and allows lookup in reverse.
 */
class ClientManager {
public:
    uint32_t resolveClientID(const asio::ip::udp::endpoint& ep);
    void removeClient(const asio::ip::udp::endpoint& ep);

    /**
     * @brief Returns the endpoint for a given clientId if known, 
     *        else a default-constructed endpoint.
     */
    asio::ip::udp::endpoint getEndpointForId(uint32_t clientId);

private:
    std::mutex mutex_;
    std::unordered_map<asio::ip::udp::endpoint, uint32_t> epToId_;
    std::unordered_map<uint32_t, asio::ip::udp::endpoint> idToEp_;
    uint32_t nextId_ = 1;
};
