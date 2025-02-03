//Client.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <memory>
#include "NetworkClient.hpp"
#include "HandleBackground.hpp"
#include "HandleSprites.hpp"
#include "EntityManager.hpp"

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
    void sendPlayerPosition(uint32_t playerID, float posX, float posY);

private:
    sf::RenderWindow _window;
    sf::Clock _clock;
    bool _connected { false };

    sf::Font _font;
    sf::Text _connectButton;

    std::unique_ptr<NetworkClient> _networkClient;
    HandleBackground _background;
    SpriteEntity _sprites;
    // std::map<uint32_t, std::unique_ptr<SpriteEntity>> _monsters;
    EntityManager _entityManager;
    uint32_t _playerID = 0;
};
