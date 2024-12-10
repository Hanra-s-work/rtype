/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextComponent.hpp
*/

#pragma once
#include <cstdint>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextComponent {
                public:
                TextComponent();
                ~TextComponent();

                private:
                sf::Font font;
                sf::Color color;
                std::string text;
                std::uint32_t size;
            };
        }
    }
}

