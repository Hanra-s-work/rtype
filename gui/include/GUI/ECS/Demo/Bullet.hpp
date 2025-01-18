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
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components/SpriteComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Demo
        {
            class Bullet : public EntityNode {
                public:
                Bullet(const std::uint32_t EntityId = 0);

                Bullet(const GUI::ECS::Components::SpriteComponent &sprite, const bool fromEnemy, const std::pair<int, int> &positionInitial, const unsigned int speed, const std::pair<int, int> &direction = { 0, -1 }, const int damage = 10);

                Bullet(const GUI::ECS::Demo::Bullet &bullet);

                Bullet(const std::uint32_t EntityId, const GUI::ECS::Components::SpriteComponent &sprite, const bool fromEnemy, const std::pair<int, int> &positionInitial, const unsigned int speed, const std::pair<int, int> &direction = { 0, -1 }, const int damage = 10);

                Bullet(const std::uint32_t EntityId, const GUI::ECS::Demo::Bullet &bullet);

                ~Bullet() = default;

                void setVisible(const bool visible);

                void setPosition(const std::pair<float, float> &pos);

                void setSprite(const GUI::ECS::Components::SpriteComponent &sprite);

                void setEnemy(const bool enemy);

                void setSpeed(const unsigned int speed);

                void setDirection(const std::pair<int, int> &direction);

                void setSize(const std::pair<float, float> &dimension);

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

                /**
                 * @brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 *
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;


                private:

                void _createBullet(const std::pair<int, int> &positionInitial);

                int _damage = 10;
                bool _visible;
                bool _fromEnemy;
                unsigned int _speed;
                std::pair<int, int> _direction;
                std::pair<int, int> _positionInitial; //const 
                GUI::ECS::Systems::Collision _collision;
                GUI::ECS::Components::SpriteComponent _sprite;
            };

            /**
             * @brief Outputs the sprite's info to a stream.
             *
             * @param os The output stream.
             * @param item The sprite to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const Bullet &item);
        }
    }
}
