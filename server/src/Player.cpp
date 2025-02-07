//Player.cpp
#include "Player.hpp"
#include <iostream>

Player::Player(uint32_t id)
    : Entity(EntityType::Player, id), _score(0), _life(5)
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
    // We rely on GameWorld's AABB collision using defined hitbox dimensions.
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
    if (_life > 0)
        --_life;
    std::cout << "Player " << getId() << " life decreased to " << _life << std::endl;
    if (_life == 0) {
        std::cout << "Player " << getId() << " has died." << std::endl;
        destroy();
    }
}