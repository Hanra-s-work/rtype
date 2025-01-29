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
    std::vector<ParsedMessage> messagesCopy;
    {
        std::lock_guard<std::mutex> lock(_messageMutex);
        messagesCopy.swap(_incomingMessages);
    }

    // Process
    for (auto &msg : messagesCopy) {
        switch (msg.type) {
            case MessageType::HELLO:
            {
                std::string payloadStr(msg.payload.begin(), msg.payload.end());
                std::cout << "[Client] Server says: " << payloadStr << "\n";
                break;
            }
            default:
                std::cout << "[Client] Received unknown message type.\n";
                break;
        }
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