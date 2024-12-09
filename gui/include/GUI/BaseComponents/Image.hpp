/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Image.hpp
*/

#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Factory/Image.hpp"
#include "Utilities/Colour.hpp"
#include "Utilities/Dimensions.hpp"

namespace GUI
{
    namespace BaseComponents
    {
        class Image : public Factory::ImageFactory {
            public:
            Image(const std::string &file_path);
            Image(const std::string &file_path, const Utilities::Dimensions &dimensions);
            ~Image();
            void setPosition(double x, double y);
            void setScale(double scale);
            void setRotation(double rotation);
            void setVisibility(bool visible);
            void setFillColour(const Utilities::Colour &colour);
            void removeFillColour();
            sf::Vector2f getPosition();
            sf::Vector2f getScale();
            bool getVisible();
            Utilities::Colour getFillColour();
            private:
            bool _visible;
            bool _overlay_present;
            sf::Sprite _sfml_sprite;
            sf::Texture _sfml_texture;
            Utilities::Dimensions _image_info;
            Utilities::Colour _image_overlay;
        };
    }
}
