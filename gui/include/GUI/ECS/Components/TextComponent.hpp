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
#include "GUI/ECS/Components/CollisionComponent.hpp"

namespace GUI
{
    namespace ECS
    {
        namespace Components
        {
            class TextComponent : public EntityNode {
                public:
                TextComponent(const std::uint32_t entityId = 0, const std::string &fontPath = "", const sf::Color &normalColor = sf::Color::Black, const sf::Color &hoverColor = sf::Color::Black, const sf::Color &clickedColor = sf::Color::Black, const std::string &text = "Sample Text", const std::uint32_t &size = 12, const sf::Vector2f &position = { 0,0 });
                ~TextComponent();

                void setFont(const sf::Font &font);

                void setNormalColor(const sf::Color &color);
                void setHoverColor(const sf::Color &color);
                void setClickedColor(const sf::Color &color);

                void setText(const std::string &text);

                void setSize(const std::uint32_t &size);

                void setFontPath(const std::string &fontPath);

                void setPosition(const sf::Vector2f &position);

                void setVisible(const bool visible);

                sf::Font getFont() const;

                std::string getFontPath() const;

                sf::Color getNormalColor() const;
                sf::Color getHoverColor() const;
                sf::Color getClickedColor() const;

                std::string getText() const;

                std::uint32_t getSize() const;

                sf::Vector2f getPosition() const;

                bool getVisible() const;

                void render(sf::RenderWindow &window) const;

                void update(const GUI::ECS::Utilities::MouseInfo &mouse);
                void update(const GUI::ECS::Components::TextComponent &copy);

                GUI::ECS::Components::TextComponent &operator =(const GUI::ECS::Components::TextComponent &copy);

                private:
                void _processTextComponent();
                void _loadFont();

                bool _visible;
                sf::Font _font;
                sf::Color _color = sf::Color::Black;
                std::string _text;
                std::uint32_t _size;
                sf::Color _hoverColor = sf::Color::Black;
                sf::Color _clickedColor = sf::Color::Black;
                std::string _fontPath;
                sf::Text _sfTextComponent;
                CollisionComponent _textPos;
            };
        }
    }
}

