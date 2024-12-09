/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** TextFactory.hpp
*/

#pragma once
#include <SFML/Graphics/Text.hpp>
#include "Interfaces/IComponent.hpp"

namespace GUI
{
    namespace Factory
    {
        class TextFactory : public GUI::Interfaces::IComponent {
            public:
            virtual ~TextFactory() = default;
            virtual sf::Text createText(std::string text, std::string font_file) = 0;
        };
    }
}
