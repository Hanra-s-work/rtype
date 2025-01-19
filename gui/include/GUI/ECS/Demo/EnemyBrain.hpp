/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EnemyBrain.hpp
*/

/**
 * @file EnemyBrain.hpp
 *
 * @brief Declaration of the EnemyBrain class and its related functionality.
 *
 * @details This file contains the definition of the EnemyBrain class, which is part of the ECS (Entity-Component-System) architecture in the Demo namespace.
 * It provides behavior for enemy entities, including managing their sprite, position, health, and interactions.
 */

#pragma once
#include <random>
#include "Log.hpp"
#include "Recoded.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Demo/Bullet.hpp"
#include "GUI/ECS/Demo/PlayerBrain.hpp"
#include "GUI/ECS/Systems/Collision.hpp"
#include "GUI/ECS/Components/SpriteComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Demo
        {
            /**
             * @brief The EnemyBrain class represents the logic and behavior of an enemy entity.
             *
             * @details This class inherits from EntityNode and manages various aspects of an enemy's behavior, such as its sprite, position, health, and visibility.
             */
            class EnemyBrain : public EntityNode {
                public:
                /**
                 * @brief Default constructor.
                 *
                 * @param entityId The unique ID of the entity. Default is 0.
                 */
                EnemyBrain(const std::uint32_t entityId = 0);

                /**
                 * @brief Copy constructor.
                 *
                 * @param copy The EnemyBrain instance to copy.
                 */
                EnemyBrain(const GUI::ECS::Demo::EnemyBrain &copy);

                /**
                 * @brief Parameterized constructor that initializes with another EnemyBrain.
                 *
                 * @param entityId The unique ID of the entity.
                 * @param copy The EnemyBrain instance to copy.
                 */
                EnemyBrain(const std::uint32_t entityId, const GUI::ECS::Demo::EnemyBrain &copy);

                /**
                 * @brief Destructor.
                 */
                ~EnemyBrain() = default;

                /**
                 * @brief Sets the sprite components for the enemy and its bullet.
                 *
                 * @param sprite The sprite for the enemy.
                 * @param bullet The sprite for the bullet.
                 */
                void setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet);

                /**
                 * @brief Sets the position of the enemy.
                 *
                 * @param pos The position as a pair of (x, y) coordinates.
                 */
                void setPosition(const std::pair<float, float> &pos);

                /**
                 * @brief Sets the dimensions of the enemy.
                 *
                 * @param size The dimensions as a pair of (width, height).
                 */
                void setDimension(const std::pair<float, float> &size);

                /**
                 * @brief Sets the health of the enemy.
                 *
                 * @param health The health value.
                 */
                void setHealth(const long int health);

                /**
                 * @brief Sets the visibility of the enemy.
                 *
                 * @param visible True if visible, false otherwise.
                 */
                void setVisible(const bool visible);

                /**
                 * @brief Sets the size of the bullet.
                 *
                 * @param size The size as a pair of (width, height).
                 */
                void setBulletSize(const std::pair<float, float> &size);

                /**
                 * @brief Checks if the enemy is colliding with another entity.
                 *
                 * @param second The collision data of the other entity.
                 *
                 * @return True if colliding, false otherwise.
                 */
                const bool isColliding(const GUI::ECS::Systems::Collision &second) const;

                /**
                 * @brief Checks if the enemy is visible.
                 *
                 * @return True if visible, false otherwise.
                 */
                const bool isVisible() const;

                /**
                 * @brief Updates the enemy's state and determines if it should fire a bullet.
                 *
                 * @return An optional Bullet instance if a bullet is fired, or std::nullopt if not.
                 */
                const std::optional<GUI::ECS::Demo::Bullet> tick();

                /**
                 * @brief Renders the enemy's sprite.
                 *
                 * @return The SpriteComponent of the enemy.
                 */
                const GUI::ECS::Components::SpriteComponent render();

                /**
                 * @brief Updates the sprite by copying another EnemyBrain.
                 *
                 * @param copy The EnemyBrain to copy data from.
                 */
                void update(const GUI::ECS::Demo::EnemyBrain &copy);

                /**
                 * @brief Overloads the assignment operator to copy from another EnemyBrain.
                 *
                 * @param copy The EnemyBrain to copy data from.
                 *
                 * @return A reference to the updated instance.
                 */
                EnemyBrain &operator =(const GUI::ECS::Demo::EnemyBrain &copy);

                /**
                 * @brief Gets the visibility status of the enemy.
                 *
                 * @return True if visible, false otherwise.
                 */
                const bool getVisible() const;

                /**
                 * @brief Gets the health of the enemy.
                 *
                 * @return The current health value.
                 */
                const long int getHealth() const;

                /**
                 * @brief Gets the bullet data for the enemy.
                 *
                 * @return The Bullet instance.
                 */
                const GUI::ECS::Demo::Bullet getBullet() const;

                /**
                 * @brief Gets the sprite data for the enemy.
                 *
                 * @return The SpriteComponent instance.
                 */
                const GUI::ECS::Components::SpriteComponent getSprite() const;

                /**
                 * @brief Gets the collision data for the enemy.
                 *
                 * @return The Collision instance.
                 */
                const GUI::ECS::Systems::Collision getCollision() const;

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
                 * @brief Generates a random integer within a specified range.
                 *
                 * @param min The minimum value (inclusive). Default is 5.
                 * @param max The maximum value (inclusive). Default is 20.
                 *
                 * @return A random integer within the range.
                 */
                const int _randInt(int min = 5, int max = 20);

                bool _visible = true;                                           //!< Indicates if the enemy is visible.
                long int _health = 1;//00;                                      //!< The health of the enemy.
                unsigned int _delayBeforeShot = 20;                             //!< The delay before the enemy can shoot.
                GUI::ECS::Demo::Bullet _bullet;                                 //!< The bullet associated with the enemy.
                GUI::ECS::Systems::Collision _collision;                        //!< The collision data of the enemy.
                GUI::ECS::Components::SpriteComponent _sprite;                  //!< The sprite data of the enemy.
            };

            /**
             * @brief Outputs the sprite's info to a stream.
             *
             * @param os The output stream.
             * @param item The sprite to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const EnemyBrain &item);
        }
    }
}
