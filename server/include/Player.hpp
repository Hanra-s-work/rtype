//Player.hpp
#pragma once

#include "Entity.hpp"

#include <iostream>

class Player : public Entity {
public:
    Player(uint32_t id);
    virtual ~Player();

    void update(float dt) override;
    bool collidesWith(const Entity& other) const override;
    void onCollision(Entity& other) override;

    uint8_t getLife() const;
    void decreaseLife();

    void addScore(int points);
    int  getScore() const;

private:
    int _score;
    uint8_t _life = 5;
    float _invulnTimer = 0.f;
};