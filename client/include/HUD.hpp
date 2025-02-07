#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @brief Displays the game Heads-Up Display (HUD).
*/
class HUD {
    public:
        /**
         * @brief Constructs a new HUD object.
         *
         * Loads necessary resources for display.
        */
        HUD();
        /**
         * @brief Sets the font used by the HUD.
         * @param font The font to use.
        */
        void setFont(const sf::Font& font);
        /**
         * @brief Updates the player information (ID and life).
         * @param id Player ID.
         * @param life Current life count.
        */
        void updatePlayer(uint32_t id, uint32_t life);
        /**
         * @brief Updates the score display.
         * @param score Current score.
        */
        void setScore(uint32_t score);
        /**
         * @brief Shows a temporary notification on the screen.
         * @param text Notification text.
         * @param color Text color.
         * @param pos Display position.
        */
        void showNotification(const std::string& text, const sf::Color& color, const sf::Vector2f& pos);
        /**
         * @brief Shows a temporary notification on the screen.
         * @param text Notification text.
         * @param color Text color.
         * @param pos Display position.
        */
        void draw(sf::RenderWindow& window);
    private:
        sf::Text _playerInfo;       ///< Player information text
        sf::Text _scoreText;        ///< Score text
        sf::Text _notificationText; ///< Notification text
        sf::Texture _heartTexture;  ///< Heart texture (for life display)
        sf::Sprite _heartSprite;    ///< Heart sprite
        uint32_t _life{ 0 };        ///< Player life count
        bool _displayNotif{ false };///< Flag to indicate if a notification is displayed
};

#endif // HUD_HPP
