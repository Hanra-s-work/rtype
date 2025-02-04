#include "Missile.hpp"
#include <cmath>

Missile::Missile(uint32_t id, EntityType missileType)
: Entity(missileType, id)
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
    return distSq <= std::pow(radius + otherRadius, 2);
}

void Missile::onCollision(Entity& other)
{
    if (other.getType() == EntityType::Monster || other.getType() == EntityType::MonsterMissile) {
        destroy();
        other.destroy();
    }
}