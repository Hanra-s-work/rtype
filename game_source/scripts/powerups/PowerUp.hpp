#pragma once

#include "GameObject.hpp"
#include "IPickable.hpp"

/**
 * @class PowerUp
 * @brief Represents a collectible power-up item.
 */
class PowerUp : public GameObject, public IPickable {
public:
    enum PowerType { DEFAULT };
    PowerType power;

    void Buff(GameObject *picker);
    void PickUp(GameObject *picker) override { Buff(picker); }
    void OnCollision(GameObject *other) override;
};