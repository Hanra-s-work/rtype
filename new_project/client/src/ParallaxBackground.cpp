#include "ParallaxBackground.hpp"
#include <iostream>

ParallaxBackground::ParallaxBackground() {}

void ParallaxBackground::loadTextures(const std::vector<std::string>& texturePaths, sf::RenderWindow& window)
{
    float speedFactor = 30.0f;
    float windowHeight = window.getSize().y;

    for (size_t i = 0; i < texturePaths.size(); ++i) {
        Layer layer;
        if (!layer.texture.loadFromFile(texturePaths[i])) {
            std::cerr << "❌ Erreur : Impossible de charger " << texturePaths[i] << "\n";
            continue;
        } else {
            std::cout << "✅ Chargé avec succès : " << texturePaths[i] << "\n";
        }

        float scaleX = static_cast<float>(window.getSize().x) / layer.texture.getSize().x;
        float scaleY = static_cast<float>(window.getSize().y) / layer.texture.getSize().y;
        float scale = std::max(scaleX, scaleY); // Conserve le ratio
        layer.sprite.setScale(scale, scale);
        layer.texture.setRepeated(true);
        layer.sprite.setTextureRect(sf::IntRect(0, 0, window.getSize().x, window.getSize().y));
        std::cout << "Texture size: " << layer.texture.getSize().x << "x" << layer.texture.getSize().y << "\n";
        std::cout << "Sprite scale: " << scale << "\n";
        std::cout << "Sprite size after scaling: " << layer.sprite.getGlobalBounds().width << "x" << layer.sprite.getGlobalBounds().height << "\n";
        layer.sprite.setPosition(0, 0); // Position de départ fixe
        layer.speed = speedFactor * (i + 1);
        _layers.push_back(layer);
    }
}

// ParallaxBackground.cpp (méthode update)
void ParallaxBackground::update(float dt, sf::RenderWindow& window)
{
    for (auto& layer : _layers) {
        layer.sprite.move(-layer.speed * dt, 0);
        float spriteWidth = layer.sprite.getGlobalBounds().width;
        if (layer.sprite.getPosition().x <= -spriteWidth) {
            layer.sprite.setPosition(0, 0);
        }
    }
}

// ParallaxBackground.cpp (méthode render)
void ParallaxBackground::render(sf::RenderWindow& window)
{
    if (_layers.empty()) return;

    for (auto& layer : _layers) {
        // Dessiner le sprite principal
        window.draw(layer.sprite);
        
        // Dessiner une copie à droite pour le défilement continu
        sf::Sprite secondSprite = layer.sprite;
        secondSprite.setPosition(layer.sprite.getPosition().x + layer.sprite.getGlobalBounds().width, 0);
        // Dans ParallaxBackground::render()
std::cout << "Sprite position: " << layer.sprite.getPosition().x << ", " << layer.sprite.getPosition().y << "\n";
        window.draw(secondSprite);
    }
}
