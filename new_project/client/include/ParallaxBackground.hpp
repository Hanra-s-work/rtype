#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class ParallaxBackground {
public:
    ParallaxBackground();
    void loadTextures(const std::vector<std::string>& texturePaths, sf::RenderWindow& window);
    void update(float dt, sf::RenderWindow& window);
    void render(sf::RenderWindow& window);

private:
    struct Layer {
        sf::Texture texture;
        sf::Sprite sprite;
        float speed;
    };

    std::vector<Layer> _layers;
};
