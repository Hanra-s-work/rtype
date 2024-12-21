/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** SpriteComponent.hpp
*/

/**
 * @file SpriteComponent.hpp
 * @brief This is the file that contains the class in charge of managing a sprite.
 */

#pragma once

#include <SFML/Graphics/Sprite.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Components/TextureComponent.hpp"
#include "GUI/ECS/Components/AnimationComponent.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class SpriteComponent : EntityNode {
                public:
                SpriteComponent();
                SpriteComponent(const std::string &name);
                SpriteComponent(const std::string &spritesheetPath);
                SpriteComponent(const GUI::ECS::Components::CollisionComponent &collision);
                SpriteComponent(const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                ~SpriteComponent();

                void setName(const std::string &name);
                void setCollision(const GUI::ECS::Components::CollisionComponent &copy);

                void setSpritesheet(const std::string &spritesheetPath);
                void setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture);

                void setAnimation(const GUI::ECS::Components::AnimationComponent &animation);

                void update(const GUI::ECS::Components::SpriteComponent &copy);

                void render(sf::RenderWindow &window) const;

                bool isCollisionSet() const;
                bool isAnimationSet() const;
                bool isSpritesheetSet() const;
                bool isSpriteSet() const;

                void checkTick();

                std::string getName() const;
                GUI::ECS::Components::TextureComponent getSpritesheet() const;
                GUI::ECS::Components::CollisionComponent getCollision() const;
                GUI::ECS::Components::AnimationComponent getAnimation() const;

                SpriteComponent &operator =(const GUI::ECS::Components::SpriteComponent &copy);

                private:
                bool _visible = true;
                std::string _spriteName = "";
                bool _spritesheetSet = false;
                GUI::ECS::Components::TextureComponent _spritesheet;
                bool _collisionSet = false;
                GUI::ECS::Components::CollisionComponent _collision;
                bool _animationSet = false;
                GUI::ECS::Components::AnimationComponent _animation;
                bool _spriteSet = false;
                sf::Sprite _sfSprite;
            };
        }
    }
}
