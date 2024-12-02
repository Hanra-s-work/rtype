#pragma once

#include "GameObject.hpp"

/**
 * @class Monster
 * @brief Represents an enemy monster.
 */
class Monster : public GameObject {
public:
    Monster(const int initialHealth);

    void OnCreate() override;
    void Update() override;
    void Fire();
    void TakeDamage(int damage);
private:
    int health;
};