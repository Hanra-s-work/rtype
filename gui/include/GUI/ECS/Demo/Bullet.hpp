/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Bullet.hpp
*/

#pragma once
#include "Log.hpp"
#include "Recoded.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/Components/SpriteComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Demo
        {
            class Bullet {
                public:
                Bullet() = default;

                Bullet(const GUI::ECS::Components::SpriteComponent &sprite, const bool fromEnemy, const std::pair<int, int> &positionInitial, const unsigned int speed, const std::pair<int, int> &direction = { 0, -1 }, const int damage = 10);

                Bullet(const GUI::ECS::Demo::Bullet &bullet);

                ~Bullet() = default;

                void setVisible(const bool visible);

                void setPosition(const std::pair<float, float> &pos);

                void setSprite(const GUI::ECS::Components::SpriteComponent &sprite);

                void setEnemy(const bool enemy);

                void setSpeed(const unsigned int speed);

                void setDirection(const std::pair<int, int> &direction);

                void setDamage(const int damage);

                void tick();

                const GUI::ECS::Components::SpriteComponent render();

                const bool isVisible() const;

                const bool isEnemy() const;

                const std::pair<float, float> getPosition() const;


                /*
                If needed, check the opposite condition, as if<object> was the target and target the object
                ( = check isColliding as target with bullet as parameter)
                */
                const bool isColliding(const GUI::ECS::Systems::Collision &second) const;

                /**
                 * @brief Updates the sprite by copying another Bullet.
                 *
                 * @param copy The Bullet to copy data from.
                 */
                void update(const GUI::ECS::Demo::Bullet &copy);

                /**
                 * @brief Overloads the assignment operator to copy from another Bullet.
                 *
                 * @param copy The Bullet to copy data from.
                 *
                 * @return A reference to the updated instance.
                 */
                Bullet &operator =(const GUI::ECS::Demo::Bullet &copy);

                const unsigned int getSpeed() const;

                const GUI::ECS::Systems::Collision getCollision() const;

                const GUI::ECS::Components::SpriteComponent getSprite() const;

                const std::pair<int, int> getPositionInitial() const;

                const int getDamage() const;

                const std::pair<int, int> getDirection() const;

                private:

                GUI::ECS::Components::SpriteComponent _sprite;
                int _damage = 10;
                bool _visible;
                bool _fromEnemy;
                std::pair<int, int> _positionInitial; //const 
                unsigned int _speed;
                std::pair<int, int> _direction;
                GUI::ECS::Systems::Collision _collision;
            };
        }
    }
}
