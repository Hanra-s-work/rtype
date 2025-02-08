#ifndef NETWORKCLIENT_HPP
#define NETWORKCLIENT_HPP

#include <asio.hpp>
#include <thread>
#include <atomic>
#include <vector>
#include <mutex>
#include <string>
#include <iostream>
#include "../../common/NetworkProtocol.hpp"

/**
 * @brief Handles UDP network communication.
 *
 * This class uses Asio for asynchronous networking.
 */
class NetworkClient {
    public:
        NetworkClient();
        ~NetworkClient();
        void connect(const std::string& serverIp, unsigned short serverPort);
        void disconnect();
        void sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload);
        std::vector<ParsedMessage> retrieveMessages();
        void sendConnectRequest();
    private:
        void doReceive();
        void onDataReceived(const std::string& data, const asio::ip::udp::endpoint& sender);
        asio::io_context _ioContext;
        std::unique_ptr<asio::ip::udp::socket> _socket;
        asio::ip::udp::endpoint _serverEndpoint;
        std::vector<std::thread> _ioThreads;
        std::atomic<bool> _running{ false };
        std::mutex _messageMutex;
        std::vector<ParsedMessage> _incomingMessages;
};

std::string discoverServer(unsigned short advertisementPort, unsigned int timeoutMs = 3000);

#endif // NETWORKCLIENT_HPP
