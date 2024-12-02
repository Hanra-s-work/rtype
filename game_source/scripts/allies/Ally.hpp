#pragma once

#include "GameObject.hpp"

/**
 * @class Ally
 * @brief Represents an ally in game (not the player).
 */
class Ally : public GameObject {
public:
    Ally() = default;
    ~Ally() = default;

    void Fire(void);
    void TakeDamage(int damage);

private:
    int health;
};