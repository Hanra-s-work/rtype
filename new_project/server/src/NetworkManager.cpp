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
            info.entityId = entityId;

            // Add the player entity to the world
            _gameWorld.addEntity(std::move(playerEntity));

            // 4) Store info in _connectedPlayers map
            _connectedPlayers[senderEndpoint] = info;

            // Check and add to _clients vector if not already there
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

            // 6) Send CONNECT_OK with the new player ID (existing behavior)
            std::vector<uint8_t> payload(sizeof(uint32_t));
            std::memcpy(payload.data(), &newId, sizeof(uint32_t));
            sendBinaryMessage(MessageType::CONNECT_OK, payload, senderEndpoint);

            // 7) Now, send SPAWN_ENTITY messages:
            //    a) For every existing entity in the GameWorld, send SPAWN_ENTITY to the new client.
            {
                // We can get a snapshot of entities from GameWorld:
                auto entitiesSnapshot = _gameWorld.getEntitiesSnapshot();
                for (Entity* entity : entitiesSnapshot) {
                    sendEntitySpawnMessage(entity, senderEndpoint);
                }
            }

            //    b) Broadcast a SPAWN_ENTITY for the new client's player entity to every other client.
            Entity* newPlayerEntity = _gameWorld.getEntityById(info.entityId);
            for (const auto &ep : _clients) {
                if (ep != senderEndpoint) {
                    sendEntitySpawnMessage(newPlayerEntity, ep);
                }
            }

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

std::vector<uint8_t> buildEntityPayload(Entity* entity) {
    std::vector<uint8_t> payload;
    // 1 byte for entity_type, 4 for entity_id, 4 for posX, 4 for posY = 13 bytes total
    payload.reserve(1 + sizeof(uint32_t) + sizeof(float) + sizeof(float));

    // Entity type as uint8_t:
    uint8_t etype = static_cast<uint8_t>(entity->getType());
    payload.push_back(etype);

    // Entity id as uint32_t:
    uint32_t eid = entity->getId();
    uint8_t* idPtr = reinterpret_cast<uint8_t*>(&eid);
    payload.insert(payload.end(), idPtr, idPtr + sizeof(uint32_t));

    // posX as float:
    float posX = entity->getPosition().x;
    uint8_t* posXPtr = reinterpret_cast<uint8_t*>(&posX);
    payload.insert(payload.end(), posXPtr, posXPtr + sizeof(float));

    // posY as float:
    float posY = entity->getPosition().y;
    uint8_t* posYPtr = reinterpret_cast<uint8_t*>(&posY);
    payload.insert(payload.end(), posYPtr, posYPtr + sizeof(float));

    return payload;
}

void NetworkManager::sendEntitySpawnMessage(Entity* entity, const asio::ip::udp::endpoint& target) {
    if (!entity) return;
    std::vector<uint8_t> payload = buildEntityPayload(entity);
    sendBinaryMessage(MessageType::SPAWN_ENTITY, payload, target);
}

void NetworkManager::sendEntityUpdateMessage(Entity* entity, const asio::ip::udp::endpoint& target) {
    if (!entity) return;
    std::vector<uint8_t> payload = buildEntityPayload(entity);
    sendBinaryMessage(MessageType::UPDATE_ENTITY, payload, target);
}

void NetworkManager::broadcastStateDelta()
{
    // Lock _mutex to protect access to _clients and _lastBroadcastedEntityPositions.
    std::lock_guard<std::mutex> lock(_mutex);

    // Get a snapshot of entities (raw pointers)
    auto entities = _gameWorld.getEntitiesSnapshot(); // returns std::vector<Entity*>

    // Define a threshold (in world units) for considering an update significant.
    const float threshold = 1.0f;

    // For each entity, compare its current position to the last broadcasted position.
    for (Entity* e : entities) {
        if (!e) continue;
        uint32_t id = e->getId();
        Vector2 currentPos = e->getPosition();

        bool shouldUpdate = false;
        // Check if we have broadcasted this entity before.
        auto it = _lastBroadcastedEntityPositions.find(id);
        if (it == _lastBroadcastedEntityPositions.end()) {
            // No previous broadcast—so consider this a new entity.
            shouldUpdate = true;
        } else {
            Vector2 lastPos = it->second;
            float dx = currentPos.x - lastPos.x;
            float dy = currentPos.y - lastPos.y;
            if (std::fabs(dx) >= threshold || std::fabs(dy) >= threshold) {
                shouldUpdate = true;
            }
        }

        if (shouldUpdate) {
            // Update the stored position
            _lastBroadcastedEntityPositions[id] = currentPos;
            // Send an UPDATE_ENTITY message for this entity.
            // (Alternatively, you could choose to send a SPAWN_ENTITY if this is the first time.)
            // For now, we'll send UPDATE_ENTITY.
            // Use your helper function that builds a payload in the desired format.
            // Here is an inline version using the new format:
            uint8_t etype = static_cast<uint8_t>(e->getType());
            uint32_t eid  = id;
            float posX    = currentPos.x;
            float posY    = currentPos.y;

            std::vector<uint8_t> payload;
            payload.reserve(1 + sizeof(uint32_t) + sizeof(float) + sizeof(float));
            // Append entity_type (1 byte)
            payload.push_back(etype);
            // Append entity_id (4 bytes)
            uint8_t* idPtr = reinterpret_cast<uint8_t*>(&eid);
            payload.insert(payload.end(), idPtr, idPtr + sizeof(uint32_t));
            // Append posX (4 bytes)
            uint8_t* xPtr = reinterpret_cast<uint8_t*>(&posX);
            payload.insert(payload.end(), xPtr, xPtr + sizeof(float));
            // Append posY (4 bytes)
            uint8_t* yPtr = reinterpret_cast<uint8_t*>(&posY);
            payload.insert(payload.end(), yPtr, yPtr + sizeof(float));

            // Build the final message using your helper function.
            std::vector<uint8_t> msg = buildMessage(MessageType::UPDATE_ENTITY, payload);

            // Send the message to all connected clients.
            for (const auto &ep : _clients) {
                auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
                _socket->async_send_to(
                    asio::buffer(*buffer), ep,
                    [buffer](std::error_code, std::size_t) {
                        // done
                    }
                );
            }
        } // end if shouldUpdate
    } // end for each entity
}