#pragma once

#include "GameObject.hpp"

/**
 * @class Ally
 * @brief Represents an ally in game (not the player).
 */
class Ally : public GameObject{
private:
    int health;

public:
    std::string username;

    Ally(const std::string& username, int initialHealth);

    void OnCreate();
    void Update();
    void TakeDamage(int damage);
};