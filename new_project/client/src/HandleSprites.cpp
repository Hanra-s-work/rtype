//HandleSprites.cpp

#include "HandleSprites.hpp"

SpriteEntity::SpriteEntity(const std::string &imagePath, float posX, float posY, bool moving)
    : velocity(0.f, 0.f), isMoving(moving)
    {
        texture = TextureManager::getTexture(imagePath);
        sprite.setTexture(texture);
        sprite.setPosition(posX, posY);
    }

    // Méthodes de l'interface Entity
    void SpriteEntity::update(float dt) {
        sf::Vector2f currentPos = sprite.getPosition();
        sf::Vector2f dir = _targetPos - currentPos;
        float distance = std::hypot(dir.x, dir.y);
        if (distance > 1.0f) { // seuil pour éviter les oscillations
            dir /= distance; // normalisation
            sprite.move(dir * dt * 500.0f); // 500.0f représente la vitesse (à ajuster)
        }
    }


    
    void SpriteEntity::render(sf::RenderWindow &window) {
        window.draw(sprite);
    }
    
    void SpriteEntity::setPosition(float x, float y) {
        sprite.setPosition(x, y);
    }
    
    sf::Vector2f SpriteEntity::getPosition() const {
        return sprite.getPosition();
    }
    
    // Méthodes complémentaires
    void SpriteEntity::setVelocity(float vx, float vy) {
        velocity.x = vx;
        velocity.y = vy;
    }
    
    void SpriteEntity::setMoving(bool moving) {
        isMoving = moving;
    }
    
    void SpriteEntity::setScale(float scaleX, float scaleY) {
        sprite.setScale(scaleX, scaleY);
    }
    
    void SpriteEntity::rotate(float angle) {
        sprite.rotate(angle);
    }

    void SpriteEntity::draw(sf::RenderWindow &window) {
    window.draw(sprite);
    }