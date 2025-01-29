#include "NetworkManager.hpp"
#include "GameWorld.hpp"

static const unsigned short SERVER_PORT = 9000;

NetworkManager::NetworkManager()
{

}

NetworkManager::~NetworkManager()
{
    stop();
}

void NetworkManager::start()
{
    if (_running) return;
    _running = true;

    _socket = std::make_unique<asio::ip::udp::socket>(_ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), SERVER_PORT));

    doReceive();

    const size_t THREAD_COUNT = 2;
    for (size_t i = 0; i < THREAD_COUNT; i++) {
        _ioThreads.emplace_back([this]() {
            try {
                _ioContext.run();
            } catch (std::exception& e) {
                std::cerr << "IOContext thread exception: " << e.what() << std::endl;
            }
        });
    }
    std::cout << "NetworkManager started on port " << SERVER_PORT << "\n";
}

void NetworkManager::stop()
{
    if (!_running) return;
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

    std::cout << "NetworkManager stopped\n";
}

void NetworkManager::pollMessages(GameWorld& gameWorld)
{

}

void NetworkManager::broadcastState(const GameWorld& gameWorld)
{

}

void NetworkManager::doReceive()
{
    auto buffer = std::make_shared<std::array<char, 1024>>();
    auto senderEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    _socket->async_receive_from(
        asio::buffer(*buffer), *senderEndpoint,
        [this, buffer, senderEndpoint](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                std::string data(buffer->data(), bytes_recvd);

                onDataReceived(data, *senderEndpoint);
            }
            if (_running) {
                doReceive();
            }
        }
    );
}

void NetworkManager::onDataReceived(const std::string& dataStr, const asio::ip::udp::endpoint& senderEndpoint)
{
    std::vector<uint8_t> data(dataStr.begin(), dataStr.end());

    auto msgOpt = parseMessage(data);
    if (!msgOpt.has_value()) {
        std::cerr << "Received invalid or incomplete message from " << senderEndpoint << "\n";
        return;
    }

    ParsedMessage msg = msgOpt.value();
    switch (msg.type) {
        case MessageType::HELLO:
        {
            std::cout << "[Server] HELLO received from " << senderEndpoint << "\n";
            // Optionally parse payload
            std::string payloadStr(msg.payload.begin(), msg.payload.end());
            std::cout << "Payload: " << payloadStr << "\n";

            // Reply with HELLO
            std::string serverReply = "Hello from server!";
            std::vector<uint8_t> replyData(serverReply.begin(), serverReply.end());
            sendBinaryMessage(MessageType::HELLO, replyData, senderEndpoint);
            break;
        }
        case MessageType::JOIN:
            std::cout << "[Server] JOIN received\n";
            break;
        case MessageType::MOVE:
            break;
        default:
            std::cout << "[Server] Unknown message type received.\n";
            break;
    }
}

void NetworkManager::sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload, const asio::ip::udp::endpoint& target)
{
    if (!_running) return;

    std::vector<uint8_t> msg = buildMessage(type, payload);

    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));

    _socket->async_send_to(
        asio::buffer(*buffer), target,
        [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
        }
    );
}