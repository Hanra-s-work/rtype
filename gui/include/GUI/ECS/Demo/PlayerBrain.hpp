/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** PlayerBrain.hpp
*/

/**
 * @file PlayerBrain.hpp
 *
 * @brief Declaration of the PlayerBrain class and related functionality.
 *
 * @details This file defines the PlayerBrain class, which manages the player's logic, interactions, and rendering within the ECS architecture.
 */

#pragma once
#include "Log.hpp"
#include "Recoded.hpp"
#include "LogMacros.hpp"
#include "Utilities.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Demo/Bullet.hpp"
#include "GUI/ECS/Demo/EnemyBrain.hpp"
#include "GUI/ECS/Components/SpriteComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Demo
        {
            class EnemyBrain;                                                   //!< Forward declaration of the EnemyBrain class.
            class Bullet;                                                       //!< Forward declaration of the Bullet class.

            /**
             * @brief The PlayerBrain class manages the player's logic, interactions, and rendering.
             *
             * @details This class is responsible for handling player-related behaviors, including shooting, collision detection, visibility, and rendering.
             */
            class PlayerBrain : public EntityNode {
                public:
                /**
                 * @brief Default constructor.
                 *
                 * @param entityId The unique ID of the entity. Default is 0.
                 */
                PlayerBrain(const std::uint32_t entityId = 0);

                /**
                 * @brief Copy constructor.
                 *
                 * @param copy The PlayerBrain instance to copy from.
                 */
                PlayerBrain(const GUI::ECS::Demo::PlayerBrain &copy);

                /**
                 * @brief Construct a new PlayerBrain object with an entity ID and a copy of another instance.
                 *
                 * @param entityId The unique ID of the entity.
                 * @param copy The PlayerBrain instance to copy from.
                 */
                PlayerBrain(const std::uint32_t entityId, const GUI::ECS::Demo::PlayerBrain &copy);

                /**
                 * @brief Destructor.
                 */
                ~PlayerBrain() = default;

                /**
                 * @brief Sets the sprite and bullet sprite components for the player.
                 *
                 * @param sprite The player's sprite component.
                 * @param bullet The player's bullet sprite component.
                 */
                void setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet);

                /**
                 * @brief Sets the player's position.
                 *
                 * @param pos A pair of (x, y) coordinates representing the position.
                 */
                void setPosition(const std::pair<float, float> &pos);

                /**
                 * @brief Sets the player's dimensions.
                 *
                 * @param size A pair of (width, height) dimensions.
                 */
                void setDimension(const std::pair<float, float> &size);

                /**
                 * @brief Sets the player's health.
                 *
                 * @param health The health value to set.
                 */
                void setHealth(const long int health);

                /**
                 * @brief Sets the player's visibility state.
                 *
                 * @param visible True if the player should be visible, false otherwise.
                 */
                void setVisible(const bool visible);

                /**
                 * @brief Sets the bullet dimensions.
                 *
                 * @param size A pair of (width, height) dimensions for the bullet.
                 */
                void setBulletSize(const std::pair<float, float> &size);

                /**
                 * @brief Checks if the player is colliding with another entity.
                 *
                 * @param second The collision system to check against.
                 *
                 * @return True if a collision is detected, false otherwise.
                 */
                const bool isColliding(const GUI::ECS::Systems::Collision &second) const;

                /**
                 * @brief Checks if the player is currently visible.
                 *
                 * @return True if the player is visible, false otherwise.
                 */
                const bool isVisible() const;

                /**
                 * @brief Updates the player's state for the current frame.
                 */
                void tick();

                /**
                 * @brief Simulates the player shooting a bullet.
                 *
                 * @return A Bullet instance representing the player's shot.
                 */
                const GUI::ECS::Demo::Bullet shoot() const;

                /**
                 * @brief Renders the player's sprite to the screen.
                 *
                 * @return The SpriteComponent representing the player's sprite.
                 */
                const GUI::ECS::Components::SpriteComponent render();

                /**
                 * @brief Updates the player's state by copying another PlayerBrain.
                 *
                 * @param copy The PlayerBrain instance to copy data from.
                 */
                void update(const GUI::ECS::Demo::PlayerBrain &copy);

                /**
                 * @brief Overloads the assignment operator to copy from another PlayerBrain.
                 *
                 * @param copy The PlayerBrain to copy data from.
                 *
                 * @return A reference to the updated instance.
                 */
                PlayerBrain &operator =(const GUI::ECS::Demo::PlayerBrain &copy);

                /**
                 * @brief Gets the player's visibility state.
                 *
                 * @return True if the player is visible, false otherwise.
                 */
                const bool getVisible() const;

                /**
                 * @brief Gets the player's health value.
                 *
                 * @return The player's current health.
                 */
                const long int getHealth() const;

                /**
                 * @brief Gets the player's bullet instance.
                 *
                 * @return The Bullet instance for the player.
                 */
                const GUI::ECS::Demo::Bullet getBullet() const;

                /**
                 * @brief Gets the player's sprite component.
                 *
                 * @return The SpriteComponent representing the player's sprite.
                 */
                const GUI::ECS::Components::SpriteComponent getSprite() const;

                /**
                 * @brief Gets the player's collision component.
                 *
                 * @return The Collision component for the player.
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
                bool _visible = true;                                           //!< The player's visibility state.
                long int _health = 100;                                         //!< The player's health value.
                GUI::ECS::Demo::Bullet _bullet;                                 //!< The player's bullet instance.
                GUI::ECS::Systems::Collision _collision;                        //!< The player's collision component.
                GUI::ECS::Components::SpriteComponent _sprite;                  //!< The player's sprite component.
            };

            /**
             * @brief Outputs the sprite's info to a stream.
             *
             * @param os The output stream.
             * @param item The sprite to output.
             *
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const PlayerBrain &item);
        }
    }
}
