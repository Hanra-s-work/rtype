/*
** EPITECH PROJECT, 2024
** rtype (Workspace)
** File description:
** TextComponent.hpp
*/

/**
 * @file TextComponent.hpp
 * @brief This is the file that contains a class in charge of managing a test component.
 */

#pragma once
#include <cstdint>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Debug.hpp"
#include "GUI/ECS/EntityNode.hpp"
#include "GUI/ECS/Utilities/Window.hpp"
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextComponent : EntityNode {
                public:
                TextComponent(const std::string &fontPath = "", const sf::Color &color = sf::Color::Black, const sf::Color &hoverColor = sf::Color::Black, const std::string &text = "Sample Text", const std::uint32_t &size = 12, const sf::Vector2f &position = { 0,0 });
                ~TextComponent();

                void setFont(const sf::Font &font);
                void setColor(const sf::Color &color);
                void setText(const std::string &text);
                void setSize(const std::uint32_t &size);
                void setHoverColor(const sf::Color &color);
                void setFontPath(const std::string &fontPath);
                void setPosition(const sf::Vector2f &position);
                void setVisible(const bool visible);

                sf::Font getFont() const;
                std::string getFontPath() const;
                sf::Color getColor() const;
                std::string getText() const;
                std::uint32_t getSize() const;
                bool getVisible() const;


                void renderText(sf::RenderWindow &window) const;
                void update(const GUI::ECS::Utilities::MouseInfo &mouse);

                private:
                void _processTextComponent();
                void _loadFont();
                bool _visible;
                sf::Font _font;
                sf::Color _color;
                std::string _text;
                std::uint32_t _size;
                sf::Color _hoverColor;
                std::string _fontPath;
                sf::Text _sfTextComponent;
                CollisionComponent _textPos;
            };
        }
    }
}
