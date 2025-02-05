// HUD.cpp

#include "HUD.hpp"
#include "TextureManager.hpp"

HUD::HUD()
{
    _heartTexture = TextureManager::getTexture("client/assets/heart.png");
    _heartSprite.setTexture(_heartTexture);
    _heartSprite.setScale(0.5f, 0.5f);
}

void HUD::setFont(const sf::Font& font)
{
    _playerInfo.setFont(font);
    _playerInfo.setCharacterSize(20);
    _playerInfo.setFillColor(sf::Color::White);
    _scoreText.setFont(font);
    _scoreText.setCharacterSize(24);
    _scoreText.setFillColor(sf::Color::White);
    _notificationText.setFont(font);
    _notificationText.setCharacterSize(24);
}

void HUD::updatePlayer(uint32_t playerID, uint32_t life)
{
    _playerInfo.setString("Player: #" + std::to_string(playerID));
    _playerInfo.setPosition(10.f, 10.f);
    _life = life;
}

void HUD::setScore(uint32_t score)
{
    _scoreText.setString("Score: " + std::to_string(score));
    sf::FloatRect bounds = _scoreText.getLocalBounds();
    _scoreText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

void HUD::showNotification(const std::string& text, const sf::Color& color, const sf::Vector2f& position)
{
    _notificationText.setString(text);
    _notificationText.setFillColor(color);
    sf::FloatRect bounds = _notificationText.getLocalBounds();
    _notificationText.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    _notificationText.setPosition(position);
    _showNotification = true;
}

void HUD::draw(sf::RenderWindow& window)
{
    window.draw(_playerInfo);
    float startX = _playerInfo.getGlobalBounds().left + _playerInfo.getGlobalBounds().width + 10.f;
    float y = _playerInfo.getGlobalBounds().top;
    for (uint32_t i = 0; i < _life; i++) {
        _heartSprite.setPosition(startX + i * (_heartSprite.getGlobalBounds().width + 5.f), y);
        window.draw(_heartSprite);
    }
     sf::Vector2u windowSize = window.getSize();
    sf::Vector2f center(windowSize.x / 2.f, windowSize.y / 2.f);

    if (_showNotification) {
        window.draw(_notificationText);

        sf::FloatRect notifBounds = _notificationText.getGlobalBounds();
        _scoreText.setPosition(center.x, notifBounds.top + notifBounds.height + 20.f);
    } else {
        _scoreText.setPosition(center);
    }

    window.draw(_scoreText);
}
