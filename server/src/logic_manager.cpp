#include "logic_manager.hpp"
#include <iostream>

uint32_t LogicManager::registerLogicInstance(const asio::ip::udp::endpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);

    // If this endpoint is already registered, return the same logicId
    auto it = endpointToLogicId_.find(ep);
    if (it != endpointToLogicId_.end()) {
        return it->second;
    }

    uint32_t logicId = nextLogicId_++;
    LogicInstance inst;
    inst.logicId = logicId;
    inst.endpoint = ep;

    instances_[logicId] = inst;
    endpointToLogicId_[ep] = logicId;

    std::cout << "[LogicManager] Registered logicId=" << logicId 
              << " at " << ep << "\n";
    return logicId;
}

uint32_t LogicManager::assignClientToLogic(uint32_t clientId) {
    std::lock_guard<std::mutex> lock(mutex_);

    // If already assigned, return existing
    auto it = clientToLogic_.find(clientId);
    if (it != clientToLogic_.end()) {
        return it->second;
    }

    // Find an instance with <4 clients
    for (auto &pair : instances_) {
        auto &inst = pair.second;
        if (inst.clients.size() < 4) {
            inst.clients.push_back(clientId);
            clientToLogic_[clientId] = inst.logicId;
            std::cout << "[LogicManager] Assigned clientId=" << clientId 
                      << " to logicId=" << inst.logicId << "\n";
            return inst.logicId;
        }
    }
    // No available instance
    std::cout << "[LogicManager] No available logic for client=" << clientId << "\n";
    return 0;
}

uint32_t LogicManager::getLogicIdForClient(uint32_t clientId) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = clientToLogic_.find(clientId);
    if (it != clientToLogic_.end()) {
        return it->second;
    }
    return 0;
}

asio::ip::udp::endpoint LogicManager::getLogicEndpointForClient(uint32_t clientId) {
    std::lock_guard<std::mutex> lock(mutex_);
    auto it = clientToLogic_.find(clientId);
    if (it != clientToLogic_.end()) {
        uint32_t logicId = it->second;
        auto instIt = instances_.find(logicId);
        if (instIt != instances_.end()) {
            return instIt->second.endpoint;
        }
    }
    // Not found or not assigned
    return asio::ip::udp::endpoint();
}

std::vector<uint32_t> LogicManager::getClientsForLogicEndpoint(const asio::ip::udp::endpoint& ep) {
    std::lock_guard<std::mutex> lock(mutex_);
    std::vector<uint32_t> result;
    auto it = endpointToLogicId_.find(ep);
    if (it == endpointToLogicId_.end()) {
        return result; // empty
    }
    uint32_t logicId = it->second;
    auto instIt = instances_.find(logicId);
    if (instIt != instances_.end()) {
        result = instIt->second.clients; // copy vector
    }
    return result;
}
