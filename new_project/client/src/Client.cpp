//Client.cpp

#include "Client.hpp"
#include <iostream>

Client::Client() : _background(_window)
{
    initWindow();

    if (!_background.loadAssets("client/assets/background.jpg", "client/assets/etoiles-lointaines.png")) {
        std::cerr << "Erreur chargement du background et des étoiles.\n";
    }

    if (!_font.loadFromFile("client/assets/font/Arial.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    if (!_backgroundMusic.openFromFile("client/assets/audio/music.ogg")) {
    std::cerr << "Erreur de chargement de la musique de fond!\n";
    } else {
        _backgroundMusic.setLoop(true);  // Pour que la musique se répète en boucle
        _backgroundMusic.play();           // Démarrage de la musique
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

void Client::update(float dt)
{
    _background.update(dt);
    _entityManager.update(dt);
    
    // Grab new messages
    auto messages = _networkClient->retrieveMessages();
    for (auto &msg : messages) {
        switch (msg.type) {
    case MessageType::CONNECT_OK:
    {
        _connected = true;
        break;
    }
    case MessageType::PLAYER_LEFT:
        {
            // Convertir le payload en chaîne de caractères (nom ou id du joueur)
            std::string whoLeft(msg.payload.begin(), msg.payload.end());
            std::cout << "[Client] Player " << whoLeft << " left the game!\n";

            // Mise à jour du texte
            _playerLeftText.setFont(_font);
            _playerLeftText.setString("Player " + whoLeft + " left the game!");
            _playerLeftText.setCharacterSize(24);
            _playerLeftText.setFillColor(sf::Color::Red);

            // Positionner le texte en haut à droite
            float margin = 10.f;
            sf::FloatRect textBounds = _playerLeftText.getLocalBounds();
            _playerLeftText.setOrigin(textBounds.left, textBounds.top); // origine par défaut
            _playerLeftText.setPosition(static_cast<float>(_window.getSize().x) - textBounds.width - margin, margin);

            // Activer l'affichage (et réinitialiser le timer d'affichage si vous souhaitez un affichage temporaire)
            _displayPlayerLeft = true;
            _playerLeftClock.restart();
            break;
        }
        case MessageType::SPAWN_ENTITY: // Remplacez SPAWN_MONSTER par SPAWN_ENTITY
        {
            // Payload attendue : [entity_type (uint8_t), entity_id (uint32_t), posX (float), posY (float)]
            const size_t expectedSize = sizeof(uint8_t) + sizeof(uint32_t) + 2 * sizeof(float);
            if (msg.payload.size() < expectedSize) {
                std::cerr << "[Client] SPAWN_ENTITY payload trop petit!\n";
                break;
            }

            uint8_t rawType = msg.payload[0];
            EntityType entityType = static_cast<EntityType>(rawType);

            uint32_t entityId;
            std::memcpy(&entityId, msg.payload.data() + 1, sizeof(entityId));

            float posX;
            std::memcpy(&posX, msg.payload.data() + 1 + sizeof(entityId), sizeof(posX));

            float posY;
            std::memcpy(&posY, msg.payload.data() + 1 + sizeof(entityId) + sizeof(posX), sizeof(posY));

            // std::cout << "le player id : " << entityId << " de type :" << static_cast<int>(entityType) << "a spawn" << std::endl;
            // Utiliser EntityManager pour créer/mettre à jour l'entité
            _entityManager.updateEntity(entityId, entityType, posX, posY);
            if (entityType == EntityType::Player) {
                _playerID = entityId;
            }
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
        case MessageType::DESTROY_ENTITY:
        {
            // Payload attendu : [entity_type (uint8_t), entity_id (uint32_t)]
            const size_t expectedSize = sizeof(uint8_t) + sizeof(uint32_t);
            if (msg.payload.size() < expectedSize) {
                std::cerr << "[Client] DESTROY_ENTITY payload trop petit!\n";
                break;
            }
            
            // Lecture du type (bien que pour la suppression seul l'ID soit nécessaire)
            uint8_t rawType = msg.payload[0];
            EntityType entityType = static_cast<EntityType>(rawType);
            
            // Lecture de l'ID de l'entité
            uint32_t entityId;
            std::memcpy(&entityId, msg.payload.data() + sizeof(uint8_t), sizeof(entityId));
            
            // Suppression de l'entité via l'EntityManager
            _entityManager.removeEntity(entityId);
            
            // Optionnel : afficher un message pour le debug
            std::cout << "[Client] Entity " << entityId << " (type " 
                        << static_cast<int>(entityType) << ") supprimée.\n";
            break;
        }
        case MessageType::LIFE:
        {
            // Payload attendue : [entity_type (uint8_t), entity_id (uint32_t), number_remaining (uint32_t)]
            const size_t expectedSize = 1 + sizeof(uint32_t) + sizeof(uint32_t);
            if (msg.payload.size() < expectedSize) {
                std::cerr << "[Client] LIFE payload trop petit!\n";
                break;
            }
            
            uint8_t rawType = msg.payload[0];
            EntityType entityType = static_cast<EntityType>(rawType);
            size_t offset = 1;
            
            uint32_t entityId;
            std::memcpy(&entityId, msg.payload.data() + offset, sizeof(entityId));
            offset += sizeof(entityId);
            
            uint32_t life;
            std::memcpy(&life, msg.payload.data() + offset, sizeof(life));
            
            // Mise à jour de la vie via l'EntityManager
            _entityManager.updateLife(entityId, entityType, life);

            std::cout <<  "Received from server : LIFE " << "[ " << entityId << " " << static_cast<int>(entityType) << " " << life << " ]" << std::endl;
            
            break;
        }
        case MessageType::DEFEAT:
        {
            // Aucun payload attendu
            _endGameText.setFont(_font);
            _endGameText.setString("Defeat");
            _endGameText.setCharacterSize(48);
            _endGameText.setFillColor(sf::Color::Red);
            sf::FloatRect textBounds = _endGameText.getLocalBounds();
            _endGameText.setOrigin(textBounds.left + textBounds.width/2.f, textBounds.top + textBounds.height/2.f);
            _endGameText.setPosition(_window.getSize().x / 2.f, _window.getSize().y / 2.f);
            _displayEndGame = true;
            break;
        }
        case MessageType::WIN:
        {
            // Aucun payload attendu
            _endGameText.setFont(_font);
            _endGameText.setString("Victory");
            _endGameText.setCharacterSize(48);
            _endGameText.setFillColor(sf::Color::Green);
            sf::FloatRect textBounds = _endGameText.getLocalBounds();
            _endGameText.setOrigin(textBounds.left + textBounds.width/2.f, textBounds.top + textBounds.height/2.f);
            _endGameText.setPosition(_window.getSize().x / 2.f, _window.getSize().y / 2.f);
            _displayEndGame = true;
            break;
        }
        case MessageType::SCORE:
        {
            // Payload attendu : [score (uint32_t)]
            const size_t expectedSize = sizeof(uint32_t);
            if (msg.payload.size() < expectedSize) {
                std::cerr << "[Client] SCORE payload trop petit!\n";
                break;
            }
            uint32_t score;
            std::memcpy(&score, msg.payload.data(), sizeof(score));
            
            _scoreText.setFont(_font);
            _scoreText.setString("Score: " + std::to_string(score));
            _scoreText.setCharacterSize(24);
            _scoreText.setFillColor(sf::Color::White);
            sf::FloatRect textBounds = _scoreText.getLocalBounds();
            _scoreText.setOrigin(textBounds.left + textBounds.width/2.f, textBounds.top + textBounds.height/2.f);
            _scoreText.setPosition(_window.getSize().x / 2.f, _window.getSize().y - textBounds.height - 10.f);
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

void Client::render() {
    _window.clear(sf::Color::Blue);

    if (_connected) {
        _background.render(_window);
        _entityManager.render(_window); // Affichage de la scène de jeu
    }
    else {
        _window.draw(_connectButton);
    }

    // -----------------------------
    // Dessiner le HUD en haut à gauche
    // -----------------------------
    if (_connected && _playerID != 0) {
        // Récupération de l'entité du joueur
        SpriteEntity* playerEntity = _entityManager.getSpriteEntity(_playerID);
        if (playerEntity) {
            // Récupérer le nombre de vies du joueur
            uint32_t life = playerEntity->getLife();

            // Créer un texte pour afficher "player : #<id>"
            sf::Text hudText;
            hudText.setFont(_font);
            hudText.setCharacterSize(20);
            hudText.setFillColor(sf::Color::White);
            hudText.setString("player : #" + std::to_string(_playerID));
            hudText.setPosition(10.f, 10.f);
            _window.draw(hudText);

            // Récupérer le sprite du cœur (à partir du TextureManager)
            sf::Sprite heartSprite;
            heartSprite.setTexture(TextureManager::getTexture("client/assets/heart.png"));
            // Vous pouvez ajuster l'échelle du cœur si besoin (par exemple 0.5 pour réduire la taille)
            heartSprite.setScale(0.5f, 0.5f);

            // Position de départ pour les cœurs, juste après le texte (avec un petit espacement)
            sf::FloatRect textBounds = hudText.getGlobalBounds();
            float startX = textBounds.left + textBounds.width + 10.f;
            float y = textBounds.top;

            // Dessiner autant de cœurs que de vies restantes
            for (uint32_t i = 0; i < life; i++) {
                heartSprite.setPosition(startX + i * (heartSprite.getGlobalBounds().width + 5.f), y);
                _window.draw(heartSprite);
            }
        }
    }
    if (_displayPlayerLeft) {
        _window.draw(_playerLeftText);
    }
    if (_displayEndGame) {
        _window.draw(_endGameText);
    }

    _window.draw(_scoreText);
    
    _window.display();
}
