/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Shape.hpp
*/

#pragma once
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Enums/ShapeTypes.hpp"
#include "Utilities/Colour.hpp"
#include "Utilities/Dimensions.hpp"
#include "Utilities/CollisionCheck.hpp"

namespace GUI
{
    namespace BaseComponents
    {
        class Shape {
            Shape();
            void setShapeType(Enums::ShapeType type);
            void setPosition(const double x, const double y);
            void setSize(double width, double height);
            void setFillColour(const sf::Color &colour);
            void setFillColour(const Utilities::Colour &colour);
            void setFillColour(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);
            void setOutlineColour(const sf::Color &colour);
            void setOutlineColour(const Utilities::Colour &colour);
            void setOutlineColour(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);
            void setOutlineThickness(const double thickness);
            bool isColliding(const Utilities::Dimensions &position);
            bool isClicked(const sf::Vector2f &mouse_pos);
            bool isHovering(const sf::Vector2f &mouse_pos);
            double getOutlineThickness();
            Utilities::Colour getOutlineColour();
            Utilities::Colour getFillColour();
            Enums::ShapeType getShapeType();
            private:
            double _outline_thickness;
            Enums::ShapeType _shape_type;
            Utilities::Colour _fill_colour;
            Utilities::Colour _outline_colour;
            Utilities::Dimensions _shape_dimensions;
            Utilities::CollisionCheck _collision_class;
        };
    }
}
