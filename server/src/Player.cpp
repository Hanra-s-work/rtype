//Player.cpp
#include "Player.hpp"

Player::Player(uint32_t id): Entity(EntityType::Player, id), _score(0), _life(5), _invulnTimer(0.f)
{
}

Player::~Player() = default;

void Player::update(float dt)
{
    _position.x += _velocity.x * dt;
    _position.y += _velocity.y * dt;
    if (_invulnTimer > 0.f)
        _invulnTimer -= dt;
}

bool Player::collidesWith(const Entity& other) const
{
    return false;
}

void Player::onCollision(Entity& other)
{
    decreaseLife();
}

void Player::addScore(int points)
{
    _score += points;
    std::cout << "Player " << getId() << " score is now " << _score << std::endl;
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
    if (_invulnTimer > 0.f)
        return;

    if (_life > 0)
        --_life;
    std::cout << "Player " << getId() << " life decreased to " << static_cast<int>(_life) << std::endl;
    _invulnTimer = 1.0f;
    if (_life == 0) {
        std::cout << "Player " << getId() << " has died." << std::endl;
    }
}