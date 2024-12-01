#pragma once

#include <Ally.hpp>
#include <Input.hpp>

/**
 * @class Player
 * @brief Represents the player character.
 */
class Player : public Ally, public Input {
public:
    void OnMovement() override;
    void OnFire() override;
};