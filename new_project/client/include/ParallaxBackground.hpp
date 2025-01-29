#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>

/**
 * ParallaxBackground
 * - Holds multiple layers (sprites) that move at different speeds
 * - We update their position each frame for a scrolling effect
 */
class ParallaxBackground {
public:
    // Add a layer from a texture file, at a given scroll speed
    void addLayer(const std::string& textureFile, float speed);

    // Update the scrolling
    void update(float dt);

    // Draw layers
    void draw(sf::RenderWindow& window);

private:
    struct Layer {
        sf::Texture texture;
        sf::Sprite sprite1;
        sf::Sprite sprite2;
        float speed;
        float offsetX; // how far we've scrolled horizontally (or vertically)
    };

    std::vector<Layer> _layers;
};
