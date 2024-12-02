#pragma once

#include <SFML/System/Vector2.hpp>
#include "GameObject.hpp"

/**
 * @class Missile
 * @brief Base class for all missile objects.
 */
class Missile : public virtual GameObject {
public:
    Missile() = default;
    sf::Vector2<int> direction;
};