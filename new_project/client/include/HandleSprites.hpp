#ifndef HANDLESPRITES_HPP
#define HANDLESPRITES_HPP

#include <SFML/Graphics.hpp>
#include <iostream>

#include <SFML/Graphics.hpp>

class SpriteEntity {
    public:
        SpriteEntity();
        SpriteEntity(const std::string& imagePath, float posX = 0, float posY = 0, bool moving = false);

        void draw(sf::RenderWindow& window);

        void setVelocity(float vx, float vy);

        void setMoving(bool moving);

        void update(float deltaTime);

        void setPosition(float x, float y);

        void setScale(float scaleX, float scaleY);

        void rotate(float angle);

        sf::Vector2f getPosition() const;

        sf::Sprite& getSprite();
        
    private:
        sf::Texture texture;
        sf::Sprite sprite;
        sf::Vector2f velocity;
        bool isMoving;
};

#endif // HANDLESPRITES_HPP
