//Client.cpp

#include "Client.hpp"
#include <iostream>

Client::Client() : _background(_window), _sprites("client/assets/vaisseau-spatial.png", 400, 300, false)
{
    initWindow();

    if (!_background.loadAssets("client/assets/background.jpg", "client/assets/etoiles-lointaines.png")) {
        std::cerr << "Erreur chargement du background et des étoiles.\n";
    }

    if (!_font.loadFromFile("client/assets/font/Arial.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    _connectButton.setFont(_font);
    _connectButton.setString("Connect");
    _connectButton.setCharacterSize(24);
    _connectButton.setFillColor(sf::Color::White);

    sf::Vector2u winSize = _window.getSize();
    float btnX = winSize.x / 2.f - 50;
    float btnY = winSize.y / 2.f - 20;
    _connectButton.setPosition(btnX, btnY);

    _networkClient = std::make_unique<NetworkClient>();

    _sprites.setScale(0.2f, 0.2f);
    _sprites.rotate(90.f);
    _sprites.setPosition(100.0f, 250.0f);
}

void Client::initWindow()
{
    // Query desktop video mode
    sf::VideoMode desktopMode = sf::VideoMode::getDesktopMode();

    // Desired window size
    unsigned int width = 800;
    unsigned int height = 600;

    // Calculate a position to center the window
    unsigned int posX = (desktopMode.width / 2) - (width / 2);
    unsigned int posY = (desktopMode.height / 2) - (height / 2);

    // Create a resizable window
    // NOTE: On some OSes, setPosition might need to be called after creation
    _window.create(sf::VideoMode(width, height), "R-Type Client",
                   sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close,
                   sf::ContextSettings(0, 0, 0, 2, 1));
    
    _window.setVerticalSyncEnabled(true);

    _window.setPosition(sf::Vector2<int>(posX, posY));
}

void Client::run()
{
    while (_window.isOpen())
    {
        float dt = _clock.restart().asSeconds();
        // 1. Handle input/events
        handleEvents();

        // 2. Update
        update(dt);

        // 3. Render
        render();
    }
}

void Client::handleEvents()
{
    sf::Event event;
    while (_window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            _window.close();
            break;

        case sf::Event::Resized:
        {
            // Keep the button in the center if you want
            sf::Vector2u newSize = _window.getSize();
            float btnX = newSize.x / 2.f - 50.f;
            float btnY = newSize.y / 2.f - 20.f;
            _connectButton.setPosition(btnX, btnY);
            _background.resize(_window.getSize()); // Adapter le fond
            sf::FloatRect visibleArea(0, 0, newSize.x, newSize.y);
            _window.setView(sf::View(visibleArea));
            
            break;
        }
        case sf::Event::KeyPressed:
        {
            if (_connected) {
                if (event.key.code == sf::Keyboard::Z || event.key.code == sf::Keyboard::Up) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_UP, {});
                }
                if (event.key.code == sf::Keyboard::S|| event.key.code == sf::Keyboard::Down) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_DOWN, {});
                }
                if (event.key.code == sf::Keyboard::D || event.key.code == sf::Keyboard::Right) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_RIGHT, {});
                }
                if (event.key.code == sf::Keyboard::Q || event.key.code == sf::Keyboard::Left) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_LEFT, {});
                }
                if (event.key.code == sf::Keyboard::Space)
                    _networkClient->sendBinaryMessage(MessageType::PLAYER_FIRE, {});
            }
            break;
        }
        case sf::Event::KeyReleased:
        {
            if (_connected) {
                if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Z) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_UP_STOP, {});
                } else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_DOWN_STOP, {});
                } else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::Q) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_LEFT_STOP, {});
                } else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                    _networkClient->sendBinaryMessage(MessageType::MOVE_RIGHT_STOP, {});
                }
            }
            break;
        }
        case sf::Event::MouseButtonPressed:
        {
            if (!_connected && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                if (isConnectButtonClicked(mousePos)) {
                    // Attempt to connect
                    connectToServer();
                }
            }
            break;
        }
        default:
            break;
        }
    }
}

bool Client::isConnectButtonClicked(const sf::Vector2i& mousePos)
{
    sf::FloatRect btnBounds = _connectButton.getGlobalBounds();
    return btnBounds.contains(static_cast<float>(mousePos.x),
                              static_cast<float>(mousePos.y));
}

void Client::connectToServer()
{
    std::cout << "Trying to connect...\n";

    // Start the network client
    _networkClient->connect("127.0.0.1", 9000);

    // Send a CONNECT request once the socket is ready
    _networkClient->sendConnectRequest();
}

void Client::sendPlayerPosition(uint32_t playerID, float posX, float posY)
{
    // Construire la payload binaire [ id (uint32_t), posX (float), posY (float) ]
    std::vector<uint8_t> payload;
    payload.reserve(sizeof(playerID) + sizeof(posX) + sizeof(posY));

    // On insère l'ID
    const uint8_t* idPtr = reinterpret_cast<const uint8_t*>(&playerID);
    payload.insert(payload.end(), idPtr, idPtr + sizeof(playerID));

    // On insère posX
    const uint8_t* xPtr = reinterpret_cast<const uint8_t*>(&posX);
    payload.insert(payload.end(), xPtr, xPtr + sizeof(posX));

    // On insère posY
    const uint8_t* yPtr = reinterpret_cast<const uint8_t*>(&posY);
    payload.insert(payload.end(), yPtr, yPtr + sizeof(posY));

    // Puis on envoie avec notre NetworkClient
    _networkClient->sendBinaryMessage(MessageType::PLAYER_POSITION, payload);
}

void Client::update(float dt)
{
    _background.update(dt);
    _sprites.update(dt);
    _entityManager.update(dt);

    if (_connected) {
        sf::Vector2f playerPos = _sprites.getPosition();
        // sendPlayerPosition(_playerID, playerPos.x, playerPos.y);
    }
    
    // Grab new messages
    auto messages = _networkClient->retrieveMessages();
    for (auto &msg : messages) {
        switch (msg.type) {
    case MessageType::CONNECT_OK:
    {
        _connected = true;
        // Imaginons que le serveur envoie (uint32_t) comme ID en payload :
        if (msg.payload.size() >= sizeof(uint32_t)) {
            uint32_t playerID;
            std::memcpy(&playerID, msg.payload.data(), sizeof(playerID));
            _playerID = playerID;
            std::cout << "[Client] CONNECT_OK received! My ID = " << _playerID << "\n";
        } else {
            std::cout << "[Client] CONNECT_OK received but no ID in payload.\n";
        }
        break;
    }
        case MessageType::PLAYER_LEFT:
        {
            // Convert payload back to string
            std::string whoLeft(msg.payload.begin(), msg.payload.end());
            std::cout << "[Client] Player " << whoLeft << " left the game!\n";

            // E.g. remove them from the local entity list, scoreboard, etc.
            break;
        }
        case MessageType::SPAWN_MONSTER:
        {
            if (msg.payload.size() < sizeof(uint32_t) + 2 * sizeof(float)) {
                std::cerr << "[Client] SPAWN_MONSTER payload too small!\n";
                break;
            }

            uint32_t monsterID;
            std::memcpy(&monsterID, msg.payload.data(), sizeof(monsterID));

            float posX;
            std::memcpy(&posX, msg.payload.data() + sizeof(monsterID), sizeof(posX));

            float posY;
            std::memcpy(&posY, msg.payload.data() + sizeof(monsterID) + sizeof(posX), sizeof(posY));

            std::cout << "[Client] SPAWN_MONSTER -> ID=" << monsterID
                    << " pos=(" << posX << ", " << posY << ")\n";

            // Créez un nouveau SpriteEntity et stockez-le dans la map
            auto monster = std::make_unique<SpriteEntity>("client/assets/alien.png", posX, posY, false);
            monster->setScale(0.2f, 0.2f);

            _monsters[monsterID] = std::move(monster);
            break;
        }
        case MessageType::UPDATE_ENTITY:
        {
            // On s'attend à recevoir : [ entityType (uint8_t), entityId (uint32_t), posX (float), posY (float) ]
            const size_t expectedSize = 1 + sizeof(uint32_t) + 2 * sizeof(float);
            if (msg.payload.size() < expectedSize) {
                std::cerr << "[Client] UPDATE_ENTITY payload trop petit!\n";
                break;
            }
            
            // Extraction de l'EntityType (premier octet)
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
            
            // Mise à jour/création de l'entité via l'EntityManager
            _entityManager.updateEntity(entityId, entityType, posX, posY);
            break;
        }
        // Possibly handle other messages
        default:
            std::cout << "[Client] Unknown message type.\n";
            break;
        }
    }
    static float heartbeatTimer = 0.f;
    heartbeatTimer += dt;
    if (heartbeatTimer >= 5.f) // send heartbeat every 5 seconds
    {
        heartbeatTimer = 0.f;
        _networkClient->sendBinaryMessage(MessageType::HEARTBEAT, {});
    }
}

void Client::render()
{
    _window.clear(sf::Color::Blue);
    if (_connected){
        _background.render(_window);
        _sprites.draw(_window);
        _entityManager.render(_window);

    }
    for (auto &pair : _monsters) {
        pair.second->draw(_window);
    }
    if (!_connected) {
        _window.draw(_connectButton);
    }

    _window.display();
}

