//HandleSprites.cpp

#include "HandleSprites.hpp"

SpriteEntity::SpriteEntity(const std::string &imagePath, float posX, float posY, bool moving)
    : velocity(0.f, 0.f), isMoving(moving)
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

    void SpriteEntity::update(float dt) {
        // On récupère la position actuelle du sprite
        sf::Vector2f currentPos = sprite.getPosition();
        // On définit un facteur de lissage (plus il est grand, plus le sprite "s'accrochera" rapidement à sa cible)
        // Vous pouvez ajuster cette valeur selon le ressenti (par exemple 5.0f ou 10.0f)
        float smoothingFactor = 5.0f;
        
        // Calcul d'une nouvelle position interpolée
        sf::Vector2f newPos = currentPos + ( _targetPos - currentPos ) * smoothingFactor * dt;
        
        sprite.setPosition(newPos);
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