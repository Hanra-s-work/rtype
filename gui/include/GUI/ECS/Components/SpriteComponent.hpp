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

#include <optional>
#include <SFML/Graphics/Sprite.hpp>

#include "Debug.hpp"
#include "MyRecodes.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Colour.hpp"
#include "GUI/ECS/Components/TextureComponent.hpp"
#include "GUI/ECS/Components/AnimationComponent.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class SpriteComponent : public EntityNode {
                public:
                SpriteComponent();
                SpriteComponent(const std::string &name);
                SpriteComponent(const GUI::ECS::Components::CollisionComponent &collision);
                SpriteComponent(const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::string &name, const std::string &spritesheetPath);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::string &name, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);

                SpriteComponent(const std::uint32_t entityId);
                SpriteComponent(const std::uint32_t entityId, const std::string &name);
                SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::CollisionComponent &collision);
                SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const std::uint32_t entityId, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const std::string &spritesheetPath);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::AnimationComponent &animation, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);
                SpriteComponent(const std::uint32_t entityId, const std::string &name, const GUI::ECS::Components::CollisionComponent &collision, const GUI::ECS::Components::TextureComponent &spritesheetTexture, const GUI::ECS::Utilities::Colour &normalColor, const GUI::ECS::Utilities::Colour &hoverColor, const GUI::ECS::Utilities::Colour &clickedColor);

                ~SpriteComponent();

                void setName(const std::string &name);
                void setCollision(const GUI::ECS::Components::CollisionComponent &copy);

                void setNormalColor(const GUI::ECS::Utilities::Colour &color);
                void setHoverColor(const GUI::ECS::Utilities::Colour &color);
                void setClickedColor(const GUI::ECS::Utilities::Colour &color);

                void setSpritesheet(const std::string &spritesheetPath);
                void setSpritesheet(const GUI::ECS::Components::TextureComponent &spritesheetTexture);

                void setAnimation(const GUI::ECS::Components::AnimationComponent &animation);

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const GUI::ECS::Components::SpriteComponent &copy);

                void render(sf::RenderWindow &window) const;

                bool isCollisionSet() const;
                bool isAnimationSet() const;
                bool isSpritesheetSet() const;
                bool isSpriteSet() const;

                void checkTick();

                const std::string getName() const;
                const GUI::ECS::Components::TextureComponent getSpritesheet() const;
                const GUI::ECS::Components::CollisionComponent getCollision() const;
                const GUI::ECS::Components::AnimationComponent getAnimation() const;

                const GUI::ECS::Utilities::Colour getNormalColor() const;
                const GUI::ECS::Utilities::Colour getHoverColor() const;
                const GUI::ECS::Utilities::Colour getClickedColor() const;
                /**
                 *@brief This is a function meant for debugging purposes
                 * It will dump the current state of the variables upon call.
                 * It will dump them for itself and any of it's underlying classes
                 *
                 * @param indent The level to which the class should be indented in the dump.
                 * @return const std::string The formatted output.
                 */
                const std::string getInfo(const unsigned int indent = 0) const;

                SpriteComponent &operator =(const GUI::ECS::Components::SpriteComponent &copy);

                private:
                void _processSprite();
                void _processCollision();
                void _processSpriteColor();

                bool _visible = true;
                std::string _spriteName = "";
                bool _spritesheetSet = false;
                GUI::ECS::Components::TextureComponent _spritesheet;
                bool _collisionSet = false;
                GUI::ECS::Components::CollisionComponent _collision;
                bool _animationSet = false;
                GUI::ECS::Components::AnimationComponent _animation;
                bool _spriteSet = false;
                std::optional<sf::Sprite> _sfSprite;
                GUI::ECS::Utilities::Colour _hoverColor = GUI::ECS::Utilities::Colour::White;
                GUI::ECS::Utilities::Colour _normalColor = GUI::ECS::Utilities::Colour::Transparent;
                GUI::ECS::Utilities::Colour _clickedColor = GUI::ECS::Utilities::Colour::Yellow;
            };

            /**
             * @brief Outputs the sprite's info to a stream.
             * @param os The output stream.
             * @param item The sprite to output.
             * @return The modified output stream.
             */
            std::ostream &operator<<(std::ostream &os, const SpriteComponent &item);
        }
    }
}
