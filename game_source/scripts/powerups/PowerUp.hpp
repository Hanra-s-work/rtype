#pragma once

#include <GameObject.hpp>
#include <Pickable.hpp>

/**
 * @class PowerUp
 * @brief Represents a collectible power-up item.
 */
class PowerUp : public GameObject, public Pickable {
public:
    enum PowerType { DEFAULT };
    PowerType power;

    void Buff(GameObject *picker);
    void PickUp(GameObject *picker) override { Buff(picker); }
    void OnCollision(GameObject *other) override;
};