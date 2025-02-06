// Client.cpp

#include "Client.hpp"
#include <cstring>
#include "TextureManager.hpp"

Client::Client() : _background(_window), _hud(), _music()
{
    initWindow();
    _background.loadAssets("client/assets/background.jpg", "client/assets/etoiles-lointaines.png");
    _font.loadFromFile("client/assets/font/Arial.ttf");
    _connectButton.setFont(_font);
    _connectButton.setString("Connect");
    _connectButton.setCharacterSize(24);
    _connectButton.setFillColor(sf::Color::White);
    sf::Vector2u winSize = _window.getSize();
    _connectButton.setPosition(winSize.x / 2.f - 50.f, winSize.y / 2.f - 20.f);
    _networkClient = std::make_unique<NetworkClient>();
    _hud.setFont(_font);
}

void Client::initWindow()
{
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();
    _window.create(desktopMode, "R-Type Client", sf::Style::Fullscreen | sf::Style::Titlebar | sf::Style::Close, sf::ContextSettings(0, 0, 0, 2, 1));
}

void Client::run()
{
    while (_window.isOpen()) {
        float dt = _clock.restart().asSeconds();
        handleEvents();
        update(dt);
        render();
    }
}

void Client::handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            _window.close();
        else if (event.type == sf::Event::Resized) {
            sf::Vector2u newSize = _window.getSize();
            _connectButton.setPosition(newSize.x / 2.f - 50.f, newSize.y / 2.f - 20.f);
            _background.resize(newSize);
            sf::FloatRect visibleArea(0, 0, newSize.x, newSize.y);
            _window.setView(sf::View(visibleArea));
        }
        else if (event.type == sf::Event::KeyPressed) {
            if (_connected) {
                if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_UP, {});
                if (event.key.code == sf::Keyboard::S || event.key.code == sf::Keyboard::Down)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_DOWN, {});
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_RIGHT, {});
                if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_LEFT, {});
                if (event.key.code == sf::Keyboard::Space){
                    _networkClient->sendBinaryMessage(MessageType::PLAYER_FIRE, {});
                    _music.playPlayerFire();
                }
            }
        }
        else if (event.type == sf::Event::KeyReleased) {
            if (_connected) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_UP_STOP, {});
                else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_DOWN_STOP, {});
                else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_LEFT_STOP, {});
                else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D)
                    _networkClient->sendBinaryMessage(MessageType::MOVE_RIGHT_STOP, {});
            }
        }
        else if (event.type == sf::Event::MouseButtonPressed) {
            if (!_connected && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                if (isConnectButtonClicked(mousePos))
                    connectToServer();
            }
        }
    }
}

bool Client::isConnectButtonClicked(const sf::Vector2i& mousePos)
{
    return _connectButton.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}

void Client::connectToServer()
{
    _networkClient->connect("127.0.0.1", 9000);
    _networkClient->sendConnectRequest();
}

void Client::update(float dt)
{
    _background.update(dt);
    _entityManager.update(dt);
    auto messages = _networkClient->retrieveMessages();
    for (auto &msg : messages) {
        if (msg.type == MessageType::CONNECT_OK)
            _connected = true;
        else if (msg.type == MessageType::PLAYER_LEFT) {
            std::string whoLeft(msg.payload.begin(), msg.payload.end());
            _hud.showNotification("Player " + whoLeft + " left", sf::Color::Red, {1720.f, 10.f});
        }
        else if (msg.type == MessageType::UPDATE_ENTITY) {
            size_t expectedSize = 1 + sizeof(uint32_t) + 2 * sizeof(float);
            if (msg.payload.size() < expectedSize)
                continue;
            uint8_t rawType = msg.payload[0];
            EntityType entityType = static_cast<EntityType>(rawType);
            size_t offset = 1;
            uint32_t entityId;
            std::memcpy(&entityId, msg.payload.data() + offset, sizeof(entityId));
            offset += sizeof(entityId);
            float posX;
            std::memcpy(&posX, msg.payload.data() + offset, sizeof(posX));
            offset += sizeof(posX);
            float posY;
            std::memcpy(&posY, msg.payload.data() + offset, sizeof(posY));
            _entityManager.updateEntity(entityId, entityType, posX, posY);
            if (entityType == EntityType::Player)
                _playerID = entityId;
            if(entityType == EntityType::Collision)
                _music.playCollision();
            if (entityType == EntityType::Boss)
                _music.playSpawnBoss();
        }
        else if (msg.type == MessageType::DESTROY_ENTITY) {
            size_t expectedSize = sizeof(uint8_t) + sizeof(uint32_t);
            if (msg.payload.size() < expectedSize)
                continue;
            uint32_t entityId;
            std::memcpy(&entityId, msg.payload.data() + sizeof(uint8_t), sizeof(entityId));
            _entityManager.removeEntity(entityId);
        }
        else if (msg.type == MessageType::LIFE) {
            size_t expectedSize = 1 + sizeof(uint32_t) + sizeof(uint32_t);
            if (msg.payload.size() < expectedSize)
                continue;
            uint8_t rawType = msg.payload[0];
            EntityType entityType = static_cast<EntityType>(rawType);
            size_t offset = 1;
            uint32_t entityId;
            std::memcpy(&entityId, msg.payload.data() + offset, sizeof(entityId));
            offset += sizeof(entityId);
            uint32_t life;
            std::memcpy(&life, msg.payload.data() + offset, sizeof(life));
            _entityManager.updateLife(entityId, entityType, life);
            if (entityId == _playerID)
                if(auto player = _entityManager.getSpriteEntity(_playerID))
                    _hud.updatePlayer(_playerID, player->getLife());
        } else if (msg.type == MessageType::SCORE) {
            size_t expectedSize = sizeof(uint32_t);
            if (msg.payload.size() < expectedSize)
                continue;
            std::memcpy(&_score, msg.payload.data(), sizeof(_score));
            _hud.setScore(_score);
        } else if (msg.type == MessageType::DEFEAT){
            _hud.showNotification("Defeat", sf::Color::Red, { _window.getSize().x / 2.f, _window.getSize().y / 2.f });
            _music.playLoose();
        } else if (msg.type == MessageType::WIN){
            _hud.showNotification("Victory", sf::Color::Green, { _window.getSize().x / 2.f, _window.getSize().y / 2.f });
            _music.playWin();
        } 
    }
    static float heartbeatTimer = 0.f;
    heartbeatTimer += dt;
    if (heartbeatTimer >= 5.f) {
        heartbeatTimer = 0.f;
        _networkClient->sendBinaryMessage(MessageType::HEARTBEAT, {});
    }
}

void Client::render()
{
    _window.clear(sf::Color::Blue);
    if (_connected) {
        _background.render(_window);
        _entityManager.render(_window);
        _music.playBackgroundMusic();
        if (_playerID != 0) {
            if (auto player = _entityManager.getSpriteEntity(_playerID))
                _hud.updatePlayer(_playerID, player->getLife());
            _hud.draw(_window);
        }
    }
    else {
        _window.draw(_connectButton);
    }
    _window.display();
}
