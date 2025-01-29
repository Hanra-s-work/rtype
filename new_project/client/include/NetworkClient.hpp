#pragma once

#include <asio.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <string>
#include "../../common/NetworkProtocol.hpp"

class NetworkClient {
public:
    NetworkClient();
    ~NetworkClient();

    // Connect to server at given IP/port (UDP)
    void connect(const std::string& serverIp, unsigned short serverPort);

    // Stop network
    void disconnect();

    // Poll messages from server (call every frame in the main thread)
    void pollMessages();

    void sendMessage(const std::string& msg);
    void sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload);

private:
    // Start async receives
    void doReceive();

    // Handle incoming data
    void onDataReceived(const std::string& data, const asio::ip::udp::endpoint& sender);

private:
    asio::io_context _ioContext;
    std::unique_ptr<asio::ip::udp::socket> _socket;

    // Server endpoint
    asio::ip::udp::endpoint _serverEndpoint;

    // Thread(s) for Asio
    std::vector<std::thread> _ioThreads;
    std::atomic<bool> _running { false };

    // For thread-safe incoming messages
    std::mutex _messageMutex;
    std::vector<ParsedMessage> _incomingMessages;
};