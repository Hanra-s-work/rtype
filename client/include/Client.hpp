#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "NetworkClient.hpp"
#include "HandleBackground.hpp"
#include "EntityManager.hpp"
#include "HUD.hpp"
#include "MusicHandler.hpp"

/**
 * @brief The Client class manages the main application lifecycle.
 *
 * It encapsulates window creation, event handling, game updating, rendering, and server communication.
*/

class Client {
    public:

        /**
         * @brief Constructs a new Client object.
         *
         * Initializes the window, loads resources, and sets up the initial game state.
        */
        Client();

        /**
         * @brief Starts the main game loop.
        */
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
        
        sf::RenderWindow _window;         ///< The game window
        sf::Clock _clock;                 ///< Clock to measure frame time
        bool _connected{ false };         ///< Indicates if the client is connected to the server
        sf::Font _font;                   ///< Font used for displaying text
        sf::Text _connectText;            ///< Text for the connect button
        std::unique_ptr<NetworkClient> _networkClient; ///< Network communication handler
        HandleBackground _background;     ///< Background and star field manager
        EntityManager _entityManager;     ///< Manager for game entities (players, monsters, etc.)
        HUD _hud;                         ///< Heads-up display for game info
        MusicHandler _music;              ///< Music and sound effects handler
        uint32_t _playerID = 0;           ///< Local player identifier
        uint32_t _score = 0;              ///< Player score
        sf::Sprite _connectSprite;        ///< Sprite for the connect button
        bool _hoverConnect{ false };      ///< Indicates if the connect button is hovered
        sf::Texture _menuTexture;         ///< Texture for the menu background
        sf::Sprite _menuSprite;           ///< Sprite for the menu background
        bool _inSettings{ false };        ///< Indicates if the settings menu is displayed
        sf::Sprite _settingsSprite;       ///< Sprite for the settings button
        sf::Text _settingsText;           ///< Text for the settings button
        bool _hoverSettings{ false };     ///< Indicates if the settings button is hovered
};

#endif // CLIENT_HPP
