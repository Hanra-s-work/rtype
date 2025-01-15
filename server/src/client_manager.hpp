#pragma once
#include <asio.hpp>
#include <unordered_map>
#include <mutex>
#include <cstdint>

/**
 * @struct Client
 * @brief Contains basic-info for each client
 */
struct Client {
    uint32_t id;
    asio::ip::udp::endpoint ep;
    std::string username;
    bool ready = false;
};

/**
 * @class ClientManager
 * @brief Tracks (ip::udp::endpoint)->clientId and allows lookup in reverse.
 */
class ClientManager {
public:
    uint32_t resolveClientID(const asio::ip::udp::endpoint& ep);
    void removeClient(const asio::ip::udp::endpoint& ep);
    Client &getClient(const uint32_t id);
    /**
     * @brief Returns the endpoint for a given clientId if known, 
     *        else a default-constructed endpoint.
     */
    asio::ip::udp::endpoint getEndpointForId(uint32_t clientId);

private:
    std::mutex mutex_;
    std::unordered_map<asio::ip::udp::endpoint, uint32_t> epToId_;
    std::unordered_map<uint32_t, asio::ip::udp::endpoint> idToEp_;
    std::unordered_map<uint32_t, Client> idToClient_;
    uint32_t nextId_ = 1;
};
