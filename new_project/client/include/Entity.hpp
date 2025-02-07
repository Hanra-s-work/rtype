#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <SFML/Graphics.hpp>

/**
 * @brief Base interface for all game entities.
*/
class Entity {
    public:
        virtual ~Entity() = default;
         /**
         * @brief Updates the entity state.
         * @param dt Time elapsed since last update (in seconds).
        */
        virtual void update(float dt) = 0;
        /**
         * @brief Renders the entity to the window.
         * @param window Render window.
        */
        virtual void render(sf::RenderWindow &window) = 0;
        /**
         * @brief Sets the position of the entity.
         * @param x X-coordinate.
         * @param y Y-coordinate.
        */
        virtual void setPosition(float x, float y) = 0;
        /**
         * @brief Gets the current position of the entity.
         * @return The position as a 2D vector.
        */
        virtual sf::Vector2f getPosition() const = 0;
};

#endif // ENTITY_HPP
