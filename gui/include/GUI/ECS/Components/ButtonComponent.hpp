/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** ButtonComponent.hpp
*/

#pragma once
#include <functional>
#include <SFML/Graphics/Color.hpp>
namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class ButtonComponent {
                public:
                ButtonComponent() = default;
                ~ButtonComponent() = default;
                std::function<void()> callback();

                private:
                sf::Color hover_color;
                sf::Color clicked_color;
            };
        }
    }
}

