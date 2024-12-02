#pragma once

#include <SFML/Graphics/Sprite.hpp>

class IRenderable {
    virtual sf::Sprite &GetSprite(void) = 0;
};