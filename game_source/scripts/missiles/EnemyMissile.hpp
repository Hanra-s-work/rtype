#pragma once

#include "Missile.hpp"

/**
 * @class EnemyMissile
 * @brief Represents a missile fired by enemies.
 */
class EnemyMissile : public Missile {
public:
    void OnCollision(GameObject *other) override;
};