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
                TextComponent(std::string fontPath = "", sf::Color color = sf::Color::Black, std::string text = "Sample Text", std::uint32_t size = 12);
                ~TextComponent();

                void setFont(const sf::Font &font);
                void setFontPath(const std::string &fontPath);
                void setColor(const sf::Color &color);
                void setText(const std::string &text);
                void setSize(const std::uint32_t &size);

                sf::Font getFont() const;
                std::string getFontPath() const;
                sf::Color getColor() const;
                std::string getText() const;
                std::uint32_t getSize() const;

                private:
                std::string _fontPath;
                sf::Font _font;
                sf::Color _color;
                std::string _text;
                std::uint32_t _size;
            };
        }
    }
}

