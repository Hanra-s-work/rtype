#pragma once

#include "GameObject.hpp"

/**
 * @class Monster
 * @brief Represents an enemy monster.
 */
class Monster : public GameObject {
public:
    int health;
    std::string trajectory;

    void Fire() {}
    void TakeDamage(int damage) {}
};