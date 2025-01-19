/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Bullet.hpp
*/

/**
 * @file Bullet.hpp
 *
 * @brief File in charge of containing the logic for the bullet class
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
            /**
             * @brief Represents a bullet entity in the game.
             */
            class Bullet : public EntityNode {
                public:
                /**
                 * @brief Default constructor for the Bullet class.
                 *
                 * @param EntityId The unique identifier of the entity. Default is 0.
                 */
                Bullet(const std::uint32_t EntityId = 0);

                /**
                 * @brief Parameterized constructor for initializing a Bullet object.
                 *
                 * @param sprite The sprite representing the bullet's appearance.
                 * @param fromEnemy Indicates if the bullet was fired by an enemy.
                 * @param positionInitial The initial position of the bullet.
                 * @param speed The speed of the bullet.
                 * @param direction The direction vector of the bullet. Default is {0, -1}.
                 * @param damage The damage inflicted by the bullet. Default is 10.
                 */
                Bullet(const GUI::ECS::Components::SpriteComponent &sprite, const bool fromEnemy, const std::pair<int, int> &positionInitial, const unsigned int speed, const std::pair<int, int> &direction = { 0, -1 }, const int damage = 10);

                /**
                 * @brief Copy constructor for Bullet.
                 *
                 * @param bullet The Bullet instance to copy.
                 */
                Bullet(const GUI::ECS::Demo::Bullet &bullet);

                /**
                 * @brief Constructor for creating a Bullet with both an Entity ID and attributes.
                 *
                 * @param EntityId The unique identifier of the entity.
                 * @param sprite The sprite representing the bullet's appearance.
                 * @param fromEnemy Indicates if the bullet was fired by an enemy.
                 * @param positionInitial The initial position of the bullet.
                 * @param speed The speed of the bullet.
                 * @param direction The direction vector of the bullet. Default is {0, -1}.
                 * @param damage The damage inflicted by the bullet. Default is 10.
                 */
                Bullet(const std::uint32_t EntityId, const GUI::ECS::Components::SpriteComponent &sprite, const bool fromEnemy, const std::pair<int, int> &positionInitial, const unsigned int speed, const std::pair<int, int> &direction = { 0, -1 }, const int damage = 10);

                /**
                 * @brief Combines entity ID and Bullet attributes from another instance.
                 *
                 * @param EntityId The unique identifier of the entity.
                 * @param bullet The Bullet instance to copy attributes from.
                 */
                Bullet(const std::uint32_t EntityId, const GUI::ECS::Demo::Bullet &bullet);

                /**
                 * @brief Default destructor for the Bullet class.
                 */
                ~Bullet() = default;

                /**
                 * @brief Sets the visibility of the bullet.
                 *
                 * @param visible True if the bullet should be visible, false otherwise.
                 */
                void setVisible(const bool visible);

                /**
                 * @brief Sets the position of the bullet.
                 *
                 * @param pos The new position as a pair of floats.
                 */
                void setPosition(const std::pair<float, float> &pos);

                /**
                 * @brief Sets the sprite representing the bullet.
                 *
                 * @param sprite The new sprite component.
                 */
                void setSprite(const GUI::ECS::Components::SpriteComponent &sprite);

                /**
                 * @brief Marks the bullet as fired by an enemy or not.
                 *
                 * @param enemy True if the bullet belongs to an enemy, false otherwise.
                 */
                void setEnemy(const bool enemy);

                /**
                 * @brief Sets the speed of the bullet.
                 *
                 * @param speed The speed value.
                 */
                void setSpeed(const unsigned int speed);

                /**
                 * @brief Sets the direction of the bullet.
                 *
                 * @param direction A pair of integers representing the direction vector.
                 */
                void setDirection(const std::pair<int, int> &direction);

                /**
                 * @brief Sets the size of the bullet.
                 *
                 * @param dimension A pair of floats representing width and height.
                 */
                void setSize(const std::pair<float, float> &dimension);

                /**
                 * @brief Sets the damage dealt by the bullet.
                 *
                 * @param damage The amount of damage.
                 */
                void setDamage(const int damage);

                /**
                 * @brief Advances the bullet's state by one tick.
                 */
                void tick();

                /**
                 * @brief Renders the bullet.
                 *
                 * @return The current sprite component representing the bullet.
                 */
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

                /**
                 * @brief Get the Speed at which the bullet is traveling
                 *
                 * @return const unsigned int the speed of the bullet
                 */
                const unsigned int getSpeed() const;

                /**
                 * @brief Get the Collision component
                 *
                 * @return const GUI::ECS::Systems::Collision
                 */
                const GUI::ECS::Systems::Collision getCollision() const;

                /**
                 * @brief Get the Sprite component
                 *
                 * @return const GUI::ECS::Components::SpriteComponent
                 */
                const GUI::ECS::Components::SpriteComponent getSprite() const;

                /**
                 * @brief Get the initial position that was set for the object
                 *
                 * @return const std::pair<int, int>
                 */
                const std::pair<int, int> getPositionInitial() const;

                /**
                 * @brief Get the Damage the bullet will inflict upon impact
                 *
                 * @return const int
                 */
                const int getDamage() const;

                /**
                 * @brief Get the Direction in which the bullet is travelling
                 *
                 * @return const std::pair<int, int>
                 */
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

                /**
                 * @brief Helper function to initialize the bullet's creation.
                 *
                 * @param positionInitial The initial position of the bullet.
                 */
                void _createBullet(const std::pair<int, int> &positionInitial);

                int _damage = 10;                                               //!< Damage inflicted by the bullet.
                bool _visible;                                                  //!< Visibility status of the bullet.
                bool _fromEnemy;                                                //!< Indicates if the bullet is from an enemy.
                unsigned int _speed;                                            //!< Speed of the bullet.
                std::pair<int, int> _direction;                                 //!< Direction vector of the bullet.
                std::pair<int, int> _positionInitial;                           //!< Initial position of the bullet.
                GUI::ECS::Systems::Collision _collision;                        //!< Collision system for the bullet.
                GUI::ECS::Components::SpriteComponent _sprite;                  //!< Sprite component of the bullet.
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
