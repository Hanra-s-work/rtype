#include "Player.hpp"
#include <cmath> // if needed for collisions

Player::Player(uint32_t id)
: Entity(EntityTeam::Players, EntityType::Player, id)
, _score(0)
{
}

Player::~Player() = default;

void Player::update(float dt)
{
    // simple movement
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;

    // you can clamp position, handle screen boundaries, etc.
}

bool Player::collidesWith(const Entity& other) const
{
    // Example: naive bounding-circle check
    // (In real code, you'd store a radius or bounding box)
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx*dx + dy*dy;
    float radius = 20.f; // example radius
    float otherRadius = 20.f; // or dynamic based on type
    float sumR = radius + otherRadius;
    return distSq <= (sumR * sumR);
}

void Player::onCollision(Entity& other)
{
    // If we collide with a monster or monster missile, maybe take damage
    // If we collide with a powerup, maybe apply effect, etc.
}

void Player::addScore(int points)
{
    _score += points;
}

int Player::getScore() const
{
    return _score;
}
