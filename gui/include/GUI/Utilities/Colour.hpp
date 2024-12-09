/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** Colour.hpp
*/

#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Enums/ColourValues.hpp"

namespace GUI
{
    namespace Utilities
    {
        class Colour {
            public:
            Colour(sf::Uint8 red, sf::Uint8 green, sf::Uint8 blue, sf::Uint8 alpha = 255);
            Colour(const sf::Color &color);
            std::map<Enums::ColourValues, sf::Uint8> getColour();
            std::map<std::string, sf::Color> getSystemColours();
            private:
            sf::Color _user_colour;
            std::map<std::string, sf::Color> _system_colours;
        };
    }
}
