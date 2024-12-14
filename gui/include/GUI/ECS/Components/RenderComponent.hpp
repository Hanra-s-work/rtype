/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** RenderComponent.hpp
*/

#pragma once
#include <SFML/Graphics/Texture.hpp>
namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class RenderComponent {
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

