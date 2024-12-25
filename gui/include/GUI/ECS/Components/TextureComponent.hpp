/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextureComponent.hpp
*/

/**
 * @file TextureComponent.hpp
 * @brief This is the file that contains the class in charge of displaying a texture.
 */

#pragma once

#include <optional>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include "Debug.hpp"
#include "ExceptionHandling.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/MouseInfo.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextureComponent : public EntityNode {
                public:
                TextureComponent();
                TextureComponent(const TextureComponent &other);
                TextureComponent(const sf::Texture &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo);
                TextureComponent(const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo);

                TextureComponent(const std::uint32_t entityId);
                TextureComponent(const std::uint32_t entityId, const TextureComponent &other);
                TextureComponent(const std::uint32_t entityId, const sf::Texture &texture, const GUI::ECS::Components::CollisionComponent &collisionInfo);
                TextureComponent(const std::uint32_t entityId, const std::string &filePath, const GUI::ECS::Components::CollisionComponent &collisionInfo);

                ~TextureComponent();

                void setVisible(const bool visible);
                void setFilePath(const std::string &filePath);
                void setTexture(const sf::Texture &texture);
                void setCollisionInfo(const GUI::ECS::Components::CollisionComponent &collisionInfo);
                void setPosition(const sf::Vector2f &position);
                void setSize(const sf::Vector2f &size);

                void update(const TextureComponent &copy);

                bool getVisible() const;
                const sf::Texture &getTexture() const;
                GUI::ECS::Components::CollisionComponent getCollisionInfo() const;

                TextureComponent &operator =(const GUI::ECS::Components::TextureComponent &copy);

                private:
                bool _visible;
                sf::Texture _texture;
                GUI::ECS::Components::CollisionComponent _collisionInfo;
            };
        }
    }
}

