#include "client_manager.hpp"

uint32_t ClientManager::resolveClientID(const asio::ip::udp::endpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = epToId_.find(ep);
    if (it != epToId_.end()) {
        return it->second;
    } else {
        uint32_t newId = nextId_++;
        epToId_[ep] = newId;
        idToEp_[newId] = ep;
        return newId;
    }
}

void ClientManager::removeClient(const asio::ip::udp::endpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = epToId_.find(ep);
    if (it != epToId_.end()) {
        uint32_t cid = it->second;
        epToId_.erase(it);
        idToEp_.erase(cid);
    }
}

asio::ip::udp::endpoint ClientManager::getEndpointForId(uint32_t clientId) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = idToEp_.find(clientId);
    if (it != idToEp_.end()) {
        return it->second;
    }
    return asio::ip::udp::endpoint(); // invalid
}
