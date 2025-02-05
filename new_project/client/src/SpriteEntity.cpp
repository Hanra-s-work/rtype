// HandleSprites.cpp

#include "SpriteEntity.hpp"

SpriteEntity::SpriteEntity(const std::string &imagePath, float posX, float posY, bool moving)
    : velocity(0.f, 0.f), isMoving(moving), _targetPos(sf::Vector2f(posX, posY))
{
    texture = TextureManager::getTexture(imagePath);
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
}

void SpriteEntity::setLife(uint32_t life)
{
    _life = life;
}

uint32_t SpriteEntity::getLife() const
{
    return _life;
}

void SpriteEntity::setTargetPosition(float x, float y)
{
    _targetPos = sf::Vector2f(x, y);
}

void SpriteEntity::update(float dt)
{
    sprite.setPosition(_targetPos);
}

void SpriteEntity::render(sf::RenderWindow &window) 
{
    window.draw(sprite);
}

void SpriteEntity::setPosition(float x, float y)
{
    sprite.setPosition(x, y);
}

sf::Vector2f SpriteEntity::getPosition() const
{
    return sprite.getPosition();
}

void SpriteEntity::setVelocity(float vx, float vy)
{
    velocity.x = vx;
    velocity.y = vy;
}

void SpriteEntity::setMoving(bool moving)
{
    isMoving = moving;
}

void SpriteEntity::setScale(float scaleX, float scaleY)
{
    sprite.setScale(scaleX, scaleY);
}

void SpriteEntity::rotate(float angle)
{
    sprite.rotate(angle);
}

sf::Vector2f SpriteEntity::getSize() const
{
    sf::FloatRect bounds = sprite.getGlobalBounds();
    return sf::Vector2f(bounds.width, bounds.height);
}
