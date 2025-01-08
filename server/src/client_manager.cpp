#include "client_manager.hpp"

/**
 * @file client_manager.cpp
 * @brief Implementation of ClientManager methods.
 */

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
