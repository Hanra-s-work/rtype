/*
** EPITECH PROJECT, 2024
** Untitled (Workspace)
** File description:
** TextFactory.hpp
*/

#pragma once
#include <SFML/Graphics/Shape.hpp>
#include "Enums/ShapeTypes.hpp"
#include "Interfaces/IComponent.hpp"

namespace GUI
{
    namespace Factory
    {
        class ShapeFactory : public GUI::Interfaces::IComponent {
            public:
            virtual ~ShapeFactory() = default;
            virtual sf::Shape createShape(Enums::ShapeType shape_type, std::string colour) = 0;
        };
    }
}
