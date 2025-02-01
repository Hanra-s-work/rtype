#pragma once

#include "Entity.hpp"

class Monster : public Entity {
public:
    Monster(uint32_t id);
    virtual ~Monster();

    void update(float dt) override;
    bool collidesWith(const Entity& other) const override;
    void onCollision(Entity& other) override;
};
