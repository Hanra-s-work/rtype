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
            class EnemyBrain {
                public:
                EnemyBrain() = default;

                EnemyBrain(const GUI::ECS::Demo::EnemyBrain &copy);

                ~EnemyBrain() = default;

                void setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet);

                void setPosition(const std::pair<float, float> &pos);

                void setDimension(const std::pair<float, float> &size);

                void setHealth(const long int health);

                void setVisible(const bool visible);

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

                const unsigned int getHealth() const;

                const GUI::ECS::Demo::Bullet getBullet() const;

                const GUI::ECS::Components::SpriteComponent getSprite() const;

                const GUI::ECS::Systems::Collision getCollision() const;

                private:

                const int _randInt(int min = 5, int max = 20);

                bool _visible = true;
                unsigned int _health = 100;
                unsigned int _delayBeforeShot = 20;
                GUI::ECS::Demo::Bullet _bullet;
                GUI::ECS::Systems::Collision _collision;
                GUI::ECS::Components::SpriteComponent _sprite;
            };
        }
    }
}
