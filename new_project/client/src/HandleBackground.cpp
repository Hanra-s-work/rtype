// HandleBackground.cpp

#include "HandleBackground.hpp"

HandleBackground::HandleBackground(sf::RenderWindow& window) : _starsSpeed(70.0f)
{
}

bool HandleBackground::loadAssets(const std::string& backgroundPath, const std::string& starsPath)
{
    if (!_backgroundTexture.loadFromFile(backgroundPath))
        return false;
    if (!_starsTexture.loadFromFile(starsPath))
        return false;
    _background.setTexture(_backgroundTexture);
    _stars1.setTexture(_starsTexture);
    _stars2.setTexture(_starsTexture);
    return true;
}

void HandleBackground::resize(sf::Vector2u newSize)
{
    _background.setScale(static_cast<float>(newSize.x) / _backgroundTexture.getSize().x,
                           static_cast<float>(newSize.y) / _backgroundTexture.getSize().y);
    _starsScaleX = static_cast<float>(newSize.x) / _starsTexture.getSize().x;
    _starsScaleY = static_cast<float>(newSize.y) / _starsTexture.getSize().y;
    _stars1.setScale(_starsScaleX, _starsScaleY);
    _stars2.setScale(_starsScaleX, _starsScaleY);
    _stars1.setPosition(0, 0);
    _stars2.setPosition(newSize.x, 0);
}

void HandleBackground::update(float dt)
{
    _stars1.move(-_starsSpeed * dt, 0);
    _stars2.move(-_starsSpeed * dt, 0);
    if (_stars1.getPosition().x + _starsTexture.getSize().x * _starsScaleX <= 0)
        _stars1.setPosition(_stars2.getPosition().x + _starsTexture.getSize().x * _starsScaleX, 0);
    if (_stars2.getPosition().x + _starsTexture.getSize().x * _starsScaleX <= 0)
        _stars2.setPosition(_stars1.getPosition().x + _starsTexture.getSize().x * _starsScaleX, 0);
}

void HandleBackground::render(sf::RenderWindow& window)
{
    window.draw(_background);
    window.draw(_stars1);
    window.draw(_stars2);
}
