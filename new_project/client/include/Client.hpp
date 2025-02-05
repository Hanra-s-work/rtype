#ifndef CLIENT_HPP
    #define CLIENT_HPP

    #include <SFML/Graphics.hpp>
    #include <SFML/Audio.hpp>
    #include <memory>
    #include "NetworkClient.hpp"
    #include "HandleBackground.hpp"
    #include "EntityManager.hpp"
    #include "HUD.hpp"
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
            uint32_t _playerID = 0;
            sf::Music _backgroundMusic;
    };

#endif // CLIENT_HPP