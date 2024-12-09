/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** TextFactory.hpp
*/

#pragma once
#include <SFML/Graphics/Image.hpp>
#include "Interfaces/IComponent.hpp"

namespace GUI
{
    namespace Factory
    {
        class ImageFactory : public GUI::Interfaces::IComponent {
            public:
            virtual ~ImageFactory() = default;
            virtual sf::Image createImage(std::string file_path) = 0;
        };
    }
}
