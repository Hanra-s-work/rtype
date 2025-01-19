/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** PlayerBrain.hpp
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
            class EnemyBrain;
            class Bullet;
            class PlayerBrain : public EntityNode {
                public:
                PlayerBrain(const std::uint32_t entityId = 0);

                PlayerBrain(const GUI::ECS::Demo::PlayerBrain &copy);

                PlayerBrain(const std::uint32_t entityId, const GUI::ECS::Demo::PlayerBrain &copy);

                ~PlayerBrain() = default;

                void setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet);

                void setPosition(const std::pair<float, float> &pos);

                void setDimension(const std::pair<float, float> &size);

                void setHealth(const long int health);

                void setVisible(const bool visible);

                void setBulletSize(const std::pair<float, float> &size);

                const bool isColliding(const GUI::ECS::Systems::Collision &second) const;

                const bool isVisible() const;

                void tick();

                const GUI::ECS::Demo::Bullet shoot() const;

                const GUI::ECS::Components::SpriteComponent render();

                /**
                 * @brief Updates the sprite by copying another PlayerBrain.
                 *
                 * @param copy The PlayerBrain to copy data from.
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

                const bool getVisible() const;

                const long int getHealth() const;

                const GUI::ECS::Demo::Bullet getBullet() const;

                const GUI::ECS::Components::SpriteComponent getSprite() const;

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
                bool _visible = true;
                long int _health = 100;
                GUI::ECS::Demo::Bullet _bullet;
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
            std::ostream &operator<<(std::ostream &os, const PlayerBrain &item);
        }
    }
}
