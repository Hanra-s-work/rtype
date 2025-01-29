#pragma once

#include <asio.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <memory>
#include <optional>
#include <iostream>
#include <cstdint>
#include <cstring>
#include "../../common/NetworkProtocol.hpp"


class GameWorld;

class NetworkManager {
    public:
        NetworkManager();
        ~NetworkManager();

        void start();
        void stop();
        
        void pollMessages(GameWorld& gameWorld);
        void broadcastState(const GameWorld& gameWorld);
        void sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload, const asio::ip::udp::endpoint& target);

    private:
        void doReceive();

        void onDataReceived(const std::string& data, const asio::ip::udp::endpoint& senderEndpoint);

        asio::io_context _ioContext;
        std::unique_ptr<asio::ip::udp::socket> _socket;
        std::vector<std::thread> _ioThreads;
        std::atomic<bool> _running { false };

        std::vector<asio::ip::udp::endpoint> _clients;
};

std::optional<ParsedMessage> parseMessage(const std::vector<uint8_t>& data);
std::vector<uint8_t> buildMessage(MessageType type, const std::vector<uint8_t>& payload);