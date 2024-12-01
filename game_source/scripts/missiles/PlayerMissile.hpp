#pragma once

#include <Missile.hpp>

/**
 * @class PlayerMissile
 * @brief Represents a missile fired by the player.
 */
class PlayerMissile : public Missile {
public:
    void OnCollision(GameObject* other) override;
};