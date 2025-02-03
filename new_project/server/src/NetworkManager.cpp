#include "NetworkManager.hpp"
#include "GameWorld.hpp"
#include <algorithm>   // for std::find

static const unsigned short SERVER_PORT = 9000;
static const float speed = 200.f; // base speed for movement

// Constructor: store a reference to the game world
NetworkManager::NetworkManager(GameWorld& world)
: _gameWorld(world)
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

    // Bind the UDP socket
    _socket = std::make_unique<asio::ip::udp::socket>(
                  _ioContext,
                  asio::ip::udp::endpoint(asio::ip::udp::v4(), SERVER_PORT));

    // Start receiving packets
    doReceive();

    // Launch a couple of I/O threads
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

// Currently empty, but you could store incoming messages in a queue
// and process them here if you wanted a "polling" approach
void NetworkManager::pollMessages()
{
    // For now, we do everything asynchronously in onDataReceived()
}

// Also empty: you'd fill this in if you want to broadcast positions, etc.
// from your game world to clients each frame or periodically
void NetworkManager::broadcastFullState()
{
    std::lock_guard<std::mutex> lock(_mutex);
    // 1. Gather all entities
    const auto& entities = _gameWorld.getEntitiesSnapshot(); // or some accessor
    uint32_t count = static_cast<uint32_t>(entities.size());

    // Build a packet: [ENTITY_COUNT (4 bytes)] then repeated blocks [id, type, x, y]
    std::vector<uint8_t> payload;
    payload.reserve(4 + count * (4 + 4 + 4 + 4)); // 16 bytes per entity
    // Insert the count
    payload.insert(payload.end(),
                   reinterpret_cast<uint8_t*>(&count),
                   reinterpret_cast<uint8_t*>(&count) + 4);

    // For each entity, insert data
    for (auto & e : entities) {
        uint32_t eid   = e->getId();
        uint32_t etype = static_cast<uint32_t>(e->getType());
        float x        = e->getPosition().x;
        float y        = e->getPosition().y;

        // Insert ID
        auto eidPtr = reinterpret_cast<uint8_t*>(&eid);
        payload.insert(payload.end(), eidPtr, eidPtr + 4);

        // Insert type
        auto etypePtr = reinterpret_cast<uint8_t*>(&etype);
        payload.insert(payload.end(), etypePtr, etypePtr + 4);

        // Insert x
        auto xPtr = reinterpret_cast<uint8_t*>(&x);
        payload.insert(payload.end(), xPtr, xPtr + 4);

        // Insert y
        auto yPtr = reinterpret_cast<uint8_t*>(&y);
        payload.insert(payload.end(), yPtr, yPtr + 4);
    }

    // Build final message
    auto msg = buildMessage(MessageType::STATE_UPDATE, payload);

    // 2. Send to all clients
    for (auto & ep : _clients) {
        auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
        _socket->async_send_to(
            asio::buffer(*buffer), ep,
            [buffer](std::error_code, std::size_t) {
                // done
            }
        );
    }
}

void NetworkManager::broadcastEntityState(Entity* e)
{
    std::lock_guard<std::mutex> lock(_mutex);
    if (!e) return;

    // Build a small packet for just this one entity
    // e.g. [1 count], [eid, type, x, y]
    std::vector<uint8_t> payload;
    payload.reserve(4 + 16); // 4 bytes for count=1, plus 16 for data

    uint32_t count = 1;
    payload.insert(payload.end(),
                   reinterpret_cast<uint8_t*>(&count),
                   reinterpret_cast<uint8_t*>(&count) + 4);

    // Now the entity data
    uint32_t eid   = e->getId();
    uint32_t etype = static_cast<uint32_t>(e->getType());
    float x        = e->getPosition().x;
    float y        = e->getPosition().y;

    auto eidPtr = reinterpret_cast<uint8_t*>(&eid);
    payload.insert(payload.end(), eidPtr, eidPtr + 4);

    auto etypePtr = reinterpret_cast<uint8_t*>(&etype);
    payload.insert(payload.end(), etypePtr, etypePtr + 4);

    auto xPtr = reinterpret_cast<uint8_t*>(&x);
    payload.insert(payload.end(), xPtr, xPtr + 4);

    auto yPtr = reinterpret_cast<uint8_t*>(&y);
    payload.insert(payload.end(), yPtr, yPtr + 4);

    // Build final
    auto msg = buildMessage(MessageType::STATE_UPDATE, payload);

    // Send to all
    for (auto & ep : _clients) {
        auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
        _socket->async_send_to(
            asio::buffer(*buffer), ep,
            [buffer](std::error_code, std::size_t) {
                // done
            }
        );
    }
}

void NetworkManager::doReceive()
{
    auto buffer        = std::make_shared<std::array<char, 1024>>();
    auto senderEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    // Start an async receive
    _socket->async_receive_from(
        asio::buffer(*buffer), *senderEndpoint,
        [this, buffer, senderEndpoint](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                // Convert raw data to std::string
                std::string dataStr(buffer->data(), bytes_recvd);

                onDataReceived(dataStr, *senderEndpoint);
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
        std::cerr << "[Server] Invalid or incomplete message from "
                  << senderEndpoint << "\n";
        return;
    }

    ParsedMessage msg = msgOpt.value();
    switch (msg.type) {

        case MessageType::CONNECT:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            std::cout << "[Server] CONNECT received from " << senderEndpoint << "\n";

            // 1) Generate a new player ID
            uint32_t newId = generateEntityId();

            // 2) Create a PlayerInfo struct
            PlayerInfo info;
            info.playerId = newId;

            // 3) Create a new Player entity in the GameWorld
            auto playerEntity = std::make_unique<Player>(newId);
            playerEntity->setPosition({100.f, 300.f}); // example starting pos

            uint32_t entityId = playerEntity->getId(); // typically same as newId
            info.entityId     = entityId;

            // Add the player entity to the world
            _gameWorld.addEntity(std::move(playerEntity));

            // 4) Store info in our _connectedPlayers map
            _connectedPlayers[senderEndpoint] = info;

            // Check if we already have this endpoint in _clients
            bool knownClient = false;
            for (auto& ep : _clients) {
                if (ep == senderEndpoint) {
                    knownClient = true;
                    break;
                }
            }
            if (!knownClient) {
                _clients.push_back(senderEndpoint);
            }

            // 5) Track heartbeat
            _clientHeartbeats[senderEndpoint] = std::chrono::steady_clock::now();

            // 6) Send CONNECT_OK with the new player ID
            std::vector<uint8_t> payload(sizeof(uint32_t));
            std::memcpy(payload.data(), &newId, sizeof(uint32_t));
            sendBinaryMessage(MessageType::CONNECT_OK, payload, senderEndpoint);
            break;
        }

        case MessageType::DISCONNECT:
        {
            std::cout << "[Server] DISCONNECT from " << senderEndpoint << "\n";

            {
                std::unique_lock<std::mutex> lock(_mutex);

                // Remove from _clients vector
                auto it = std::find(_clients.begin(), _clients.end(), senderEndpoint);
                if (it != _clients.end()) {
                    _clients.erase(it);
                    std::cout << "[Server] Removed client " << senderEndpoint << "\n";
                }

                // Remove from _connectedPlayers
                _connectedPlayers.erase(senderEndpoint);

                // At this point, we need to notify others,
                // so release the lock before calling broadcastPlayerLeft:
                lock.unlock();
            }
            
            broadcastPlayerLeft(senderEndpoint);
            break;
        }

        case MessageType::HEARTBEAT:
        {
            _clientHeartbeats[senderEndpoint] = std::chrono::steady_clock::now();
            std::cout << "[Server] Received heartbeat from " << senderEndpoint << std::endl;
            break;
        }
        case MessageType::MOVE_UP:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        vel.y = -speed;   // move up
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_UP received from " << senderEndpoint << "\n";
            break;
        }

        // MOVE_UP_STOP: reset upward velocity (if currently moving upward)
        case MessageType::MOVE_UP_STOP:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        if (vel.y < 0) { // if moving upward
                            vel.y = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_UP_STOP received from " << senderEndpoint << "\n";
            break;
        }

        // MOVE_DOWN_START: set downward velocity (positive Y)
        case MessageType::MOVE_DOWN:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        vel.y = speed;   // move down
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_DOWN received from " << senderEndpoint << "\n";
            break;
        }

        // MOVE_DOWN_STOP: reset downward velocity (if currently moving downward)
        case MessageType::MOVE_DOWN_STOP:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        if (vel.y > 0) { // if moving down
                            vel.y = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_DOWN_STOP received from " << senderEndpoint << "\n";
            break;
        }

        // MOVE_LEFT_START: set leftward velocity (negative X)
        case MessageType::MOVE_LEFT:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        vel.x = -speed;  // move left
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_LEFT received from " << senderEndpoint << "\n";
            break;
        }

        // MOVE_LEFT_STOP: reset leftward velocity (if currently moving left)
        case MessageType::MOVE_LEFT_STOP:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        if (vel.x < 0) { // if moving left
                            vel.x = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_LEFT_STOP received from " << senderEndpoint << "\n";
            break;
        }

        // MOVE_RIGHT_START: set rightward velocity (positive X)
        case MessageType::MOVE_RIGHT:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        vel.x = speed;   // move right
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_RIGHT received from " << senderEndpoint << "\n";
            break;
        }

        // MOVE_RIGHT_STOP: reset rightward velocity (if currently moving right)
        case MessageType::MOVE_RIGHT_STOP:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 vel = player->getVelocity();
                        if (vel.x > 0) { // if moving right
                            vel.x = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_RIGHT_STOP received from " << senderEndpoint << "\n";
            break;
        }
        case MessageType::PLAYER_FIRE:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            uint32_t newId = generateEntityId();
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t entityId = it->second.entityId; // player's entity
                Entity* entity = _gameWorld.getEntityById(entityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        // 1. Get player position
                        Vector2 pPos = player->getPosition();

                        // 2. Create a new missile
                        auto missile = std::make_unique<Missile>(newId);
                        // Place it at player's position
                        missile->setPosition(pPos);

                        // Give it velocity to go straight (e.g. to the right)
                        missile->setVelocity({300.f, 0.f});

                        // 3. Add to the world
                        _gameWorld.addEntity(std::move(missile));
                    }
                }
            }
            std::cout << "[Server] PLAYER_FIRE received from " << senderEndpoint << "\n";
            break;
        }
        default:
            // Unknown or unhandled type
            break;
    }
}

void NetworkManager::sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload, const asio::ip::udp::endpoint& target)
{
    if (!_running) return;

    // Build final packet (type + size + payload)
    std::vector<uint8_t> msg = buildMessage(type, payload);
    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));

    _socket->async_send_to(
        asio::buffer(*buffer), target,
        [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
            // The shared_ptr keeps 'buffer' alive until send completes
        }
    );
}

void NetworkManager::checkHeartbeats()
{
    auto now = std::chrono::steady_clock::now();
    const auto TIMEOUT = std::chrono::seconds(15); // no heartbeat in 15s => timed out

    std::lock_guard<std::mutex> lock(_mutex);

    for (auto it = _clientHeartbeats.begin(); it != _clientHeartbeats.end(); /* no ++ here */)
    {
        auto elapsed = now - it->second;
        if (elapsed > TIMEOUT)
        {
            auto timedOutClient = it->first;
            std::cout << "[Server] Client timed out: " << timedOutClient << "\n";

            // Remove from _clients vector
            auto vecIt = std::find(_clients.begin(), _clients.end(), timedOutClient);
            if (vecIt != _clients.end()) {
                _clients.erase(vecIt);
            }

            // Also remove from connectedPlayers
            _connectedPlayers.erase(timedOutClient);

            // Notify others
            broadcastPlayerLeft(timedOutClient);

            // Erase from _clientHeartbeats
            it = _clientHeartbeats.erase(it);
        }
        else {
            ++it;
        }
    }
}

void NetworkManager::broadcastPlayerLeft(const asio::ip::udp::endpoint& clientEndpoint)
{
    std::lock_guard<std::mutex> lock(_mutex);
    // For example, we encode the address+port in a string
    std::string leftInfo = clientEndpoint.address().to_string() + ":" +
                           std::to_string(clientEndpoint.port());

    std::vector<uint8_t> payload(leftInfo.begin(), leftInfo.end());
    auto msg = buildMessage(MessageType::PLAYER_LEFT, payload);

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
