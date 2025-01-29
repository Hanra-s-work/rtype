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

    // Optionally send a "HELLO" or "JOIN" message
    sendMessage("JOIN");
}

void NetworkClient::disconnect()
{
    if (!_running) return;
    _running = false;

    // Close socket
    if (_socket) {
        asio::error_code ec;
        _socket->close(ec);
    }

    // Stop io_context
    _ioContext.stop();

    // Join threads
    for (auto &t : _ioThreads) {
        if (t.joinable()) t.join();
    }
    _ioThreads.clear();
}

void NetworkClient::pollMessages()
{
    // Here we can safely copy or process any newly received messages
    std::vector<std::string> messagesCopy;
    {
        std::lock_guard<std::mutex> lock(_messageMutex);
        messagesCopy.swap(_incomingMessages);
    }

    // Process them
    for (auto &msg : messagesCopy) {
        std::cout << "[Client] Received: " << msg << "\n";
        // Then update local game state accordingly
    }
}

void NetworkClient::sendMessage(const std::string& msg)
{
    if (!_running) return;

    auto buffer = std::make_shared<std::string>(msg);
    _socket->async_send_to(
        asio::buffer(*buffer),
        _serverEndpoint,
        [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
            // send callback
        }
    );
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

void NetworkClient::onDataReceived(const std::string& data, const asio::ip::udp::endpoint& /*sender*/)
{
    // Lock and push to the incoming message vector
    {
        std::lock_guard<std::mutex> lock(_messageMutex);
        _incomingMessages.push_back(data);
    }
}
