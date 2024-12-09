/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** IComponent.hpp
*/

#pragma once
#include <SFML/Window.hpp>

namespace GUI
{
    namespace Interfaces
    {
        class IComponent {
            public:
            virtual ~IComponent() = default;
            virtual void render(sf::Window &window) = 0;
        };
    }
}
