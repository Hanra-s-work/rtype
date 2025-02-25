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

void HUD::updatePlayer(uint32_t id, uint32_t life)
{
    _playerInfo.setString("Player: #" + std::to_string(id));
    _playerInfo.setPosition(10.f, 10.f);
    _life = life;
}

void HUD::setScore(uint32_t score)
{
    _scoreText.setString("Score: " + std::to_string(score));
    _scoreText.setPosition(10.f, 45.f);
}

void HUD::showNotification(const std::string& text, const sf::Color& color, const sf::Vector2f& pos)
{
    _notificationText.setString(text);
    _notificationText.setFillColor(color);
    _notificationText.setPosition(pos);
    _displayNotif = true;
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
    window.draw(_scoreText);
    if (_displayNotif)
        window.draw(_notificationText);
}
