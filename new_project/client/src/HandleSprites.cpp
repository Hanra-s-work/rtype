#include "HandleSprites.hpp"

SpriteEntity::SpriteEntity(const std::string& imagePath, float posX, float posY, bool moving)
    : velocity(0.f, 0.f), isMoving(moving) {
    if (!texture.loadFromFile(imagePath)) {
        throw std::runtime_error("Impossible de charger l'image : " + imagePath);
    }
    sprite.setTexture(texture);
    sprite.setPosition(posX, posY);
}

void SpriteEntity::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

void SpriteEntity::setVelocity(float vx, float vy) {
    velocity.x = vx;
    velocity.y = vy;
}

void SpriteEntity::setMoving(bool moving) {
    isMoving = moving;
}

void SpriteEntity::update(float deltaTime) {
    if (isMoving) {
        sprite.move(velocity * deltaTime);
    }
}

void SpriteEntity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void SpriteEntity::setScale(float scaleX, float scaleY) {
    sprite.setScale(scaleX, scaleY);
}

void SpriteEntity::rotate(float angle) {
    sprite.rotate(angle);
}

sf::Vector2f SpriteEntity::getPosition() const {
    return sprite.getPosition();
}

sf::Sprite& SpriteEntity::getSprite() {
    return sprite;
}