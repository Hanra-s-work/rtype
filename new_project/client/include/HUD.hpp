#ifndef HUD_HPP
#define HUD_HPP

#include <SFML/Graphics.hpp>
#include <string>

class HUD {
    public:
        HUD();
        void setFont(const sf::Font& font);
        void updatePlayer(uint32_t id, uint32_t life);
        void setScore(uint32_t score);
        void showNotification(const std::string& text, const sf::Color& color, const sf::Vector2f& pos);
        void draw(sf::RenderWindow& window);
    private:
        sf::Text _playerInfo;
        sf::Text _scoreText;
        sf::Text _notificationText;
        sf::Texture _heartTexture;
        sf::Sprite _heartSprite;
        uint32_t _life{ 0 };
        bool _displayNotif{ false };
};

#endif // HUD_HPP
