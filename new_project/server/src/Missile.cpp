#include "Missile.hpp"
#include <cmath> // if needed for collision checks

Missile::Missile(uint32_t id, EntityType missileType)
: Entity(missileType, id)
{
    // Optionally set a default velocity here, or do it after creation.
}

Missile::~Missile() = default;

void Missile::update(float dt)
{
    // Move according to velocity
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;

    // You might remove the missile if it goes offscreen
    // e.g. if (_position.x > 1280) { destroy(); }
}

bool Missile::collidesWith(const Entity& other) const
{
    // For simplicity, do a bounding-circle check or bounding-box check
    // Example circle check:
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx*dx + dy*dy;
    float radius = 10.f;         // missile radius
    float otherRadius = 20.f;    // rough radius for the other entity
    return distSq <= std::pow(radius + otherRadius, 2);
}

void Missile::onCollision(Entity& other)
{
    // If we collide with an enemy (team=Monsters),
    // we might destroy both
    if (other.getType() == EntityType::Monster || other.getType() == EntityType::MonsterMissile) {
        destroy();
        other.destroy();
    }
    // else if we hit the wall or something else, handle differently
}
