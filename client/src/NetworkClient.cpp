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
    _socket = std::make_unique<asio::ip::udp::socket>(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), LOCAL_PORT));
    _serverEndpoint = asio::ip::udp::endpoint(asio::ip::make_address(serverIp), serverPort);
    doReceive();
    const size_t THREAD_COUNT = 1;
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        _ioThreads.emplace_back([this]() {
            try {
                _ioContext.run();
            }
            catch (...) {}
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
        [this, buffer, sender](std::error_code ec, std::size_t bytes) {
            if (!ec && bytes > 0) {
                std::string data(buffer->data(), bytes);
                onDataReceived(data, *sender);
            }
            if (_running)
                doReceive();
        }
    );
}

void NetworkClient::onDataReceived(const std::string& data, const asio::ip::udp::endpoint& sender)
{
    std::vector<uint8_t> vec(data.begin(), data.end());
    auto msgOpt = parseMessage(vec);
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
    _socket->async_send_to(asio::buffer(*buffer), _serverEndpoint, [buffer](std::error_code, std::size_t){});
}

std::vector<ParsedMessage> NetworkClient::retrieveMessages()
{
    std::lock_guard<std::mutex> lock(_messageMutex);
    std::vector<ParsedMessage> res = std::move(_incomingMessages);
    _incomingMessages.clear();
    return res;
}

void NetworkClient::sendConnectRequest()
{
    if (!_running)
        return;
    std::vector<uint8_t> msg = buildMessage(MessageType::CONNECT, {});
    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));
    _socket->async_send_to(asio::buffer(*buffer), _serverEndpoint, [buffer](std::error_code, std::size_t){});
}

std::string discoverServer(unsigned short advertisementPort, unsigned int timeoutMs)
{
    try {
        asio::io_context ioContext;
        // Bind to the advertisement port on all interfaces.
        asio::ip::udp::socket socket(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), advertisementPort));
        
        // Optionally, set a timeout on the socket (platform-dependent; here we simply use a blocking receive with a timeout in a separate thread)
        std::array<char, 1024> recvBuffer;
        asio::ip::udp::endpoint senderEndpoint;
        
        // Here we use a simple blocking receive.
        socket.non_blocking(false);
        socket.receive_from(asio::buffer(recvBuffer), senderEndpoint);
        
        // For debugging: print the received message.
        std::string receivedMessage(recvBuffer.data());
        std::cout << "Received advertisement: " << receivedMessage << std::endl;
        
        // Return the sender's IP address.
        return senderEndpoint.address().to_string();
    } catch (std::exception& e) {
        std::cerr << "Error discovering server: " << e.what() << std::endl;
        return "";
    }
}