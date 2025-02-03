//HandleBackground.cpp

#include "HandleBackground.hpp"
#include <iostream>

HandleBackground::HandleBackground(sf::RenderWindow& window) : _starsSpeed(50.0f) {
    // Initialisation des textures (chargement séparé via loadAssets)
}

bool HandleBackground::loadAssets(const std::string& backgroundPath, const std::string& starsPath) {
    if (!_backgroundTexture.loadFromFile(backgroundPath)) {
        std::cerr << "Erreur: Impossible de charger " << backgroundPath << std::endl;
        return false;
    }

    if (!_starsTexture.loadFromFile(starsPath)) {
        std::cerr << "Erreur: Impossible de charger " << starsPath << std::endl;
        return false;
    }

    _background.setTexture(_backgroundTexture);
    _stars1.setTexture(_starsTexture);
    _stars2.setTexture(_starsTexture);

    return true;
}

void HandleBackground::resize(sf::Vector2u newSize) {
    // Ajuster le fond
    _background.setScale(
        (float)newSize.x / _backgroundTexture.getSize().x,
        (float)newSize.y / _backgroundTexture.getSize().y
    );

    // Ajuster la taille et position des étoiles
    _starsScaleX = (float)newSize.x / _starsTexture.getSize().x;
    _starsScaleY = (float)newSize.y / _starsTexture.getSize().y;
    _stars1.setScale(_starsScaleX, _starsScaleY);
    _stars2.setScale(_starsScaleX, _starsScaleY);

    _stars1.setPosition(0, 0);
    _stars2.setPosition(newSize.x, 0);
}

void HandleBackground::update(float dt) {
    _stars1.move(-_starsSpeed * dt, 0);
    _stars2.move(-_starsSpeed * dt, 0);

    if (_stars1.getPosition().x + _starsTexture.getSize().x * _starsScaleX <= 0)
        _stars1.setPosition(_stars2.getPosition().x + _starsTexture.getSize().x * _starsScaleX, 0);

    if (_stars2.getPosition().x + _starsTexture.getSize().x * _starsScaleX <= 0)
        _stars2.setPosition(_stars1.getPosition().x + _starsTexture.getSize().x * _starsScaleX, 0);
}

void HandleBackground::render(sf::RenderWindow& window) {
    window.draw(_background);
    window.draw(_stars1);
    window.draw(_stars2);
}
