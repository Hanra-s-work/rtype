/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** Dimensions.hpp
*/

#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

namespace GUI
{
    namespace Utilities
    {
        class Dimensions {
            public:
            Dimensions();
            Dimensions(int x, int y);
            Dimensions(int width, int height);
            Dimensions(int width, int height, int x, int y);
            ~Dimensions();
            void setPosition(int x, int y);
            void setDimensions(int width, int height);
            sf::Vector2i getPosition();
            sf::Vector2i getDimensions();
            void updatePosition(int x, int y);
            void updateDimensions(int width, int height);
            private:
            sf::IntRect _dimensions;
        };
    }
}
