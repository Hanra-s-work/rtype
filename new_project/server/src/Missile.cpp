//Missile.cpp
#include "Missile.hpp"
#include <cmath>

Missile::Missile(uint32_t id, EntityType missileType)
    : Entity(missileType, id), _ownerId(0)
{
}

Missile::~Missile() = default;

void Missile::update(float dt)
{
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;
}

bool Missile::collidesWith(const Entity& other) const
{
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx*dx + dy*dy;
    float radius = 10.f;
    float otherRadius = 20.f;
    return distSq <= (radius + otherRadius) * (radius + otherRadius);
}

void Missile::onCollision(Entity& other)
{
    // In our updated logic, collision resolution is handled in GameWorld::update.
    destroy();
    other.destroy();
}

void Missile::setOwnerId(uint32_t owner)
{
    _ownerId = owner;
}

uint32_t Missile::getOwnerId() const
{
    return _ownerId;
}