#pragma once

#include "Entity.hpp"

// A simple missile that moves according to its velocity
// Typically belongs to player's team if it's a player missile
class Missile : public Entity {
public:
    // Pass the ID (unique) and optionally team/type
    Missile(uint32_t id, EntityType missileType = EntityType::PlayerMissile);
    virtual ~Missile();

    void update(float dt) override;
    bool collidesWith(const Entity& other) const override;
    void onCollision(Entity& other) override;

private:
    // If you want any extra fields specifically for missiles (damage, range, etc.)
    // you can add them here
};
