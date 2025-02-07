#ifndef SPRITEENTITY_HPP
#define SPRITEENTITY_HPP

#include "Entity.hpp"
#include <SFML/Graphics.hpp>
#include <string>
#include "TextureManager.hpp"

/**
 * @brief Represents a graphical entity using a sprite.
*/
class SpriteEntity : public Entity {
    public:
        /**
         * @brief Constructs a new SpriteEntity object.
         * @param imagePath Path to the image file.
         * @param posX Initial X position.
         * @param posY Initial Y position.
         * @param moving Indicates whether the entity is moving.
        */
        SpriteEntity(const std::string &imagePath, float posX, float posY, bool moving = false);
        void setLife(uint32_t life);
        uint32_t getLife() const;
        void setTargetPosition(float x, float y);
        void update(float dt) override;
        void render(sf::RenderWindow &window) override;
        void setPosition(float x, float y) override;
        sf::Vector2f getPosition() const override;
        void setVelocity(float vx, float vy);
        void setMoving(bool moving);
        void setScale(float scaleX, float scaleY);
        void rotate(float angle);
        sf::Vector2f getSize() const;
    private:
        sf::Vector2f _targetPos;    ///< Target position for interpolation
        sf::Texture texture;        ///< Entity texture
        sf::Sprite sprite;          ///< Entity sprite
        sf::Vector2f velocity;      ///< Movement velocity
        bool isMoving;              ///< Movement flag
        uint32_t _life{ 5 };        ///< Entity life value
};

#endif // SPRITEENTITY_HPP
