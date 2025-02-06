#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "NetworkClient.hpp"
#include "HandleBackground.hpp"
#include "EntityManager.hpp"
#include "HUD.hpp"
#include "MusicHandler.hpp"

class Client {
    public:
        Client();
        void run();
    private:
        void initWindow();
        void processEvents();
        void processEvent(sf::Event& event);
        void processKeyboardPress(sf::Keyboard::Key key);
        void processKeyboardRelease(sf::Keyboard::Key key);
        void processMousePress(const sf::Vector2i& pos);
        void processMouseMove(const sf::Vector2i& pos);
        bool isButtonHovered(const sf::Sprite& sprite, const sf::Vector2i& pos);
        void update(float dt);
        void render();
        void processMessages();
        void updateButtonColors();
        void connectToServer();
        void processSettingsClick(const sf::Vector2i& pos);
        void drawSettings();
        
        sf::RenderWindow _window;
        sf::Clock _clock;
        bool _connected{ false };
        sf::Font _font;
        sf::Text _connectText;
        std::unique_ptr<NetworkClient> _networkClient;
        HandleBackground _background;
        EntityManager _entityManager;
        HUD _hud;
        MusicHandler _music;
        uint32_t _playerID = 0;
        uint32_t _score = 0;
        sf::Sprite _connectSprite;
        bool _hoverConnect{ false };
        sf::Texture _menuTexture;
        sf::Sprite _menuSprite;
        bool _inSettings{ false };
        sf::Sprite _settingsSprite;
        sf::Text _settingsText;
        bool _hoverSettings{ false};
};

#endif // CLIENT_HPP
