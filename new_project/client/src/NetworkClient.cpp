// NetworkClient.cpp

#include "NetworkClient.hpp"
#include <array>
#include <chrono>

static const unsigned short LOCAL_PORT = 0;

NetworkClient::NetworkClient()
{
}

NetworkClient::~NetworkClient()
{
    disconnect();
}

void NetworkClient::connect(const std::string& serverIp, unsigned short serverPort)
{
    if (_running)
        return;
    _running = true;
    _socket = std::make_unique<asio::ip::udp::socket>(_ioContext,
        asio::ip::udp::endpoint(asio::ip::udp::v4(), LOCAL_PORT));
    _serverEndpoint = asio::ip::udp::endpoint(asio::ip::make_address(serverIp), serverPort);
    doReceive();
    const size_t THREAD_COUNT = 1;
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        _ioThreads.emplace_back([this]() {
            try {
                _ioContext.run();
            }
            catch (std::exception&) {}
        });
    }
}

void NetworkClient::disconnect()
{
    if (!_running)
        return;
    sendBinaryMessage(MessageType::DISCONNECT, {});
    _running = false;
    if (_socket) {
        asio::error_code ec;
        _socket->close(ec);
    }
    _ioContext.stop();
    for (auto &t : _ioThreads)
        if (t.joinable())
            t.join();
    _ioThreads.clear();
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
            if (_running)
                doReceive();
        }
    );
}

void NetworkClient::onDataReceived(const std::string& data, const asio::ip::udp::endpoint& senderEndpoint)
{
    std::vector<uint8_t> dataVec(data.begin(), data.end());
    auto msgOpt = parseMessage(dataVec);
    if (!msgOpt.has_value())
        return;
    ParsedMessage msg = msgOpt.value();
    {
        std::lock_guard<std::mutex> lock(_messageMutex);
        _incomingMessages.push_back(msg);
    }
}

void NetworkClient::sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload)
{
    if (!_running)
        return;
    std::vector<uint8_t> msg = buildMessage(type, payload);
    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));
    _socket->async_send_to(
        asio::buffer(*buffer), _serverEndpoint,
        [buffer](std::error_code, std::size_t) {}
    );
}

std::vector<ParsedMessage> NetworkClient::retrieveMessages()
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    std::vector<ParsedMessage> result = std::move(_incomingMessages);
    _incomingMessages.clear();
    return result;
}

void NetworkClient::sendConnectRequest()
{
    if (!_running)
        return;
    std::vector<uint8_t> emptyPayload;
    std::vector<uint8_t> msg = buildMessage(MessageType::CONNECT, emptyPayload);
    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));
    _socket->async_send_to(
        asio::buffer(*buffer),
        _serverEndpoint,
        [buffer](std::error_code, std::size_t) {}
    );
}
