/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** Text.hpp
*/

#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include "Factory/Text.hpp"
#include "Utilities/Colour.hpp"
#include "Utilities/Dimensions.hpp"
#include "Utilities/CollisionCheck.hpp"

namespace GUI
{
    namespace BaseComponents
    {
        class Text : public Factory::TextFactory {
            public:
            Text(const std::string &text, const std::string &font_file);
            Text(const std::string &text, const std::string &font_file, sf::Vector2f &position);
            ~Text();
            void setPosition(double x, double y);
            void setText(const std::string &text);
            void setFont(const std::string &font_file);
            void setFontSize(const unsigned int size);
            void setFontColor(const sf::Color &colour);
            void setFontColor(const Utilities::Colour &colour);
            void setFontColor(const sf::Uint8 red, const sf::Uint8 green, const sf::Uint8 blue, const sf::Uint8 alpha = 255);
            void setFontFamily(const std::string &font_file);
            bool isColliding(const Utilities::Dimensions &position);
            bool isClicked(const sf::Vector2f &mouse_pos);
            bool isHovering(const sf::Vector2f &mouse_pos);
            std::string getText();
            std::string getFontFamily();
            Utilities::Colour getColour();
            private:
            sf::Text _sfml_text;
            sf::Font _sfml_font;
            Utilities::CollisionCheck _collision_class;
        };
    }
}
