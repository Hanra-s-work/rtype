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

void NetworkManager::onDataReceived(const std::string& dataStr,
                                    const asio::ip::udp::endpoint& senderEndpoint)
{
    // Convert to a byte vector
    std::vector<uint8_t> data(dataStr.begin(), dataStr.end());

    // Parse the message
    auto msgOpt = parseMessage(data);
    if (!msgOpt.has_value()) {
        std::cerr << "[Server] Invalid or incomplete message from " << senderEndpoint << "\n";
        return;
    }

    ParsedMessage msg = msgOpt.value();

    switch (msg.type) {
        case MessageType::CONNECT:
        {
            std::cout << "[Server] CONNECT received from " << senderEndpoint << "\n";
            
            // Add the client to your list if not present
            bool knownClient = false;
            for (auto& c : _clients) {
                if (c == senderEndpoint) {
                    knownClient = true;
                    break;
                }
            }
            if (!knownClient) {
                _clients.push_back(senderEndpoint);
            }

            // Now send back CONNECT_OK
            std::vector<uint8_t> emptyPayload; // No extra data needed
            sendBinaryMessage(MessageType::CONNECT_OK, emptyPayload, senderEndpoint);
            break;
        }
        // ... other message types (MOVE, SHOOT, etc.) ...
        
        default:
            std::cout << "[Server] Received unknown message type from " << senderEndpoint << "\n";
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