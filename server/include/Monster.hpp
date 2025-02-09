//Monster.hpp
#pragma once

#include <cstdlib>
#include <iostream>
#include <cmath>

#include "Entity.hpp"
#include "GameWorld.hpp"
#include "Missile.hpp"

class GameWorld;

class Monster : public Entity {
    public:
        Monster(uint32_t id, GameWorld& world);
        virtual ~Monster();

        void update(float dt) override;
        bool collidesWith(const Entity& other) const override;
        void onCollision(Entity& other) override;

        int _health = 1;

    private:
        float _shootTimer = 0.f;
        float _shootInterval = 3.f;
        GameWorld& _world;
};