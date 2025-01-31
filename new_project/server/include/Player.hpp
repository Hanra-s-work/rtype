#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
    Player() = default;
    virtual ~Player() = default;

    void update(double dt) override {
        _position.x += _velocity.x * dt;
        _position.y += _velocity.y * dt;
    }

    bool collidesWith(const Entity& other) const override {
        return false;
    }
};
