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
            if (!knownClient)
                _clients.push_back(senderEndpoint);
            _clientHeartbeats[senderEndpoint] = std::chrono::steady_clock::now();

            // Now send back CONNECT_OK
            std::vector<uint8_t> emptyPayload; // No extra data needed
            sendBinaryMessage(MessageType::CONNECT_OK, emptyPayload, senderEndpoint);
            break;
        }
        case MessageType::DISCONNECT:
        {
            std::cout << "[Server] DISCONNECT from " << senderEndpoint << "\n";

            // 1. Remove this client from your list
            auto it = std::find(_clients.begin(), _clients.end(), senderEndpoint);
            if (it != _clients.end()) {
                _clients.erase(it);
                std::cout << "[Server] Removed client " << senderEndpoint << "\n";
            }
            broadcastPlayerLeft(senderEndpoint);

            // 2. Optionally notify other clients that this client left
            // e.g. broadcast a "player left" message, etc.

            break;
        }
        case MessageType::HEARTBEAT:
        {
            // Just update the client's last heartbeat time
            _clientHeartbeats[senderEndpoint] = std::chrono::steady_clock::now();
            std::cout << "[Server] Received heartbeat from " << senderEndpoint << std::endl;
            break;
        }
        case MessageType::MOVE_UP:
        {
            std::cout << "[Server][MOVE] player has pressed key (UP) 1 time" <<std::endl;
            break;
        }
        case MessageType::MOVE_DOWN:
        {
            std::cout << "[Server][MOVE] player has pressed key (DOWN) 1 time" <<std::endl;
            break;
        }
        case MessageType::MOVE_RIGHT:
        {
            std::cout << "[Server][MOVE] player has pressed key (RIGHT) 1 time" <<std::endl;
            break;
        }
        case MessageType::MOVE_LEFT:
        {
            std::cout << "[Server][MOVE] player has pressed key (LEFT) 1 time" <<std::endl;
            break;
        }
        case MessageType::PLAYER_FIRE:
        {
            std::cout << "[Server][FIRE] player has pressed key (SPACE) 1 time" <<std::endl;
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

void NetworkManager::checkHeartbeats()
{
    auto now = std::chrono::steady_clock::now();
    const auto TIMEOUT = std::chrono::seconds(15); // 15s with no heartbeat = offline

    for (auto it = _clientHeartbeats.begin(); it != _clientHeartbeats.end(); /* no ++ here */)
    {
        auto elapsed = now - it->second;
        if (elapsed > TIMEOUT)
        {
            // Timed out => remove from _clients
            asio::ip::udp::endpoint timedOutClient = it->first;
            std::cout << "[Server] Client timed out: " << timedOutClient << "\n";

            // Remove from _clients vector
            auto vecIt = std::find(_clients.begin(), _clients.end(), timedOutClient);
            if (vecIt != _clients.end()) {
                _clients.erase(vecIt);
            }

            // Notify other clients that this one left
            broadcastPlayerLeft(timedOutClient);

            // Erase from _clientHeartbeats
            it = _clientHeartbeats.erase(it);
        }
        else {
            ++it; // only increment if we didn't erase
        }
    }
}

void NetworkManager::broadcastPlayerLeft(const asio::ip::udp::endpoint& clientEndpoint)
{
    // Optional: store some "player ID" or transform the endpoint into a string
    std::string leftInfo = clientEndpoint.address().to_string() + ":" +
                           std::to_string(clientEndpoint.port());

    // Convert string to bytes
    std::vector<uint8_t> payload(leftInfo.begin(), leftInfo.end());

    // Build the message
    auto msg = buildMessage(MessageType::PLAYER_LEFT, payload);

    // Send to all other clients
    for (auto &ep : _clients)
    {
        if (ep != clientEndpoint) {
            auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
            _socket->async_send_to(
                asio::buffer(*buffer), ep,
                [buffer](std::error_code, std::size_t) {
                    // done
                }
            );
        }
    }
}