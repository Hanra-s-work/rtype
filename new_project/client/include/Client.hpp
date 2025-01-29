#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "NetworkClient.hpp"
#include "ParallaxBackground.hpp"

class Client {
public:
    Client();
    ~Client() = default;

    void run();

private:
    void initWindow();

    void handleEvents();

    void update(float dt);

    void render();

    bool isConnectButtonClicked(const sf::Vector2i& mousePos);

    void connectToServer();

private:
    sf::RenderWindow _window;

    sf::Clock _clock;

    bool _connected { false };

    sf::Font _font;
    sf::Text _connectButton;

    ParallaxBackground _parallaxBackground;

    std::unique_ptr<NetworkClient> _networkClient;
};
