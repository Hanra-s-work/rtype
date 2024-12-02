#pragma once

#include <SFML/Graphics/Sprite.hpp>

/**
 * @class IRenderable
 * @brief Interface for classes that can be rendered on the window.
 */
class IRenderable {
    virtual sf::Sprite &GetSprite(void) = 0;
};