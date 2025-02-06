#ifndef CLIENT_HPP
    #define CLIENT_HPP

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <memory>
    #include "NetworkClient.hpp"
    #include "HandleBackground.hpp"
    #include "EntityManager.hpp"
    #include "HUD.hpp"
    #include "MusicHandler.hpp"
    #include "iostream"

    class Client {
        public:
            Client();
            void run();
            void initWindow();
            void handleEvents();
            void update(float dt);
            void render();
            bool isConnectButtonClicked(const sf::Vector2i& mousePos);
            void connectToServer();
        private:
            sf::RenderWindow _window;
            sf::Clock _clock;
            bool _connected{ false };
            sf::Font _font;
            sf::Text _connectButton;
            std::unique_ptr<NetworkClient> _networkClient;
            HandleBackground _background;
            EntityManager _entityManager;
            HUD _hud;
            MusicHandler _music;
            uint32_t _playerID = 0;
            // sf::Music _backgroundMusic;
            uint32_t _score;
            sf::Sprite _connectButtonSprite;
            bool _isHoveringConnectButton = false;
            sf::Texture _menuWallpaperTexture;
            sf::Sprite _menuWallpaperSprite;
    };

#endif // CLIENT_HPP