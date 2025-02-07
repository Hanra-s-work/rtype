#include "Client.hpp"
#include "TextureManager.hpp"
#include <algorithm>
#include <iostream>
#include <cstring>

Client::Client() : _background(_window), _hud(), _music()
{
    initWindow();
    sf::Vector2u winSize = _window.getSize();
    _background.loadAssets("client/assets/background.jpg", "client/assets/etoiles-lointaines.png");
    _font.loadFromFile("client/assets/font/SuperMarioBros2.ttf");
    _menuTexture = TextureManager::getTexture("client/assets/menu_wallpaper.jpg");
    _menuSprite.setTexture(_menuTexture);
    sf::Vector2u texSize = _menuTexture.getSize();
    _menuSprite.setScale(winSize.x / static_cast<float>(texSize.x), winSize.y / static_cast<float>(texSize.y));
    sf::Texture& btnTexture = TextureManager::getTexture("client/assets/button.png");
    _connectSprite.setTexture(btnTexture);
    _connectSprite.setOrigin(btnTexture.getSize().x / 2.f, btnTexture.getSize().y / 2.f);
    _connectSprite.setPosition(winSize.x / 2.f, winSize.y / 2.f);
    _connectText.setFont(_font);
    _connectText.setString("CONNECT");
    _connectText.setCharacterSize(24);
    sf::FloatRect textBounds = _connectText.getLocalBounds();
    _connectText.setOrigin(textBounds.width / 2.f, textBounds.height / 2.f);
    _connectText.setFillColor(sf::Color::White);
    _connectText.setPosition(winSize.x / 2.f, (winSize.y / 2.f) - 5.f);
    _networkClient = std::make_unique<NetworkClient>();
    _hud.setFont(_font);
    sf::Texture& settingsTexture = TextureManager::getTexture("client/assets/button.png");
    _settingsSprite.setTexture(settingsTexture);
    _settingsSprite.setOrigin(settingsTexture.getSize().x / 2.f, settingsTexture.getSize().y / 2.f);
    _settingsSprite.setPosition(winSize.x / 2.f, (winSize.y / 2.f) - 100.f);
    _settingsText.setFont(_font);
    _settingsText.setString("SETTINGS");
    _settingsText.setCharacterSize(24);
    sf::FloatRect settingsBounds = _settingsText.getLocalBounds();
    _settingsText.setOrigin(settingsBounds.width / 2.f, settingsBounds.height / 2.f);
    _settingsText.setFillColor(sf::Color::White);
    _settingsText.setPosition(winSize.x / 2.f, (winSize.y / 2.f) - 100.f);
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
        processEvents();
        update(dt);
        render();
    }
}

void Client::processEvents()
{
    sf::Event event;
    while (_window.pollEvent(event)) {
        processEvent(event);
    }
}

void Client::processEvent(sf::Event& event)
{
    if (event.type == sf::Event::Closed)
        _window.close();
    else if (event.type == sf::Event::Resized) {
        sf::Vector2u newSize = _window.getSize();
        _background.resize(newSize);
        sf::FloatRect area(0, 0, newSize.x, newSize.y);
        _window.setView(sf::View(area));
    }
    else if (event.type == sf::Event::KeyPressed)
        processKeyboardPress(event.key.code);
    else if (event.type == sf::Event::KeyReleased)
        processKeyboardRelease(event.key.code);
    else if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2i pos(event.mouseButton.x, event.mouseButton.y);
        if (!_connected) {
            if (_inSettings)
                processSettingsClick(pos);
            else
                processMousePress(pos);
        }
    }
    else if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i pos(event.mouseMove.x, event.mouseMove.y);
        processMouseMove(pos);
    }
}

void Client::processKeyboardPress(sf::Keyboard::Key key)
{
    if (_connected) {
        if (key == sf::Keyboard::Z || key == sf::Keyboard::Up)
            _networkClient->sendBinaryMessage(MessageType::MOVE_UP, {});
        if (key == sf::Keyboard::S || key == sf::Keyboard::Down)
            _networkClient->sendBinaryMessage(MessageType::MOVE_DOWN, {});
        if (key == sf::Keyboard::D || key == sf::Keyboard::Right)
            _networkClient->sendBinaryMessage(MessageType::MOVE_RIGHT, {});
        if (key == sf::Keyboard::Q || key == sf::Keyboard::Left)
            _networkClient->sendBinaryMessage(MessageType::MOVE_LEFT, {});
        if (key == sf::Keyboard::Space) {
            _networkClient->sendBinaryMessage(MessageType::PLAYER_FIRE, {});
            _music.playPlayerFire();
        }
    }
}

void Client::processKeyboardRelease(sf::Keyboard::Key key)
{
    if (_connected) {
        if (key == sf::Keyboard::Up || key == sf::Keyboard::Z)
            _networkClient->sendBinaryMessage(MessageType::MOVE_UP_STOP, {});
        if (key == sf::Keyboard::Down || key == sf::Keyboard::S)
            _networkClient->sendBinaryMessage(MessageType::MOVE_DOWN_STOP, {});
        if (key == sf::Keyboard::Left || key == sf::Keyboard::Q)
            _networkClient->sendBinaryMessage(MessageType::MOVE_LEFT_STOP, {});
        if (key == sf::Keyboard::Right || key == sf::Keyboard::D)
            _networkClient->sendBinaryMessage(MessageType::MOVE_RIGHT_STOP, {});
    }
}

void Client::processMousePress(const sf::Vector2i& pos)
{
    if (isButtonHovered(_settingsSprite, pos))
        _inSettings = true;
    else if (isButtonHovered(_connectSprite, pos))
        connectToServer();
}

void Client::processMouseMove(const sf::Vector2i& pos)
{
    _hoverConnect = isButtonHovered(_connectSprite, pos);
    _hoverSettings = isButtonHovered(_settingsSprite, pos);
}

bool Client::isButtonHovered(const sf::Sprite& sprite, const sf::Vector2i& pos)
{
    return sprite.getGlobalBounds().contains(static_cast<float>(pos.x), static_cast<float>(pos.y));
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
    processMessages();
    updateButtonColors();
    static float heartbeat = 0.f;
    heartbeat += dt;
    if (heartbeat >= 5.f) {
        heartbeat = 0.f;
        _networkClient->sendBinaryMessage(MessageType::HEARTBEAT, {});
    }
}

void Client::processMessages()
{
    auto messages = _networkClient->retrieveMessages();
    for (auto &msg : messages) {
        if (msg.type == MessageType::CONNECT_OK)
            _connected = true;
        else if (msg.type == MessageType::PLAYER_LEFT) {
            std::string left(msg.payload.begin(), msg.payload.end());
            _hud.showNotification("Player " + left + " left", sf::Color::Red, {1710.f, 10.f});
        }
        else if (msg.type == MessageType::UPDATE_ENTITY) {
            size_t expected = 1 + sizeof(uint32_t) + 2 * sizeof(float);
            if (msg.payload.size() < expected)
                continue;
            uint8_t raw = msg.payload[0];
            EntityType type = static_cast<EntityType>(raw);
            size_t off = 1;
            uint32_t id;
            std::memcpy(&id, msg.payload.data() + off, sizeof(id));
            off += sizeof(id);
            float posX, posY;
            std::memcpy(&posX, msg.payload.data() + off, sizeof(posX));
            off += sizeof(posX);
            std::memcpy(&posY, msg.payload.data() + off, sizeof(posY));
            _entityManager.updateEntity(id, type, posX, posY);
            if (type == EntityType::Player)
                _playerID = id;
            if (type == EntityType::Collision)
                _music.playCollision();
            if (type == EntityType::Boss)
                _music.playSpawnBoss();
        }
        else if (msg.type == MessageType::DESTROY_ENTITY) {
            size_t expected = sizeof(uint8_t) + sizeof(uint32_t);
            if (msg.payload.size() < expected)
                continue;
            uint32_t id;
            std::memcpy(&id, msg.payload.data() + sizeof(uint8_t), sizeof(id));
            _entityManager.removeEntity(id);
        }
        else if (msg.type == MessageType::LIFE) {
            size_t expected = 1 + sizeof(uint32_t) + sizeof(uint32_t);
            if (msg.payload.size() < expected)
                continue;
            uint8_t raw = msg.payload[0];
            EntityType type = static_cast<EntityType>(raw);
            size_t off = 1;
            uint32_t id;
            std::memcpy(&id, msg.payload.data() + off, sizeof(id));
            off += sizeof(id);
            uint32_t life;
            std::memcpy(&life, msg.payload.data() + off, sizeof(life));
            _entityManager.updateLife(id, type, life);
            if (id == _playerID)
                if (auto player = _entityManager.getSpriteEntity(_playerID))
                    _hud.updatePlayer(_playerID, player->getLife());
        }
        else if (msg.type == MessageType::SCORE) {
            if (msg.payload.size() < sizeof(uint32_t))
                continue;
            std::memcpy(&_score, msg.payload.data(), sizeof(_score));
            std::cout << _score << std::endl;
            _hud.setScore(_score);
        }
        else if (msg.type == MessageType::DEFEAT) {
            _networkClient->disconnect();
            _hud.showNotification("Defeat", sf::Color::Red, { _window.getSize().x / 2.f, _window.getSize().y / 2.f });
            _music.pauseBackgroundMusic();
            _music.playLoose();
        }
        else if (msg.type == MessageType::WIN) {
            _networkClient->disconnect();
            _hud.showNotification("Victory", sf::Color::Green, { _window.getSize().x / 2.f, _window.getSize().y / 2.f });
            _music.pauseBackgroundMusic();
            _music.playWin();
        }
    }
}

void Client::updateButtonColors()
{
    if (!_connected) {
        _connectSprite.setColor(_hoverConnect ? sf::Color(200,200,200) : sf::Color::White);
        _connectText.setFillColor(_hoverConnect ? sf::Color::Yellow : sf::Color::White);
        _settingsSprite.setColor(_hoverSettings ? sf::Color(200,200,200) : sf::Color::White);
        _settingsText.setFillColor(_hoverSettings ? sf::Color::Yellow : sf::Color::White);
    }
}

void Client::processSettingsClick(const sf::Vector2i& pos)
{
    sf::Vector2f mouseF(static_cast<float>(pos.x), static_cast<float>(pos.y));
    sf::FloatRect backRect(50.f, _window.getSize().y - 100.f, 150.f, 50.f);
    if (backRect.contains(mouseF)) {
        _inSettings = false;
        return;
    }
    sf::FloatRect musicMinus(100.f, 190.f, 50.f, 50.f);
    if (musicMinus.contains(mouseF)) {
        float vol = _music.getMusicVolume();
        _music.setMusicVolume(std::max(0.f, vol - 5.f));
        return;
    }
    sf::FloatRect musicPlus(160.f, 190.f, 50.f, 50.f);
    if (musicPlus.contains(mouseF)) {
        float vol = _music.getMusicVolume();
        _music.setMusicVolume(std::min(100.f, vol + 5.f));
        return;
    }
    sf::FloatRect effectsMinus(100.f, 290.f, 50.f, 50.f);
    if (effectsMinus.contains(mouseF)) {
        float vol = _music.getEffectsVolume();
        _music.setEffectsVolume(std::max(0.f, vol - 5.f));
        return;
    }
    sf::FloatRect effectsPlus(160.f, 290.f, 50.f, 50.f);
    if (effectsPlus.contains(mouseF)) {
        float vol = _music.getEffectsVolume();
        _music.setEffectsVolume(std::min(100.f, vol + 5.f));
        return;
    }
}

void Client::drawSettings()
{
    _window.draw(_menuSprite);
    sf::Text title;
    title.setFont(_font);
    title.setString("Menu Audio");
    title.setCharacterSize(32);
    title.setFillColor(sf::Color::White);
    title.setPosition(100.f, 50.f);
    _window.draw(title);
    sf::Text musicText;
    musicText.setFont(_font);
    musicText.setString("Musique: " + std::to_string(static_cast<int>(_music.getMusicVolume())));
    musicText.setCharacterSize(24);
    musicText.setFillColor(sf::Color::White);
    musicText.setPosition(100.f, 150.f);
    _window.draw(musicText);
    sf::RectangleShape musicMinus(sf::Vector2f(50.f,50.f));
    musicMinus.setFillColor(sf::Color::Blue);
    musicMinus.setPosition(100.f,190.f);
    _window.draw(musicMinus);
    sf::Text minus;
    minus.setFont(_font);
    minus.setString("-");
    minus.setCharacterSize(30);
    minus.setFillColor(sf::Color::White);
    minus.setOrigin(minus.getLocalBounds().width/2.f, minus.getLocalBounds().height/2.f);
    minus.setPosition(125.f,215.f);
    _window.draw(minus);
    sf::RectangleShape musicPlus(sf::Vector2f(50.f,50.f));
    musicPlus.setFillColor(sf::Color::Blue);
    musicPlus.setPosition(160.f,190.f);
    _window.draw(musicPlus);
    sf::Text plus;
    plus.setFont(_font);
    plus.setString("+");
    plus.setCharacterSize(30);
    plus.setFillColor(sf::Color::White);
    plus.setOrigin(plus.getLocalBounds().width/2.f, plus.getLocalBounds().height/2.f);
    plus.setPosition(185.f,215.f);
    _window.draw(plus);
    sf::Text effectsText;
    effectsText.setFont(_font);
    effectsText.setString("Effets: " + std::to_string(static_cast<int>(_music.getEffectsVolume())));
    effectsText.setCharacterSize(24);
    effectsText.setFillColor(sf::Color::White);
    effectsText.setPosition(100.f, 250.f);
    _window.draw(effectsText);
    sf::RectangleShape effectsMinus(sf::Vector2f(50.f,50.f));
    effectsMinus.setFillColor(sf::Color::Blue);
    effectsMinus.setPosition(100.f,290.f);
    _window.draw(effectsMinus);
    sf::Text minusEff;
    minusEff.setFont(_font);
    minusEff.setString("-");
    minusEff.setCharacterSize(30);
    minusEff.setFillColor(sf::Color::White);
    minusEff.setOrigin(minusEff.getLocalBounds().width/2.f, minusEff.getLocalBounds().height/2.f);
    minusEff.setPosition(125.f,315.f);
    _window.draw(minusEff);
    sf::RectangleShape effectsPlus(sf::Vector2f(50.f,50.f));
    effectsPlus.setFillColor(sf::Color::Blue);
    effectsPlus.setPosition(160.f,290.f);
    _window.draw(effectsPlus);
    sf::Text plusEff;
    plusEff.setFont(_font);
    plusEff.setString("+");
    plusEff.setCharacterSize(30);
    plusEff.setFillColor(sf::Color::White);
    plusEff.setOrigin(plusEff.getLocalBounds().width/2.f, plusEff.getLocalBounds().height/2.f);
    plusEff.setPosition(185.f,315.f);
    _window.draw(plusEff);
    sf::Text back;
    back.setFont(_font);
    back.setString("Retour");
    back.setCharacterSize(24);
    back.setFillColor(sf::Color::White);
    back.setPosition(50.f, _window.getSize().y - 100.f);
    _window.draw(back);
}

void Client::render()
{
    _window.clear(sf::Color::Black);
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
        if (_inSettings)
            drawSettings();
        else {
            _window.draw(_menuSprite);
            _window.draw(_settingsSprite);
            _window.draw(_settingsText);
            _window.draw(_connectSprite);
            _window.draw(_connectText);
        }
    }
    _window.display();
}
