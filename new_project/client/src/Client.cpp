#include "Client.hpp"
#include <iostream>

Client::Client()
{
    initWindow();

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

            sf::FloatRect visibleArea(0, 0, newSize.x, newSize.y);
            _window.setView(sf::View(visibleArea));
            
            if (_parallaxBackground) {
                _parallaxBackground->loadTextures({"client/assets/rougevif.jpg"}, _window);
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
    // Grab new messages
    auto messages = _networkClient->retrieveMessages();
    for (auto &msg : messages) {
        switch (msg.type) {
            case MessageType::CONNECT_OK:
                std::cout << "[Client] CONNECT_OK received!\n";
                _connected = true;
                // Charger le background parallaxe après la connexion
                _parallaxBackground = std::make_unique<ParallaxBackground>();
                _parallaxBackground->loadTextures({
                    "client/assets/rougevif.jpg"
                }, _window);
                break;
            case MessageType::PLAYER_LEFT:
            {
                // Convert payload back to string
                std::string whoLeft(msg.payload.begin(), msg.payload.end());
                std::cout << "[Client] Player " << whoLeft << " left the game!\n";

                // E.g. remove them from the local entity list, scoreboard, etc.
                break;
            }
            // Possibly handle other messages
            default:
                std::cout << "[Client] Unknown message type.\n";
                break;
        }
    }
    if (_connected && _parallaxBackground){
        _parallaxBackground->update(dt, _window);
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

    if (_connected && _parallaxBackground) {
        _parallaxBackground->render(_window);
    }

     sf::RectangleShape testRect(sf::Vector2f(100, 100));
    testRect.setFillColor(sf::Color::Red);
    testRect.setPosition(50, 50);
    _window.draw(testRect);

    if (!_connected) {
        _window.draw(_connectButton);
    }

    _window.display();
}

