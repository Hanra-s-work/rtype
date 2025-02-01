#include "Monster.hpp"
#include <cmath>

Monster::Monster(uint32_t id)
: Entity(EntityTeam::Monsters, EntityType::Monster, id)
{
}

Monster::~Monster() = default;

void Monster::update(float dt)
{
    // Move left or some AI pattern
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;
}

bool Monster::collidesWith(const Entity& other) const
{
    // Similar bounding-circle approach as Player
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx*dx + dy*dy;
    float radius = 20.f; // example monster radius
    float otherRadius = 20.f; 
    float sumR = radius + otherRadius;
    return distSq <= (sumR * sumR);
}

void Monster::onCollision(Entity& other)
{
    // If collided with a Player missile => destroy ourselves
    // If collided with a player => maybe deal damage, etc.
}
