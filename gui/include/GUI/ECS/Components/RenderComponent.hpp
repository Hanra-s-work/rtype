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

                private:
                bool visible;
                sf::Texture texture;
            };
        }
    }
}

