//NetworkClient.cpp

#include "NetworkClient.hpp"
#include <iostream>
#include <chrono>

static const unsigned short LOCAL_PORT = 0; // 0 means OS will pick an available port

NetworkClient::NetworkClient()
{
    // Nothing yet
}

NetworkClient::~NetworkClient()
{
    disconnect();
}

void NetworkClient::connect(const std::string& serverIp, unsigned short serverPort)
{
    if (_running) return; // Already running

    _running = true;

    _socket = std::make_unique<asio::ip::udp::socket>(_ioContext,
        asio::ip::udp::endpoint(asio::ip::udp::v4(), LOCAL_PORT));

    // Store server endpoint
    _serverEndpoint = asio::ip::udp::endpoint(asio::ip::make_address(serverIp), serverPort);

    // Start receiving
    doReceive();

    // Start I/O threads
    const size_t THREAD_COUNT = 1;
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        _ioThreads.emplace_back([this]() {
            try {
                _ioContext.run();
            } catch (std::exception &e) {
                std::cerr << "Asio error: " << e.what() << "\n";
            }
        });
    }
}

// NetworkClient.cpp

void NetworkClient::disconnect()
{
    if (!_running) return;

    // 1. Gracefully notify the server
    sendBinaryMessage(MessageType::DISCONNECT, {});

    // 2. Then proceed with your existing disconnect logic
    _running = false;

    if (_socket) {
        asio::error_code ec;
        _socket->close(ec);
    }
    _ioContext.stop();

    for (auto &t : _ioThreads) {
        if (t.joinable()) {
            t.join();
        }
    }
    _ioThreads.clear();

    std::cout << "[NetworkClient] Disconnected.\n";
}


void NetworkClient::doReceive()
{
    auto buffer = std::make_shared<std::array<char, 1024>>();
    auto sender = std::make_shared<asio::ip::udp::endpoint>();

    _socket->async_receive_from(
        asio::buffer(*buffer), *sender,
        [this, buffer, sender](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                std::string data(buffer->data(), bytes_recvd);
                onDataReceived(data, *sender);
            }

            if (_running) {
                doReceive();
            }
        }
    );
}

void NetworkClient::onDataReceived(const std::string& dataStr,
                                   const asio::ip::udp::endpoint& senderEndpoint)
{
    // Convert std::string -> vector<uint8_t>
    std::vector<uint8_t> data(dataStr.begin(), dataStr.end());

    auto msgOpt = parseMessage(data);
    if (!msgOpt.has_value()) {
        // incomplete or invalid message
        return;
    }
    ParsedMessage msg = msgOpt.value();

    // You can store it in _incomingMessages as a structured message
    {
        std::lock_guard<std::mutex> lock(_messageMutex);
        _incomingMessages.push_back(msg);
    }
}

void NetworkClient::sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload)
{
    if (!_running) return;

    std::vector<uint8_t> msg = buildMessage(type, payload);
    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));

    _socket->async_send_to(
        asio::buffer(*buffer), _serverEndpoint,
        [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
            // data is kept alive until this lambda finishes
        }
    );
}

std::vector<ParsedMessage> NetworkClient::retrieveMessages()
{
    // Lock the mutex so we don't race with onDataReceived()
    std::lock_guard<std::mutex> lock(_messageMutex);

    // Move _incomingMessages into a temporary vector
    // so we can clear it in one step
    std::vector<ParsedMessage> result = std::move(_incomingMessages);

    // Now _incomingMessages is empty, so the next call to retrieveMessages()
    // won't return duplicates.
    _incomingMessages.clear();

    return result;
}

void NetworkClient::sendConnectRequest()
{
    if (!_running) return;

    std::vector<uint8_t> emptyPayload; // We don't need any data in the CONNECT request
    std::vector<uint8_t> msg = buildMessage(MessageType::CONNECT, emptyPayload);

    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));
    _socket->async_send_to(
        asio::buffer(*buffer),
        _serverEndpoint,
        [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
            // On completion
        }
    );
}