#pragma once

#include <GameObject.hpp>
#include <Pickable.hpp>

/**
 * @class HealthPack
 * @brief Represents a collectible health pack.
 */
class HealthPack : public GameObject, public IPickable {
public:
    void Heal(GameObject *picker);
    void PickUp(GameObject *picker) override { Heal(picker); }
    void OnCollision(GameObject *other) override;
};