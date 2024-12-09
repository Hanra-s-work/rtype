/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** CollisionCheck.hpp
*/

#pragma once
#include <SFML/Graphics.hpp>
#include "Utilities/Dimensions.hpp"

namespace GUI
{
    namespace Utilities
    {
        class CollisionCheck {
            public:
            CollisionCheck();
            ~CollisionCheck();
            bool isClicked(const Utilities::Dimensions &Dimensions, const sf::Vector2f &mouse_pos);
            bool isHovering(const Utilities::Dimensions &Dimensions, const sf::Vector2f &mouse_pos);
            bool isColliding(const Utilities::Dimensions &Dimension1, const Utilities::Dimensions &Dimensions2);
        };
    }
}
