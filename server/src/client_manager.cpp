#include "client_manager.hpp"

uint32_t ClientManager::resolveClientID(const asio::ip::udp::endpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = endpointToId_.find(ep);
    if (it != endpointToId_.end()) {
        return it->second;
    } else {
        uint32_t newId = nextClientId_++;
        endpointToId_[ep] = newId;
        idToEndpoint_[newId] = ep;
        return newId;
    }
}

asio::ip::udp::endpoint ClientManager::getEndpoint(uint32_t clientId) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = idToEndpoint_.find(clientId);
    if (it != idToEndpoint_.end()) {
        return it->second;
    }
    return asio::ip::udp::endpoint(); // invalid
}
