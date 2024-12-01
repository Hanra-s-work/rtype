#pragma once

#include <Ally.hpp>
#include <IInput.hpp>

/**
 * @class Player
 * @brief Represents the player character.
 */
class Player : public Ally, public IInput {
public:
    void OnMovement() override;
    void OnFire() override;
};