#pragma once

#include "Ally.hpp"

/**
 * @class Player
 * @brief Represents the player character.
 */
class Player : public Ally {
public:
    void OnMovement();
    void OnFire();
};