//HandleSprites.hpp

#pragma once
#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include <stdexcept>
#include "TextureManager.hpp"
#include <tgmath.h>

class SpriteEntity : public Entity {
public:
    // Constructeur qui charge l'image spécifiée et positionne le sprite
    SpriteEntity(const std::string &imagePath, float posX, float posY, bool moving = false);

    void setTargetPosition(float x, float y) { 
        _targetPos = sf::Vector2f(x, y); 
    }
    // Méthodes de l'interface Entity
    void update(float dt) override;
    
    void render(sf::RenderWindow &window) override;
    void setPosition(float x, float y) override;
    
    sf::Vector2f getPosition() const override;
    
    // Méthodes complémentaires
    void setVelocity(float vx, float vy);
    
    void setMoving(bool moving);
    
    void setScale(float scaleX, float scaleY);
    
    void rotate(float angle);

    void draw(sf::RenderWindow &window);
private:
    sf::Vector2f _targetPos;
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool isMoving;
};
