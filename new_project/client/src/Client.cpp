#include "Client.hpp"
#include <iostream>

Client::Client()
{
    initWindow();

    // Load a font (placeholder)
    if (!_font.loadFromFile("arial.ttf")) {
        std::cerr << "Error loading font!\n";
    }

    // Setup connect button
    _connectButton.setFont(_font);
    _connectButton.setString("Connect");
    _connectButton.setCharacterSize(24);
    _connectButton.setColor(sf::Color::White);

    // Position the button roughly in the center
    sf::Vector2u winSize = _window.getSize();
    float btnX = winSize.x / 2.f - 50;  // approximate width
    float btnY = winSize.y / 2.f - 20;
    _connectButton.setPosition(btnX, btnY);

    // Create the parallax background
    _parallaxBackground.addLayer("stars_layer1.png", 20.f);
    _parallaxBackground.addLayer("stars_layer2.png", 40.f);

    // Create network client
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
                   sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);

    _window.setPosition(sf::Vector2<int>(posX, posY));
}

void Client::run()
{
    while (_window.isOpen())
    {
        float dt = _clock.restart().asSeconds();

        // 1. Handle input/events
        handleEvents();

        connectToServer();

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
            break;
        case sf::Event::MouseButtonPressed:
            if (!_connected && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos(event.mouseButton.x, event.mouseButton.y);
                if (isConnectButtonClicked(mousePos)) {
                    connectToServer();
                }
            }
            break;
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
    // Attempt to connect
    std::cout << "Connecting to server...\n";
    _networkClient->connect("127.0.0.1", 9000); // Example IP/port
    _connected = true;
    // Example: client sends HELLO with a small string payload
    std::string testStr = "Hello from client";
    std::vector<uint8_t> payload(testStr.begin(), testStr.end());
    _networkClient->sendBinaryMessage(MessageType::HELLO, payload);
}

void Client::update(float dt)
{
    _parallaxBackground.update(dt);

    if (_connected) {
        _networkClient->pollMessages();

        // Based on messages, update any local game state (positions of players, enemies, etc.)
        // For now, we'll just assume we have some data in _networkClient->getEntities() or similar.
    }
}

void Client::render()
{
    _window.clear(sf::Color::Black);

    _parallaxBackground.draw(_window);

    if (!_connected) {
        _window.draw(_connectButton);
    }
    else {
        // Draw game entities, UI, etc.
        // For example:
        //
        // auto& entities = _networkClient->getEntities();
        // for (auto &e : entities) { e.draw(_window); }
        //
        // For now, we’ll omit the actual drawing code.
    }

    _window.display();
}
