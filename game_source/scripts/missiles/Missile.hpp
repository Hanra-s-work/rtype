#pragma once

#include "GameObject.hpp"

/**
 * @class Missile
 * @brief Base class for all missile objects.
 */
class Missile : public GameObject {
public:
    std::string trajectory;
    int direction;
};