/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** EnemyBrain.hpp
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
            class EnemyBrain : public EntityNode {
                public:
                EnemyBrain(const std::uint32_t entityId = 0);

                EnemyBrain(const GUI::ECS::Demo::EnemyBrain &copy);

                EnemyBrain(const std::uint32_t entityId, const GUI::ECS::Demo::EnemyBrain &copy);

                ~EnemyBrain() = default;

                void setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet);

                void setPosition(const std::pair<float, float> &pos);

                void setDimension(const std::pair<float, float> &size);

                void setHealth(const long int health);

                void setVisible(const bool visible);

                void setBulletSize(const std::pair<float, float> &size);

                const bool isColliding(const GUI::ECS::Systems::Collision &second) const;

                const bool isVisible() const;

                const std::optional<GUI::ECS::Demo::Bullet> tick();

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

                const int _randInt(int min = 5, int max = 20);

                bool _visible = true;
                long int _health = 1;//00;
                unsigned int _delayBeforeShot = 20;
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
            std::ostream &operator<<(std::ostream &os, const EnemyBrain &item);
        }
    }
}
