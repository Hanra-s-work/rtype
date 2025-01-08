#pragma once
#include <asio.hpp>
#include <unordered_map>
#include <mutex>
#include <cstdint>

class ClientManager {
public:
    // Return the clientId for an endpoint, or create a new one if none exists
    uint32_t resolveClientID(const asio::ip::udp::endpoint& ep);

    // Remove the client from the map
    void removeClient(const asio::ip::udp::endpoint& ep);

private:
    std::mutex mutex_;
    std::unordered_map<asio::ip::udp::endpoint, uint32_t> epToId_;
    std::unordered_map<uint32_t, asio::ip::udp::endpoint> idToEp_;
    uint32_t nextId_ = 1;
};
