#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

class Entity {
    public:
        virtual ~Entity() = default;
        virtual void update(float dt) = 0;
        virtual void render(sf::RenderWindow &window) = 0;
        virtual void setPosition(float x, float y) = 0;
        virtual sf::Vector2f getPosition() const = 0;
};

#endif // ENTITY_HPP
