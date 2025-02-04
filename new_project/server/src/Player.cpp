#include "Player.hpp"
#include <cmath>

Player::Player(uint32_t id)
: Entity(EntityType::Player, id)
, _score(0)
{
}

Player::~Player() = default;

void Player::update(float dt)
{
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;
}

bool Player::collidesWith(const Entity& other) const
{
    float dx = _position.x - other.getPosition().x;
    float dy = _position.y - other.getPosition().y;
    float distSq = dx*dx + dy*dy;
    float radius = 20.f;
    float otherRadius = 20.f;
    float sumR = radius + otherRadius;
    return distSq <= (sumR * sumR);
}

void Player::onCollision(Entity& other)
{
    decreaseLife();
}

void Player::addScore(int points)
{
    _score += points;
}

int Player::getScore() const
{
    return _score;
}

uint8_t Player::getLife() const
{
    return _life;
}

void Player::decreaseLife()
{
    if (_life > 0)
        --_life;
}