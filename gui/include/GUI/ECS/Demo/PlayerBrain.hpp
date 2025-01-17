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
            class PlayerBrain {
                public:
                PlayerBrain() = default;

                PlayerBrain(const GUI::ECS::Demo::PlayerBrain &copy);

                ~PlayerBrain() = default;

                void setSprite(const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &sprite, const std::shared_ptr<GUI::ECS::Components::SpriteComponent> &bullet);

                void setPosition(const std::pair<float, float> &pos);

                void setDimension(const std::pair<float, float> &size);

                void setHealth(const long int health);

                void setVisible(const bool visible);

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

                const unsigned int getHealth() const;

                const GUI::ECS::Demo::Bullet getBullet() const;

                const GUI::ECS::Components::SpriteComponent getSprite() const;

                const GUI::ECS::Systems::Collision getCollision() const;

                private:
                bool _visible = true;
                unsigned int _health = 100;
                GUI::ECS::Demo::Bullet _bullet;
                GUI::ECS::Systems::Collision _collision;
                GUI::ECS::Components::SpriteComponent _sprite;
            };
        }
    }
}
