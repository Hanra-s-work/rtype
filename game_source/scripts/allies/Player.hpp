#pragma once

#include "Ally.hpp"

/**
 * @class Player
 * @brief Represents the player character.
 */
class Player : public Ally {
public:

    Player(const std::string &username, const int initialHeath);

    void OnCreate() override;
    void Update() override;
    void OnMovement();
    void OnFire();
};