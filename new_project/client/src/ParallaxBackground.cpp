#include "ParallaxBackground.hpp"
#include <iostream>

void ParallaxBackground::addLayer(const std::string& textureFile, float speed)
{
    Layer layer;
    if (!layer.texture.loadFromFile(textureFile)) {
        std::cerr << "Failed to load " << textureFile << "\n";
    }
    layer.texture.setRepeated(true); // if you want seamless repeat

    layer.sprite1.setTexture(layer.texture);
    layer.sprite2.setTexture(layer.texture);

    // Position sprite2 to start immediately after sprite1
    sf::Vector2u size = layer.texture.getSize();

    // For a horizontal scroll, set the second sprite's x to the texture width
    layer.sprite2.setPosition((float)size.x, 0.f);

    layer.speed = speed;
    layer.offsetX = 0.f;

    _layers.push_back(std::move(layer));
}

void ParallaxBackground::update(float dt)
{
    // Scroll each layer horizontally
    for (auto &layer : _layers) {
        layer.offsetX += layer.speed * dt;

        // If offset is bigger than the texture width, wrap around
        float texWidth = (float)layer.texture.getSize().x;
        if (layer.offsetX >= texWidth) {
            layer.offsetX -= texWidth;
        }

        // Update the sprite positions
        layer.sprite1.setPosition(-layer.offsetX, 0.f);
        layer.sprite2.setPosition(-layer.offsetX + texWidth, 0.f);
    }
}

void ParallaxBackground::draw(sf::RenderWindow &window)
{
    for (auto &layer : _layers) {
        window.draw(layer.sprite1);
        window.draw(layer.sprite2);
    }
}
