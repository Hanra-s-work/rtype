#include "HandleBackground.hpp"

HandleBackground::HandleBackground(sf::RenderWindow& window) : _starsSpeed(70.f)
{
}

bool HandleBackground::loadAssets(const std::string& bgPath, const std::string& starsPath)
{
    if (!_bgTexture.loadFromFile(bgPath))
        return false;
    if (!_starsTexture.loadFromFile(starsPath))
        return false;
    _bgSprite.setTexture(_bgTexture);
    _stars1.setTexture(_starsTexture);
    _stars2.setTexture(_starsTexture);
    return true;
}

void HandleBackground::resize(sf::Vector2u newSize)
{
    _bgSprite.setScale(static_cast<float>(newSize.x) / _bgTexture.getSize().x,
                       static_cast<float>(newSize.y) / _bgTexture.getSize().y);
    _scaleX = static_cast<float>(newSize.x) / _starsTexture.getSize().x;
    _scaleY = static_cast<float>(newSize.y) / _starsTexture.getSize().y;
    _stars1.setScale(_scaleX, _scaleY);
    _stars2.setScale(_scaleX, _scaleY);
    _stars1.setPosition(0, 0);
    _stars2.setPosition(newSize.x, 0);
}

void HandleBackground::update(float dt)
{
    _stars1.move(-_starsSpeed * dt, 0);
    _stars2.move(-_starsSpeed * dt, 0);
    if (_stars1.getPosition().x + _starsTexture.getSize().x * _scaleX <= 0)
        _stars1.setPosition(_stars2.getPosition().x + _starsTexture.getSize().x * _scaleX, 0);
    if (_stars2.getPosition().x + _starsTexture.getSize().x * _scaleX <= 0)
        _stars2.setPosition(_stars1.getPosition().x + _starsTexture.getSize().x * _scaleX, 0);
}

void HandleBackground::render(sf::RenderWindow& window)
{
    window.draw(_bgSprite);
    window.draw(_stars1);
    window.draw(_stars2);
}
