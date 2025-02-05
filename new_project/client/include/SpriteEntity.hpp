#ifndef HANDLE_SPRITE_HPP
    #define HANDLE_SPRITE_HPP

    #include "Entity.hpp"
    #include <SFML/Graphics.hpp>
    #include <string>
    #include <algorithm> // pour std::max
    #include <cmath>
    #include "TextureManager.hpp"

    class SpriteEntity : public Entity {
        public:
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
            sf::Vector2f _targetPos;
            sf::Texture texture;
            sf::Sprite sprite;
            sf::Vector2f velocity;
            bool isMoving;
            uint32_t _life{ 5 };
    };

#endif //HANDLE_SPRITE_HPP