/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderComponent.hpp
*/

/**
 * @file RenderComponent.hpp
 * @brief This is the file that contains the class in charge of displaying or not an element.
 */

#pragma once
#include <SFML/Graphics/Texture.hpp>
#include "Debug.hpp"
#include "EntityNode.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class RenderComponent : EntityNode {
                public:
                RenderComponent() = default;
                RenderComponent(const RenderComponent &) = delete;
                RenderComponent &operator=(const RenderComponent &) = delete;
                ~RenderComponent() = default;
                void setTexture(const sf::Texture &texture);
                void setVisible(const bool visible);
                sf::Texture getTexture() const;
                bool getVisible() const;

                private:
                bool _visible;
                sf::Texture _texture;
            };
        }
    }
}

