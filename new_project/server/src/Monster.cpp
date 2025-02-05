//Monster.cpp
#include "Monster.hpp"
#include <cmath>
#include <cstdlib>
#include <iostream>

static float degToRad(float deg) { return deg * 3.14159f / 180.f; }

Monster::Monster(uint32_t id, GameWorld& world)
    : Entity(EntityType::Monster, id), _world(world), _shootTimer(0.f), _shootInterval(2.f)
{
}

Monster::~Monster() = default;

void Monster::update(float dt)
{
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;

    _shootTimer += dt;
    if (_shootTimer >= _shootInterval) {
        _shootTimer = 0.f;
        float angleDeg = static_cast<float>(std::rand() % 360);
        float angle = degToRad(angleDeg);
        float bulletSpeed = 200.f;
        float vx = std::cos(angle) * bulletSpeed;
        float vy = std::sin(angle) * bulletSpeed;

        uint32_t bulletId = generateEntityId();
        auto bullet = std::make_unique<Missile>(bulletId, EntityType::MonsterMissile);
        bullet->setPosition(_position);
        bullet->setVelocity({vx, vy});
        _world.addEntity(std::move(bullet));
    }
}

bool Monster::collidesWith(const Entity& other) const
{
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx*dx + dy*dy;
    float radius = 20.f; // approximate collision radius for monster
    float otherRadius = 20.f;
    return distSq <= (radius + otherRadius) * (radius + otherRadius);
}

void Monster::onCollision(Entity& other)
{
    // In our collision loop, we may call this for additional logic if needed.
}