#pragma once

#include "Entity.hpp"
#include <cstdlib>
#include <iostream>
#include "GameWorld.hpp"
#include <cmath>
#include "Missile.hpp"

class Monster : public Entity {
    public:
        Monster(uint32_t id, GameWorld&);
        virtual ~Monster();

        void update(float dt) override;
        bool collidesWith(const Entity& other) const override;
        void onCollision(Entity& other) override;

    private:
        float _shootTimer     = 0.f;
        float _shootInterval  = 2.f;
        GameWorld _world;
};
