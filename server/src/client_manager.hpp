#pragma once

#include <asio.hpp>
#include <unordered_map>
#include <mutex>
#include <cstdint>
#include "asio_hash.hpp"

/**
 * ClientManager:
 *   - gives each (ip,port) client a stable uint32_t ID
 *   - can retrieve the endpoint for a given client ID
 */
class ClientManager {
public:
    /**
     * resolveClientID:
     *   - returns the client ID for (ip,port).
     *   - if unknown, creates a new ID.
     */
    uint32_t resolveClientID(const asio::ip::udp::endpoint& ep);

    /**
     * getEndpoint:
     *   - returns the (ip,port) for a known client ID
     */
    asio::ip::udp::endpoint getEndpoint(uint32_t clientId);

private:
    std::mutex mutex_;
    std::unordered_map<asio::ip::udp::endpoint, uint32_t> endpointToId_;
    std::unordered_map<uint32_t, asio::ip::udp::endpoint> idToEndpoint_;
    uint32_t nextClientId_ = 1;
};
