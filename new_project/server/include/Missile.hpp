#pragma once

#include "Entity.hpp"

class Missile : public Entity {
public:
    Missile(uint32_t id, EntityType missileType = EntityType::PlayerMissile);
    virtual ~Missile();

    void update(float dt) override;
    bool collidesWith(const Entity& other) const override;
    void onCollision(Entity& other) override;
};