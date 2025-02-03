#pragma once

#include "Entity.hpp"

class Player : public Entity {
public:
    Player(uint32_t id);
    virtual ~Player();

    void update(float dt) override;
    bool collidesWith(const Entity& other) const override;
    void onCollision(Entity& other) override;

    void addScore(int points);
    int  getScore() const;

private:
    int _score;
};
