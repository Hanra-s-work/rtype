#pragma once

#include "Entity.hpp"

class Missile : public Entity {
public:
    Missile(uint32_t id, EntityType missileType = EntityType::PlayerMissile);
    virtual ~Missile();

    void update(float dt) override;
    bool collidesWith(const Entity& other) const override;
    void onCollision(Entity& other) override;
    void setOwnerId(uint32_t owner);
    uint32_t getOwnerId() const;

    uint32_t _ownerId;
};