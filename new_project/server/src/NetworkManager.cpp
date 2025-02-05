//NetworkManager.cpp
#include "NetworkManager.hpp"
#include "GameWorld.hpp"
#include <algorithm>

static const unsigned short SERVER_PORT = 9000;
static const float speed = 200.f; // base speed for movement

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
        if (t.joinable())
            t.join();
    }
    _ioThreads.clear();

    std::cout << "NetworkManager stopped\n";
}

void NetworkManager::doReceive()
{
    auto buffer = std::make_shared<std::array<char, 1024>>();
    auto senderEndpoint = std::make_shared<asio::ip::udp::endpoint>();

    _socket->async_receive_from(
        asio::buffer(*buffer), *senderEndpoint,
        [this, buffer, senderEndpoint](std::error_code ec, std::size_t bytes_recvd) {
            if (!ec && bytes_recvd > 0) {
                std::string dataStr(buffer->data(), bytes_recvd);

                onDataReceived(dataStr, *senderEndpoint);
            }
            if (_running)
                doReceive();
        }
    );
}

void NetworkManager::onDataReceived(const std::string& dataStr, const asio::ip::udp::endpoint& senderEndpoint)
{
    std::vector<uint8_t> data(dataStr.begin(), dataStr.end());

    auto msgOpt = parseMessage(data);
    if (!msgOpt.has_value()) {
        std::cerr << "[Server] Invalid or incomplete message from " << senderEndpoint << std::endl;
        return;
    }

    ParsedMessage msg = msgOpt.value();
    switch (msg.type) {
        case MessageType::CONNECT:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            std::cout << "[Server] CONNECT received from " << senderEndpoint << "\n";

            uint32_t newId = generateEntityId();

            PlayerInfo info;
            info.playerId = newId;
            auto playerEntity = std::make_unique<Player>(newId);
            playerEntity->setPosition({100.f, 300.f});
            uint32_t entityId = playerEntity->getId();
            info.entityId = entityId;
            _gameWorld.addEntity(std::move(playerEntity));

            _connectedPlayers[senderEndpoint] = info;

            bool knownClient = false;
            for (auto& ep : _clients) {
                if (ep == senderEndpoint) {
                    knownClient = true;
                    break;
                }
            }
            if (!knownClient)
                _clients.push_back(senderEndpoint);

            _clientHeartbeats[senderEndpoint] = std::chrono::steady_clock::now();

            std::vector<uint8_t> payload(sizeof(uint32_t));
            std::memcpy(payload.data(), &newId, sizeof(uint32_t));
            sendBinaryMessage(MessageType::CONNECT_OK, payload, senderEndpoint);

            Entity* newPlayerEntity = _gameWorld.getEntityById(info.entityId);
            if (newPlayerEntity) {
                Player* player = dynamic_cast<Player*>(newPlayerEntity);
                if (player) {
                    sendLifeMessage(player, senderEndpoint);
                }
            }

            auto entitiesSnapshot = _gameWorld.getEntitiesSnapshot();
            for (Entity* e : entitiesSnapshot) {
                sendEntitySpawnMessage(e, senderEndpoint);
            }
            for (const auto &ep : _clients) {
                if (ep != senderEndpoint)
                    sendEntitySpawnMessage(newPlayerEntity, ep);
            }
            std::cout << "Connected clients count: " << _clients.size() << std::endl;
            for (const auto& ep : _clients) {
                std::cout << ep << std::endl;
            }
            if (onNewConnection) {
                onNewConnection(senderEndpoint);
            }
            break;
        }
        case MessageType::DISCONNECT:
        {
            std::cout << "[Server] DISCONNECT from " << senderEndpoint << std::endl;

            std::unique_lock<std::mutex> lock(_mutex);

            Entity* entityToDestroy = nullptr;
            auto itInfo = _connectedPlayers.find(senderEndpoint);
            if (itInfo != _connectedPlayers.end()) {
                uint32_t entityId = itInfo->second.entityId;
                entityToDestroy = _gameWorld.getEntityById(entityId);
            }

            auto itClient = std::find(_clients.begin(), _clients.end(), senderEndpoint);
            if (itClient != _clients.end()) {
                _clients.erase(itClient);
                std::cout << "[Server] Removed client " << senderEndpoint << std::endl;
            }

            _connectedPlayers.erase(senderEndpoint);
            _clientHeartbeats.erase(senderEndpoint);

            lock.unlock();

            if (entityToDestroy)
                broadcastEntityDestroy(entityToDestroy);
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
                        vel.y = -speed;
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_UP received from " << senderEndpoint << std::endl;
            break;
        }
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
                        if (vel.y < 0) {
                            vel.y = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_UP_STOP received from " << senderEndpoint << std::endl;
            break;
        }
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
                        vel.y = speed;
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_DOWN received from " << senderEndpoint << std::endl;
            break;
        }
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
                        if (vel.y > 0) {
                            vel.y = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_DOWN_STOP received from " << senderEndpoint << std::endl;
            break;
        }
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
                        vel.x = -speed;
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_LEFT received from " << senderEndpoint << std::endl;
            break;
        }
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
                        if (vel.x < 0) {
                            vel.x = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_LEFT_STOP received from " << senderEndpoint << std::endl;
            break;
        }
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
                        vel.x = speed;
                        player->setVelocity(vel);
                    }
                }
            }
            std::cout << "[Server] MOVE_RIGHT received from " << senderEndpoint << std::endl;
            break;
        }
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
                        if (vel.x > 0) {
                            vel.x = 0.f;
                            player->setVelocity(vel);
                        }
                    }
                }
            }
            std::cout << "[Server] MOVE_RIGHT_STOP received from " << senderEndpoint << std::endl;
            break;
        }
        case MessageType::PLAYER_FIRE:
        {
            std::lock_guard<std::mutex> lock(_mutex);
            uint32_t newId = generateEntityId();
            auto it = _connectedPlayers.find(senderEndpoint);
            if (it != _connectedPlayers.end()) {
                uint32_t playerEntityId = it->second.entityId;
                Entity* entity = _gameWorld.getEntityById(playerEntityId);
                if (entity) {
                    Player* player = dynamic_cast<Player*>(entity);
                    if (player) {
                        Vector2 pPos = player->getPosition();
                        auto missile = std::make_unique<Missile>(newId, EntityType::PlayerMissile);
                        // Spawn missile with an offset so it doesn't collide with the player immediately.
                        Vector2 missileStartPos = { pPos.x + 50.f, pPos.y };
                        missile->setPosition(missileStartPos);
                        missile->setVelocity({300.f, 0.f});
                        missile->setOwnerId(playerEntityId);
                        _gameWorld.addEntity(std::move(missile));
                    }
                }
            }
            std::cout << "[Server] PLAYER_FIRE received from " << senderEndpoint << std::endl;
            break;
        }
        default:
            break;
    }
}

void NetworkManager::sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload, const asio::ip::udp::endpoint& target) {
    if (!_running) 
        return;
    std::vector<uint8_t> msg = buildMessage(type, payload);
    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));
    _socket->async_send_to(
        asio::buffer(*buffer), target,
        [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
        }
    );
}

void NetworkManager::sendBinaryMessage(MessageType type, const std::vector<uint8_t>& payload) {
    std::vector<uint8_t> msg = buildMessage(type, payload);
    for (const auto &target : _clients) {
        auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
        _socket->async_send_to(
            asio::buffer(*buffer), target,
            [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
            }
        );
    }
}

void NetworkManager::checkHeartbeats()
{
    auto now = std::chrono::steady_clock::now();
    const auto TIMEOUT = std::chrono::seconds(15);

    std::vector<asio::ip::udp::endpoint> timedOutEndpoints;
    std::vector<Entity*> entitiesToDestroy;

    {
        std::lock_guard<std::mutex> lock(_mutex);

        for (auto it = _clientHeartbeats.begin(); it != _clientHeartbeats.end(); ) {
            auto elapsed = now - it->second;
            if (elapsed > TIMEOUT) {
                timedOutEndpoints.push_back(it->first);

                std::cout << "[Server] Client timed out: " << it->first << std::endl;

                auto itInfo = _connectedPlayers.find(it->first);
                if (itInfo != _connectedPlayers.end()) {
                    uint32_t entityId = itInfo->second.entityId;
                    Entity* entity = _gameWorld.getEntityById(entityId);
                    if (entity)
                        entitiesToDestroy.push_back(entity);
                }
                it = _clientHeartbeats.erase(it);
            } else
                ++it;
        }

        for (const auto &ep : timedOutEndpoints) {
            auto itClient = std::find(_clients.begin(), _clients.end(), ep);
            if (itClient != _clients.end())
                _clients.erase(itClient);
            _connectedPlayers.erase(ep);
        }
    }

    for (const auto &ep : timedOutEndpoints) {
        broadcastPlayerLeft(ep);
    }

    for (Entity* entity : entitiesToDestroy) {
        broadcastEntityDestroy(entity);
    }
}

void NetworkManager::broadcastPlayerLeft(const asio::ip::udp::endpoint& clientEndpoint)
{
    std::lock_guard<std::mutex> lock(_mutex);
    std::string leftInfo = clientEndpoint.address().to_string() + ":" + std::to_string(clientEndpoint.port());

    std::vector<uint8_t> payload(leftInfo.begin(), leftInfo.end());
    auto msg = buildMessage(MessageType::PLAYER_LEFT, payload);

    for (auto &ep : _clients)
    {
        if (ep != clientEndpoint) {
            auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
            _socket->async_send_to(
                asio::buffer(*buffer), ep,
                [buffer](std::error_code, std::size_t) {
            });
        }
    }
}

std::vector<uint8_t> buildEntityPayload(Entity* entity) {
    std::vector<uint8_t> payload;
    payload.reserve(1 + sizeof(uint32_t) + 2 * sizeof(float));

    uint8_t etype = static_cast<uint8_t>(entity->getType());
    uint32_t eid  = entity->getId();
    float posX    = entity->getPosition().x;
    float posY    = entity->getPosition().y;

    payload.push_back(etype);
    uint8_t* idPtr = reinterpret_cast<uint8_t*>(&eid);
    payload.insert(payload.end(), idPtr, idPtr + sizeof(uint32_t));
    uint8_t* posXPtr = reinterpret_cast<uint8_t*>(&posX);
    payload.insert(payload.end(), posXPtr, posXPtr + sizeof(float));
    uint8_t* posYPtr = reinterpret_cast<uint8_t*>(&posY);
    payload.insert(payload.end(), posYPtr, posYPtr + sizeof(float));

    return payload;
}

std::vector<uint8_t> buildDestroyEntityPayload(Entity* entity) {
    std::vector<uint8_t> payload;
    payload.reserve(1 + sizeof(uint32_t));

    uint8_t etype = static_cast<uint8_t>(entity->getType());
    payload.push_back(etype);

    uint32_t eid = entity->getId();
    uint8_t* idPtr = reinterpret_cast<uint8_t*>(&eid);
    payload.insert(payload.end(), idPtr, idPtr + sizeof(uint32_t));

    return payload;
}

void NetworkManager::broadcastEntityDestroy(Entity* entity) {
    if (!entity)
        return;
    std::vector<uint8_t> payload = buildDestroyEntityPayload(entity);

    uint8_t etype = payload[0];
    uint32_t eid = 0;
    std::memcpy(&eid, payload.data() + 1, sizeof(uint32_t));
    std::cout << "Broadcasting DESTROY_ENTITY: type=" << static_cast<int>(etype) << ", id=" << eid << std::endl;

    std::vector<uint8_t> msg = buildMessage(MessageType::DESTROY_ENTITY, payload);

    for (const auto &ep : _clients) {
        auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
        _socket->async_send_to(
            asio::buffer(*buffer), ep,
            [buffer](std::error_code, std::size_t) {
            }
        );
    }
}

void NetworkManager::sendEntitySpawnMessage(Entity* entity, const asio::ip::udp::endpoint& target) {
    if (!entity)
        return;
    std::vector<uint8_t> payload = buildEntityPayload(entity);
    sendBinaryMessage(MessageType::SPAWN_ENTITY, payload, target);
}

void NetworkManager::broadcastEntityUpdate(Entity* entity) {
    if (!entity)
        return;
    std::vector<uint8_t> payload = buildEntityPayload(entity);
    sendBinaryMessage(MessageType::UPDATE_ENTITY, payload);
}

bool NetworkManager::hasClients() const {
    std::lock_guard<std::mutex> lock(_mutex);
    return !_clients.empty();
}

std::vector<uint8_t> buildLifePayload(Player* player) {
    std::vector<uint8_t> payload;
    payload.reserve(1 + sizeof(uint32_t) + sizeof(uint32_t));

    uint8_t etype = static_cast<uint8_t>(player->getType());
    payload.push_back(etype);

    uint32_t eid = player->getId();
    uint8_t* idPtr = reinterpret_cast<uint8_t*>(&eid);
    payload.insert(payload.end(), idPtr, idPtr + sizeof(uint32_t));

    uint32_t life = player->getLife();
    uint8_t* lifePtr = reinterpret_cast<uint8_t*>(&life);
    payload.insert(payload.end(), lifePtr, lifePtr + sizeof(uint32_t));

    return payload;
}

void NetworkManager::sendLifeMessage(Player* player, const asio::ip::udp::endpoint& target) {
    if (!player)
        return;
    std::vector<uint8_t> payload = buildLifePayload(player);
    sendBinaryMessage(MessageType::LIFE, payload, target);
}

bool NetworkManager::shouldSendLifeUpdate(uint32_t entityId, uint32_t currentLife) {
        std::lock_guard<std::mutex> lock(_lifeMutex);
        auto it = _lastBroadcastedLife.find(entityId);
        if (it == _lastBroadcastedLife.end()) {
            _lastBroadcastedLife[entityId] = currentLife;
            return true;
        }
        if (it->second != currentLife) {
            it->second = currentLife;
            return true;
        }
        return false;
}

asio::ip::udp::endpoint NetworkManager::getEndpointForEntity(uint32_t entityId) const {
    std::lock_guard<std::mutex> lock(_mutex);
    for (const auto& pair : _connectedPlayers) {
        if (pair.second.entityId == entityId)
            return pair.first;
    }
    throw std::runtime_error("Endpoint not found for given entityId");
}

std::vector<uint8_t> buildScorePayload(uint32_t score) {
    std::vector<uint8_t> payload;
    payload.reserve(sizeof(uint32_t));
    uint8_t* scorePtr = reinterpret_cast<uint8_t*>(&score);
    payload.insert(payload.end(), scorePtr, scorePtr + sizeof(uint32_t));
    return payload;
}

void NetworkManager::sendScoreMessage(uint32_t score, const asio::ip::udp::endpoint& target) {
    std::vector<uint8_t> payload = buildScorePayload(score);
    std::vector<uint8_t> msg = buildMessage(MessageType::SCORE, payload);
    
    std::cout << "[NetworkManager] Sending SCORE: " << score << " to " << target << "\n";
    
    auto buffer = std::make_shared<std::vector<uint8_t>>(std::move(msg));
    _socket->async_send_to(
        asio::buffer(*buffer), target,
        [buffer](std::error_code /*ec*/, std::size_t /*bytes_sent*/) {
        }
    );
}

bool NetworkManager::shouldSendScoreUpdate(uint32_t entityId, int currentScore) {
    std::lock_guard<std::mutex> lock(_scoreMutex);
    auto it = _lastBroadcastedScore.find(entityId);
    if (it == _lastBroadcastedScore.end()) {
        _lastBroadcastedScore[entityId] = currentScore;
        return true;
    }
    if (it->second != currentScore) {
        it->second = currentScore;
        return true;
    }
    return false;
}

void NetworkManager::broadcastEntityDestroy(uint8_t type, uint32_t id) {
    // Build the payload: [entity_type (1 byte), entity_id (4 bytes)]
    std::vector<uint8_t> payload;
    payload.reserve(1 + sizeof(uint32_t));
    payload.push_back(type);
    uint8_t* idPtr = reinterpret_cast<uint8_t*>(&id);
    payload.insert(payload.end(), idPtr, idPtr + sizeof(uint32_t));
    
    std::vector<uint8_t> msg = buildMessage(MessageType::DESTROY_ENTITY, payload);
    std::cout << "Broadcasting DESTROY_ENTITY: type=" << static_cast<int>(type)
              << ", id=" << id << std::endl;
    for (const auto &ep : _clients) {
        auto buffer = std::make_shared<std::vector<uint8_t>>(msg);
        _socket->async_send_to(asio::buffer(*buffer), ep,
            [buffer](std::error_code, std::size_t) { });
    }
}